/*
 * ollama.c — Call Ollama's /api/generate endpoint from C.
 *
 * Zero external dependencies (beyond standard C + Winsock2).
 * Minimal hand-rolled JSON building and parsing.
 *
 * Usage examples:
 *   char *answer = call_ollama1("define recursion in three sentences", "llama3");
 *   free(answer);
 *
 *   char *answer2 = call_ollama2("define recursion in three sentences", "llama3");
 *   free(answer2);
 */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define OLLAMA_HOST "127.0.0.1"
#define OLLAMA_PORT 11434
#define OLLAMA_PATH "/api/generate"

/* ------------------------------------------------------------------ */
/*  Winsock init/cleanup                                               */
/* ------------------------------------------------------------------ */

static bool winsock_init(void)
{
  WSADATA wsa;
  if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
    fprintf(stderr, "WSAStartup failed: %d\n", WSAGetLastError());
    return false;
  }
  return true;
}

static void winsock_cleanup(void)
{
  WSACleanup();
}

/* ------------------------------------------------------------------ */
/*  Dynamic buffer for socket responses                                */
/* ------------------------------------------------------------------ */

typedef struct {
  char *data;
  size_t size;
} Buffer;

static bool buffer_append(Buffer *buf, const char *chunk, size_t len)
{
  char *tmp = realloc(buf->data, buf->size + len + 1);
  if (!tmp) {
    fprintf(stderr, "realloc failed\n");
    return false;
  }
  buf->data = tmp;
  memcpy(buf->data + buf->size, chunk, len);
  buf->size += len;
  buf->data[buf->size] = '\0';
  return true;
}

/* ------------------------------------------------------------------ */
/*  Minimal JSON helpers                                               */
/* ------------------------------------------------------------------ */

/* Escape a string for JSON (handles \, ", \n, \r, \t, \b, \f).
 * Returns a malloc'd string the caller must free(). */
static char *json_escape(const char *s)
{
  size_t len = strlen(s);
  /* Worst case: every char becomes \uXXXX (6 chars) */
  char *out = malloc(len * 6 + 1);
  if (!out)
    return NULL;

  char *p = out;
  for (size_t i = 0; i < len; i++) {
    unsigned char c = (unsigned char)s[i];
    switch (c) {
    case '"':
      *p++ = '\\';
      *p++ = '"';
      break;
    case '\\':
      *p++ = '\\';
      *p++ = '\\';
      break;
    case '\n':
      *p++ = '\\';
      *p++ = 'n';
      break;
    case '\r':
      *p++ = '\\';
      *p++ = 'r';
      break;
    case '\t':
      *p++ = '\\';
      *p++ = 't';
      break;
    case '\b':
      *p++ = '\\';
      *p++ = 'b';
      break;
    case '\f':
      *p++ = '\\';
      *p++ = 'f';
      break;
    default:
      if (c < 0x20) {
        p += snprintf(p, 7, "\\u%04x", c);
      } else {
        *p++ = (char)c;
      }
      break;
    }
  }
  *p = '\0';
  return out;
}

/* Find the value associated with "key" in a JSON string.
 * Returns a pointer into `json` right after the colon (skipping whitespace).
 * Returns NULL if not found. */
static const char *json_find_key(const char *json, const char *key)
{
  size_t klen = strlen(key);
  const char *p = json;
  while ((p = strstr(p, "\"")) != NULL) {
    p++; /* skip opening quote */
    if (strncmp(p, key, klen) == 0 && p[klen] == '"') {
      p += klen + 1; /* skip key and closing quote */
      /* Skip whitespace and colon */
      while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
      if (*p != ':')
        continue;
      p++;
      while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
      return p;
    }
  }
  return NULL;
}

/* Extract a JSON string value for the given key.
 * Returns a malloc'd unescaped string, or NULL if not found.
 * Handles basic JSON escape sequences. */
static char *json_get_string(const char *json, const char *key)
{
  const char *v = json_find_key(json, key);
  if (!v || *v != '"')
    return NULL;
  v++; /* skip opening quote */

  /* Find the extent of the string (handle escaped quotes) */
  size_t cap = 256;
  char *out = malloc(cap);
  if (!out)
    return NULL;
  size_t len = 0;

  while (*v && *v != '"') {
    if (len + 6 >= cap) {
      cap *= 2;
      char *tmp = realloc(out, cap);
      if (!tmp) {
        free(out);
        return NULL;
      }
      out = tmp;
    }
    if (*v == '\\' && v[1]) {
      v++;
      switch (*v) {
      case '"':
        out[len++] = '"';
        break;
      case '\\':
        out[len++] = '\\';
        break;
      case 'n':
        out[len++] = '\n';
        break;
      case 'r':
        out[len++] = '\r';
        break;
      case 't':
        out[len++] = '\t';
        break;
      case 'b':
        out[len++] = '\b';
        break;
      case 'f':
        out[len++] = '\f';
        break;
      case '/':
        out[len++] = '/';
        break;
      default:
        out[len++] = *v;
        break;
      }
    } else {
      out[len++] = *v;
    }
    v++;
  }
  out[len] = '\0';
  return out;
}

/* Extract a JSON number value for the given key.
 * Sets *found = true if the key exists and is a number. */
static double json_get_number(const char *json, const char *key, bool *found)
{
  const char *v = json_find_key(json, key);
  if (!v) {
    *found = false;
    return 0.0;
  }
  /* Must start with a digit or minus sign (not a quote or brace) */
  if (*v != '-' && (*v < '0' || *v > '9')) {
    *found = false;
    return 0.0;
  }
  char *end = NULL;
  double val = strtod(v, &end);
  *found = (end != v);
  return val;
}

/* ------------------------------------------------------------------ */
/*  Build the JSON payload                                             */
/* ------------------------------------------------------------------ */

static char *make_payload(const char *prompt, const char *model)
{
  char *esc_model = json_escape(model);
  char *esc_prompt = json_escape(prompt);
  if (!esc_model || !esc_prompt) {
    free(esc_model);
    free(esc_prompt);
    return NULL;
  }

  size_t needed = strlen(esc_model) + strlen(esc_prompt) + 64;
  char *json = malloc(needed);
  if (!json) {
    free(esc_model);
    free(esc_prompt);
    return NULL;
  }

  snprintf(json, needed,
           "{\"model\":\"%s\",\"prompt\":\"%s\",\"stream\":false}",
           esc_model, esc_prompt);

  free(esc_model);
  free(esc_prompt);
  return json; /* caller must free() */
}

/* ------------------------------------------------------------------ */
/*  POST to Ollama and return the raw response body                    */
/* ------------------------------------------------------------------ */

static char *post_ollama(const char *payload,
                         long read_timeout_s, long connect_timeout_s)
{
  SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock == INVALID_SOCKET) {
    fprintf(stderr, "socket() failed: %d\n", WSAGetLastError());
    fflush(stderr);
    return NULL;
  }

  /* Set connect timeout (blocking) */
  DWORD connect_ms = (DWORD)(connect_timeout_s * 1000);
  setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO,
             (const char *)&connect_ms, sizeof(connect_ms));

  struct sockaddr_in addr = {
      .sin_family = AF_INET,
      .sin_port = htons(OLLAMA_PORT),
  };
  inet_pton(AF_INET, OLLAMA_HOST, &addr.sin_addr);

  if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR) {
    int err = WSAGetLastError();
    if (err == WSAECONNREFUSED) {
      fprintf(stderr, "connect refused (is Ollama running on port %d?)\n",
              OLLAMA_PORT);
      fflush(stderr);
    } else {
      fprintf(stderr, "connect failed: %d\n", err);
      fflush(stderr);
    }
    closesocket(sock);
    return NULL;
  }

  DWORD recv_timeout_ms = (DWORD)(read_timeout_s * 1000);
  setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO,
             (const char *)&recv_timeout_ms, sizeof(recv_timeout_ms));

  /* Build HTTP request */
  int payload_len = (int)strlen(payload);
  int req_size = payload_len + 256;
  char *request = malloc((size_t)req_size);
  if (!request) {
    fprintf(stderr, "malloc failed\n");
    closesocket(sock);
    return NULL;
  }

  int req_len = snprintf(request, (size_t)req_size,
                         "POST %s HTTP/1.1\r\n"
                         "Host: %s:%d\r\n"
                         "Content-Type: application/json\r\n"
                         "Content-Length: %d\r\n"
                         "Connection: close\r\n"
                         "\r\n"
                         "%s",
                         OLLAMA_PATH, OLLAMA_HOST, OLLAMA_PORT, payload_len, payload);

  /* Send request */
  int total_sent = 0;
  while (total_sent < req_len) {
    int sent = send(sock, request + total_sent, req_len - total_sent, 0);
    if (sent == SOCKET_ERROR) {
      fprintf(stderr, "send() failed: %d\n", WSAGetLastError());
      free(request);
      closesocket(sock);
      return NULL;
    }
    total_sent += sent;
  }
  free(request);

  /* Read response */
  Buffer buf = {.data = NULL, .size = 0};
  char chunk[4096];
  for (;;) {
    int n = recv(sock, chunk, sizeof(chunk), 0);
    if (n == SOCKET_ERROR) {
      fprintf(stderr, "recv() failed: %d\n", WSAGetLastError());
      free(buf.data);
      closesocket(sock);
      return NULL;
    }
    if (n == 0)
      break;
    if (!buffer_append(&buf, chunk, (size_t)n)) {
      free(buf.data);
      closesocket(sock);
      return NULL;
    }
  }
  closesocket(sock);

  if (!buf.data) {
    fprintf(stderr, "empty response from Ollama\n");
    return NULL;
  }

  /* Skip HTTP headers — body starts after \r\n\r\n */
  char *body = strstr(buf.data, "\r\n\r\n");
  if (!body) {
    fprintf(stderr, "malformed HTTP response\n");
    free(buf.data);
    return NULL;
  }
  body += 4;

  char *result = strdup(body);
  free(buf.data);
  return result; /* caller must free() */
}

/* ------------------------------------------------------------------ */
/*  call_ollama — simple version, returns the answer string            */
/* ------------------------------------------------------------------ */

char *call_ollama1(const char *prompt, const char *model)
{
  if (!model)
    model = "llama3";

  char *payload = make_payload(prompt, model);
  if (!payload)
    return NULL;
  char *raw = post_ollama(payload, 120, 10);
  free(payload);
  if (!raw)
    return NULL;

  char *answer = json_get_string(raw, "response");
  free(raw);
  return answer; /* caller must free() */
}

/* ------------------------------------------------------------------ */
/*  Timer thread (prints dots while waiting)                           */
/* ------------------------------------------------------------------ */

typedef struct {
  volatile bool done;
} TimerCtx;

static void *timer_thread(void *arg)
{
  TimerCtx *ctx = (TimerCtx *)arg;
  while (!ctx->done) {
    putchar('.');
    fflush(stdout);
    Sleep(1000);
  }
  return NULL;
}

/* ------------------------------------------------------------------ */
/*  call_ollama2 — prints progress dots, then stats; returns answer    */
/* ------------------------------------------------------------------ */

char *call_ollama2(const char *prompt, const char *model)
{
  if (!model)
    model = "llama3";

  char *payload = make_payload(prompt, model);
  if (!payload)
    return NULL;

  /* Start the dot-printing timer thread */
  TimerCtx ctx = {.done = false};
  pthread_t tid;
  pthread_create(&tid, NULL, timer_thread, &ctx);

  /* Make the HTTP request */
  char *raw = post_ollama(payload, 300, 10);
  free(payload);

  /* Stop the timer regardless of success/failure */
  ctx.done = true;
  pthread_join(tid, NULL);

  if (!raw)
    return NULL;

  /* Extract answer */
  char *answer = json_get_string(raw, "response");

  /* Print stats */
  printf("\n\n--- Stats ---\n");

  bool found = false;
  double total_dur = json_get_number(raw, "total_duration", &found);
  if (found)
    printf("Duration:         %.2fs\n", total_dur / 1.0e9);

  double prompt_eval = json_get_number(raw, "prompt_eval_count", &found);
  int prompt_tokens = found ? (int)prompt_eval : 0;

  double eval_count = json_get_number(raw, "eval_count", &found);
  int resp_tokens = found ? (int)eval_count : 0;

  printf("Prompt tokens:    %d\n", prompt_tokens);
  printf("Response tokens:  %d\n", resp_tokens);
  printf("Total tokens:     %d\n", prompt_tokens + resp_tokens);

  double eval_dur = json_get_number(raw, "eval_duration", &found);
  if (found && eval_dur > 0)
    printf("Speed:            %.1f tokens/s\n",
           (double)resp_tokens / (eval_dur / 1.0e9));

  printf("\n");

  free(raw);
  return answer; /* caller must free() */
}

/* ------------------------------------------------------------------ */
/*  Quick demo                                                         */
/* ------------------------------------------------------------------ */

int SHOW_ollama1(void)
{
  const char *prompt = "Define recursion in three sentences.";
  const char *model = "llama3";

  if (!winsock_init())
    return 1;

  char *answer = call_ollama1(prompt, model);
  if (answer) {
    printf("%s\n", answer);
    free(answer);
  } else {
    fprintf(stderr, "No answer received.\n");
  }

  winsock_cleanup();
  return 0;
}

int SHOW_ollama2(void)
{
  const char *prompt = "Define recursion in six sentences.";
  const char *model = "llama3";

  if (!winsock_init())
    return 1;

  char *answer = call_ollama2(prompt, model);
  if (answer) {
    printf("%s\n", answer);
    free(answer);
  } else {
    fprintf(stderr, "No answer received.\n");
  }

  winsock_cleanup();
  return 0;
}

// end

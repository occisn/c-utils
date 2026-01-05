#include <float.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define NB_OF_CORES_2 8

// workers threads and tasks queue

// Compile with: gcc -pthread -march=native -O3

// Task structure for work items
typedef struct {
  uint64_t start;
  uint64_t end;
  double result;
  char padding[64 - sizeof(uint64_t)*2 - sizeof(double)]; // Prevent false sharing
} task_t;

// Thread pool structure
typedef struct {
  pthread_t *threads;
  int num_threads;
  
  task_t *tasks;
  int task_count;
  int task_capacity;
  int next_task;
  int completed_tasks;  // NEW: Track completed tasks
  
  pthread_mutex_t queue_mutex;
  pthread_cond_t queue_cond;
  pthread_cond_t complete_cond;  // NEW: Signal completion
  bool shutdown;
} thread_pool_t;

// Worker thread function
void* worker_thread(void *arg) {
  thread_pool_t *pool = (thread_pool_t *)arg;
  
  while (true) {
    pthread_mutex_lock(&pool->queue_mutex);
    
    // Wait for work or shutdown signal
    while (pool->next_task >= pool->task_count && !pool->shutdown) {
      pthread_cond_wait(&pool->queue_cond, &pool->queue_mutex);
    }
    
    // Check if we should exit
    if (pool->shutdown && pool->next_task >= pool->task_count) {
      pthread_mutex_unlock(&pool->queue_mutex);
      break;
    }
    
    // Get next task
    int task_id = pool->next_task++;
    task_t *task = &pool->tasks[task_id];
    pthread_mutex_unlock(&pool->queue_mutex);
    
    // Process task (unlock held during computation)
    double local_sum = 0.0;
    for (uint64_t i = task->start; i < task->end; i++) {
      double sign = (i & 1) ? -1.0 : 1.0;
      local_sum += sign / (2.0 * i + 1.0);
    }
    task->result = local_sum;
    
    // Signal completion
    pthread_mutex_lock(&pool->queue_mutex);
    pool->completed_tasks++;
    pthread_cond_signal(&pool->complete_cond);  // Wake up waiting thread
    pthread_mutex_unlock(&pool->queue_mutex);
  }
  
  return NULL;
}

// Initialize thread pool
thread_pool_t* thread_pool_create(int num_threads) {
  thread_pool_t *pool = malloc(sizeof(thread_pool_t));
  pool->num_threads = num_threads;
  pool->threads = malloc(num_threads * sizeof(pthread_t));
  pool->task_capacity = 1024;
  pool->tasks = malloc(pool->task_capacity * sizeof(task_t));
  pool->task_count = 0;
  pool->next_task = 0;
  pool->completed_tasks = 0;
  pool->shutdown = false;
  
  pthread_mutex_init(&pool->queue_mutex, NULL);
  pthread_cond_init(&pool->queue_cond, NULL);
  pthread_cond_init(&pool->complete_cond, NULL);  // NEW
  
  // Create worker threads
  for (int i = 0; i < num_threads; i++) {
    pthread_create(&pool->threads[i], NULL, worker_thread, pool);
  }
  
  return pool;
}

// Submit tasks to pool
void thread_pool_submit_tasks(thread_pool_t *pool, uint64_t n, int num_tasks) {
  pthread_mutex_lock(&pool->queue_mutex);
  
  pool->task_count = num_tasks;
  pool->next_task = 0;
  pool->completed_tasks = 0;  // NEW: Reset completion counter
  
  uint64_t chunk_size = (n + num_tasks - 1) / num_tasks;
  
  for (int i = 0; i < num_tasks; i++) {
    pool->tasks[i].start = i * chunk_size;
    pool->tasks[i].end = (i + 1) * chunk_size;
    if (pool->tasks[i].end > n) {
      pool->tasks[i].end = n;
    }
    pool->tasks[i].result = 0.0;
  }
  
  pthread_mutex_unlock(&pool->queue_mutex);
  pthread_cond_broadcast(&pool->queue_cond);  // Wake all workers
}

// Wait for all tasks to complete 
void thread_pool_wait(thread_pool_t *pool) {
  pthread_mutex_lock(&pool->queue_mutex);
  
  // Wait until all tasks are completed
  while (pool->completed_tasks < pool->task_count) {
    pthread_cond_wait(&pool->complete_cond, &pool->queue_mutex);
  }
  
  pthread_mutex_unlock(&pool->queue_mutex);
}

// Destroy thread pool
void thread_pool_destroy(thread_pool_t *pool) {
  pthread_mutex_lock(&pool->queue_mutex);
  pool->shutdown = true;
  pthread_mutex_unlock(&pool->queue_mutex);
  pthread_cond_broadcast(&pool->queue_cond);  // Wake all workers to exit
  
  for (int i = 0; i < pool->num_threads; i++) {
    pthread_join(pool->threads[i], NULL);
  }
  
  pthread_mutex_destroy(&pool->queue_mutex);
  pthread_cond_destroy(&pool->queue_cond);
  pthread_cond_destroy(&pool->complete_cond);  // NEW
  free(pool->threads);
  free(pool->tasks);
  free(pool);
}

// Main computation function using thread pool
double SHOW_parallelism_with_threads(uint64_t n) {
  struct timespec start_time, end_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);

  const int num_tasks = NB_OF_CORES_2 * 4;

  thread_pool_t *pool = thread_pool_create(NB_OF_CORES_2);
  
  // Submit tasks
  thread_pool_submit_tasks(pool, n, num_tasks);
  
  // Wait for completion (now efficient!)
  thread_pool_wait(pool);
  
  // Collect results
  double tmp = 0.0;
  for (int i = 0; i < num_tasks; i++) {
    tmp += pool->tasks[i].result;
  }
  tmp *= 4.0;
  
  thread_pool_destroy(pool);
  
  clock_gettime(CLOCK_MONOTONIC, &end_time);
  double duration = (end_time.tv_sec - start_time.tv_sec) +
                    (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
  printf("Leibniz formula: pi = %.20f (in %f s, %d threads, %d tasks)\n",
         tmp, duration, NB_OF_CORES_2, num_tasks);
  fflush(stdout);
  return duration;
}

// end

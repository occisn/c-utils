#include <stdio.h>
#include <time.h>

int progress_number(unsigned int sleep_duration_us) // 50000 for real demo
{
  printf("Beginning.\n");
  for (int i = 0; i <= 100; i++) {
    printf("\rProgress: %d%%", i);
    fflush(stdout); // force output immediately
    struct timespec ts = {0, sleep_duration_us * 1000L};
    nanosleep(&ts, NULL);  // simulate work (50 ms)
  }
  printf("\nDone!\n");
  return 0;
}

int progress_bar(unsigned int sleep_duration_us) // 50000 for real demo
{
  const int bar_width = 50;
  for (int i = 0; i <= 100; i++) {
    int pos = (i * bar_width) / 100;

    printf("\r[");
    for (int j = 0; j < bar_width; j++) {
      if (j < pos)
        printf("=");
      else if (j == pos)
        printf(">");
      else
        printf(" ");
    }
    printf("] %3d%%", i);

    fflush(stdout);
    struct timespec ts = {0, sleep_duration_us * 1000L};
    nanosleep(&ts, NULL);
  }
  printf("\n");
  return 0;
}

// end

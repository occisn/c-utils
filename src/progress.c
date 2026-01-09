#include <stdio.h>
#include <unistd.h> // for sleep()
#include <sys/types.h>

int progress_number(useconds_t sleep_duration_for_demo) // 50000 for real demo
{
  printf("Beginning.\n");
  for (int i = 0; i <= 100; i++) {
    printf("\rProgress: %d%%", i);
    fflush(stdout); // force output immediately
    usleep(sleep_duration_for_demo);  // simulate work (50 ms)
  }
  printf("\nDone!\n");
  return 0;
}

int progress_bar(useconds_t sleep_duration_for_demo) // 50000 for real demo
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
    usleep(sleep_duration_for_demo);
  }
  printf("\n");
  return 0;
}

// end

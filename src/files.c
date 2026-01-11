#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>

/* check that directory exist
if necessary, try to create it */
bool ensure_directory_exists(char* dir)
{
  struct stat st = {0};
  if (stat(dir, &st) == -1) {
#ifdef _WIN32
    if (mkdir(dir) != 0) {
#else
    if (mkdir(dir, 0755) != 0) {
#endif
      perror("Failed to create output directory");
      return false;
    }
    printf("Created output directory: %s\n", dir);
  }
  return true;
}

// end

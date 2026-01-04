#include <float.h>
#include <inttypes.h>
#include <omp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// flags: -fopenmp -march=native
double SHOW_parallelism_with_openmp(uint64_t n, int nb_chunks)
{
  struct timespec start_time, end_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);

  double tmp = 0.0;

#ifdef PRINT_INFO
  printf("Max threads available: %d\n", omp_get_max_threads());
  fflush(stdout);
#endif

  int chunk_size = n / nb_chunks;
#pragma omp parallel for schedule(static, chunk_size) reduction(+ : tmp)
  for (uint64_t i = 0; i < n; i++) {

#ifdef PRINT_INFO
    if (i % chunk_size == 0) {
      uint64_t chunk_start = i;
      uint64_t chunk_end =
          (i + chunk_size - 1 < n) ? i + chunk_size - 1 : n - 1;
      printf("[thread %d] chunk [%" PRIu64 " .. %" PRIu64 "]\n",
             omp_get_thread_num(),
             chunk_start,
             chunk_end);
      fflush(stdout);
    }
#endif

    double sign = (i & 1) ? -1.0 : 1.0;
    tmp += sign / (2.0 * i + 1.0);
  }

  tmp *= 4.0;

  clock_gettime(CLOCK_MONOTONIC, &end_time);

  double duration = (end_time.tv_sec - start_time.tv_sec) +
                    (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

  printf("Leibniz formula:  %d chunks, p = %.20f (in %f s)\n",
         nb_chunks, tmp, duration);
  fflush(stdout);

  return duration;
}

// end

#include <float.h>
#include <omp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

// flags: -fopenmp -march=native

#define NUMBER_OF_CORES 8

// with reduction:
double SHOW_parallelism_with_openmp_1(uint64_t n)
{
  struct timespec start_time, end_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);

  double tmp = 0.0;

  // omp_get_max_threads()

  const int nb_chunks = NUMBER_OF_CORES * 4;
  const int chunk_size = n / nb_chunks;

#pragma omp parallel for schedule(static, chunk_size) reduction(+ : tmp) num_threads(NUMBER_OF_CORES)
  for (uint64_t i = 0; i < n; i++) {
    // omp_get_thread_num()
    double sign = (i & 1) ? -1.0 : 1.0;
    tmp += sign / (2.0 * i + 1.0);
  }

  tmp *= 4.0;

  clock_gettime(CLOCK_MONOTONIC, &end_time);

  double duration = (end_time.tv_sec - start_time.tv_sec) +
                    (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

  printf("Leibniz formula: pi = %.20f (in %f s)\n",
         tmp, duration);
  fflush(stdout);

  return duration;
}

// without reduction:
double SHOW_parallelism_with_openmp_2(uint64_t n)
{
  struct timespec start_time, end_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);

  double tmp = 0.0;

#pragma omp parallel
  {
    double local_sum = 0.0;
    // omp_get_max_threads()

#pragma omp for nowait
    // or no for schedule(static) nowait
    for (uint64_t i = 0; i < n; i++) {
      // omp_get_thread_num()
      double sign = (i & 1) ? -1.0 : 1.0;
      local_sum += sign / (2.0 * i + 1.0);
    }

#pragma omp atomic
    tmp += local_sum;
  }

  tmp *= 4.0;

  clock_gettime(CLOCK_MONOTONIC, &end_time);

  double duration = (end_time.tv_sec - start_time.tv_sec) +
                    (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

  printf("Leibniz formula: pi = %.20f (in %f s)\n",
         tmp, duration);
  fflush(stdout);

  return duration;
}

// tasks:
double SHOW_parallelism_with_openmp_3(uint64_t n)
{

  struct timespec start_time, end_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);

  double tmp = 0.0;

#pragma omp parallel
  {
#pragma omp single
    {
      const int num_tasks = omp_get_num_threads() * 4;
      uint64_t chunk = n / num_tasks;
      for (int t = 0; t < num_tasks; t++) {
        uint64_t start = t * chunk;
        uint64_t end = (t == num_tasks - 1) ? n : (t + 1) * chunk;
#pragma omp task
        {
          double local = 0.0;
          for (uint64_t i = start; i < end; i++) {
            double sign = (i & 1) ? -1.0 : 1.0;
            local += sign / (2.0 * i + 1.0);
          }
#pragma omp atomic
          tmp += local;
        }
      }
    }
  }

   tmp *= 4.0;

  clock_gettime(CLOCK_MONOTONIC, &end_time);

  double duration = (end_time.tv_sec - start_time.tv_sec) +
                    (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

  printf("Leibniz formula: pi = %.20f (in %f s)\n",
         tmp, duration);
  fflush(stdout);

  return duration;
  
}

// end

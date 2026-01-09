#include "durations.h"
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Helper function to calculate pi using Leibniz formula
double calculate_pi_leibniz_A(long n)
{
  double tmp = 0.0;
  for (long i = 0; i < n; i++) {
    double sign = (i % 2 == 0) ? 1.0 : -1.0;
    tmp += sign / (2.0 * i + 1.0);
  }

  tmp = 4.0 * tmp;
  printf("Leibniz: pi = %f\n", tmp);
  return tmp;
}

void SHOW_measure_duration(void)
{
  struct timespec start, end;
  double duration;
  clock_gettime(CLOCK_MONOTONIC, &start);

  // do something:
  calculate_pi_leibniz_A(100000000);

  clock_gettime(CLOCK_MONOTONIC, &end);
  duration = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
  printf("Duration: %f seconds\n", duration);
}

/*
 * Execute function 5 times, print each duration, and report the quickest.
 */
void SHOW_benchmark_5_times_A(void)
{
  const int nb_runs = 5;
  double durations[5];

  for (int i = 0; i < nb_runs; i++) {
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    // The function to benchmark
    calculate_pi_leibniz_A(100000000);

    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    double duration = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Run %d / %d: %f seconds\n", i + 1, nb_runs, duration);
    fflush(stdout);
    durations[i] = duration;
  }

  // Find quickest and slowest
  double quickest = DBL_MAX;
  double slowest = 0.0;
  for (int i = 0; i < nb_runs; i++) {
    if (durations[i] < quickest)
      quickest = durations[i];
    if (durations[i] > slowest)
      slowest = durations[i];
  }
  printf("\nRESULTS:\n");
  for (int i = 0; i < nb_runs; i++) {
    printf("Run %d / %d: %f seconds\n", i + 1, nb_runs, durations[i]);
  }
  printf("=> quickest time: %f seconds\n", quickest);
  printf("=> slowest time:  %f seconds = quickest + %ld %%\n",
         slowest, (long)(100.0 * (slowest - quickest) / quickest));
}

double calculate_pi_leibniz_B(long n)
{

  struct timespec start, end;
  double duration;
  clock_gettime(CLOCK_MONOTONIC, &start);

  double tmp = 0.0;
  for (long i = 0; i < n; i++) {
    double sign = (i % 2 == 0) ? 1.0 : -1.0;
    tmp += sign / (2.0 * i + 1.0);
  }

  tmp = 4.0 * tmp;

  clock_gettime(CLOCK_MONOTONIC, &end);
  duration = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

  printf("Leibniz: pi = %f (in %f seconds)\n", tmp, duration);

  return duration;
}

/*
 * Execute function 5 times, print each duration, and report the quickest.
 * In this version, the function shall return the execution duration to be benchmarked.
 * This variant enables to do other things in the version, outside of the measured time, for instance printing result."
 */

static int compare_double(const void *a, const void *b)
{
  double arg1 = *(const double *)a;
  double arg2 = *(const double *)b;
  if (arg1 < arg2)
    return -1;
  if (arg1 > arg2)
    return 1;
  return 0;
}

void SHOW_benchmark_5_times_B(void)
{
  const int nb_runs = 5;
  double durations[nb_runs];

  for (int i = 0; i < nb_runs; i++) {
    double duration = calculate_pi_leibniz_B(100000000);
    printf("Run %d / %d: %f seconds\n", i + 1, nb_runs, duration);
    fflush(stdout);
    durations[i] = duration;
  }

  qsort(durations, nb_runs, sizeof(double), compare_double);
  double quickest = durations[0];
  double second_best = durations[1];
  double slowest = durations[nb_runs - 1];

  printf("\nRESULTS:\n");
  for (int i = 0; i < nb_runs; i++) {
    printf("Run %d / %d: %f seconds\n", i + 1, nb_runs, durations[i]);
  }
  printf("=> quickest execution: %f seconds\n", quickest);
  printf("=> second best:        %f seconds\n", second_best);
  printf("=> slowest execution:  %f seconds = quickest + %ld %%\n",
         slowest, (long)(100.0 * (slowest - quickest) / quickest));
}

// end

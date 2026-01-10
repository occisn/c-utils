#include "durations.h"
#include "integers.h"
#include "integers_digits.h"
#include "integers_primes.h"
#include "parallelism_with_openmp.h"
#include "parallelism_with_threads.h"
#include "progress.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  printf("\nHello World!\n");

  printf("\n");
  printf("duration / measure_duration\n");
  printf("---------------------------\n");
  SHOW_measure_duration();
  fflush(stdout);

  printf("\n");
  printf("duration / measure_duration - benchmark x5 (A)\n");
  printf("----------------------------------------------\n");
  SHOW_benchmark_5_times_A();
  fflush(stdout);

  printf("\n");
  printf("duration / measure_duration - benchmark x5 (B)\n");
  printf("----------------------------------------------\n");
  SHOW_benchmark_5_times_B();
  fflush(stdout);

  printf("\n");
  printf("integers / gcd_int\n");
  printf("--------------------\n");
  printf("gcd(12,15) = %d\n", gcd_int(12, 15));
  fflush(stdout);

  printf("\n");
  printf("integers / lcm_int\n");
  printf("-------------------\n");
  printf("lcm(6, 9) = %d\n", lcm_int(6, 9));
  fflush(stdout);

  printf("\n");
  printf("integers_digits / reverse_number_int\n");
  printf("---------------------------------\n");
  printf("123 --> %d\n", reverse_number_int(123));
  fflush(stdout);

  printf("\n");
  printf("integers_primes / SHOW_largest_prime_factor_uint64\n");
  printf("----------------------------------------------------\n");
  SHOW_largest_prime_factor_uint64();
  fflush(stdout);

  printf("\n");
  printf("integers_primes / SHOW_factorize_uint64\n");
  printf("-----------------------------------------\n");
  SHOW_factorize_uint64();
  fflush(stdout);

  printf("\n");
  printf("integers_primes / SHOW_is_prime_uint64\n");
  printf("----------------------------------------\n");
  SHOW_is_prime_uint64();
  fflush(stdout);

  printf("\n");
  printf("integers_primes / SHOW_sieve_eratosthenes_uint64\n");
  printf("--------------------------------------------------\n");
  SHOW_sieve_eratosthenes_uint64();
  fflush(stdout);

  printf("\n");
  printf("integers_primes / SHOW_nth_prime_uint64\n");
  printf("-----------------------------------------\n");
  SHOW_nth_prime_uint64();
  fflush(stdout);

  printf("\n");
  printf("parallelism / SHOW_parallelism_with_openmp\n");
  printf("------------------------------------------\n");
  SHOW_parallelism_with_openmp_1(1000000000); // 1 billion
  SHOW_parallelism_with_openmp_2(1000000000); // 1 billion
  SHOW_parallelism_with_openmp_3(1000000000); // 1 billion
  fflush(stdout);

  printf("\n");
  printf("parallelism / SHOW_parallelism_with_threads\n");
  printf("-------------------------------------------\n");
  SHOW_parallelism_with_threads(1000000000); // 1 billion
  fflush(stdout);

  printf("\n");
  printf("progress\n");
  printf("--------\n");
  progress_number(1000); // 50000 for real demo
  fflush(stdout);
  progress_bar(1000); // 50000 for real demo
  fflush(stdout);

  printf("\n(end)\n");

  return EXIT_SUCCESS;
}

// end

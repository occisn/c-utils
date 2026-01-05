#include "durations.h"
#include "integers.h"
#include "integers_digits.h"
#include "integers_primes.h"
#include "parallelism_with_openmp.h"
#include "parallelism_with_threads.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  printf("\nHello World!\n");

  printf("\n");
  printf("duration / measure_duration\n");
  printf("---------------------------\n");
  SHOW__measure_duration();
  fflush(stdout);

  printf("\n");
  printf("duration / measure_duration - benchmark x5 (A)\n");
  printf("----------------------------------------------\n");
  SHOW__benchmark_5_times_A();
  fflush(stdout);

 printf("\n");
  printf("duration / measure_duration - benchmark x5 (B)\n");
  printf("----------------------------------------------\n");
  SHOW__benchmark_5_times_B();
  fflush(stdout);

  printf("\n");
  printf("integers / gcd__int\n");
  printf("--------------------\n");
  printf("gcd(12,15) = %d\n", gcd__int(12,15));
  fflush(stdout);

  printf("\n");
  printf("integers / lcm__int\n");
  printf("-------------------\n");
  printf("lcm(6, 9) = %d\n", lcm__int(6, 9));
  fflush(stdout);

  printf("\n");
  printf("integers_digits / reverse_number\n");
  printf("---------------------------------\n");
  printf("123 --> %d\n", reverse_number(123));
  fflush(stdout);

  printf("\n");
  printf("integers_primes / SHOW__largest_prime_factor__uint64\n");
  printf("----------------------------------------------------\n");
  SHOW__largest_prime_factor__uint64();
  fflush(stdout);

  printf("\n");
  printf("integers_primes / SHOW__factorize__uint64\n");
  printf("-----------------------------------------\n");
  SHOW__factorize__uint64();
  fflush(stdout);

  printf("\n");
  printf("integers_primes / SHOW__is_prime__uint64\n");
  printf("----------------------------------------\n");
  SHOW__is_prime__uint64();
  fflush(stdout);

  printf("\n");
  printf("integers_primes / SHOW__sieve_eratosthenes__uint64\n");
  printf("--------------------------------------------------\n");
  SHOW__sieve_eratosthenes__uint64();
  fflush(stdout);

  printf("\n");
  printf("integers_primes / SHOW__nth_prime__uint64\n");
  printf("-----------------------------------------\n");
  SHOW__nth_prime__uint64();
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

  printf("\n(end)\n");

  return EXIT_SUCCESS;
}

// end

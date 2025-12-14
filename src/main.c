#include "integers.h"
#include "integers_primes.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  printf("\nHello World!\n");

 printf("\n");
  printf("SHOW__largest_prime_factor__uint64\n");
  printf("----------------------------------\n");
  SHOW__largest_prime_factor__uint64();
  fflush(stdout);
  
  printf("\n");
  printf("SHOW__factorize__uint64\n");
  printf("------------------------\n");
  SHOW__factorize__uint64();
  fflush(stdout);

  printf("\n");
  printf("SHOW__is_prime__uint64\n");
  printf("----------------------\n");
  SHOW__is_prime__uint64();
  fflush(stdout);

  printf("\n");
  printf("SHOW_1__sieve_eratosthenes__simple__uint64\n");
  printf("------------------------------------------\n");
  SHOW_1__sieve_eratosthenes__simple__uint64();
  fflush(stdout);

  printf("\n");
  printf("SHOW_2__sieve_eratosthenes__simple__uint64\n");
  printf("------------------------------------------\n");
  SHOW_2__sieve_eratosthenes__simple__uint64();
  fflush(stdout);

  printf("\n");
  printf("SHOW_1__sieve_eratosthenes__odd_bit__uint64\n");
  printf("-------------------------------------------\n");
  SHOW_1__sieve_eratosthenes__odd_bit__uint64();
  fflush(stdout);

  printf("\n");
  printf("SHOW_2__sieve_eratosthenes__odd_bit__uint64\n");
  printf("-------------------------------------------\n");
  SHOW_2__sieve_eratosthenes__odd_bit__uint64();
  fflush(stdout);

  printf("\n");
  printf("SHOW__list_of_primes_below__uint64\n");
  printf("----------------------------------\n");
  SHOW__list_of_primes_below__uint64();
  fflush(stdout);

  printf("\n");
  printf("SHOW__nth_prime__uint64\n");
  printf("-----------------------\n");
  SHOW__nth_prime__uint64();
  fflush(stdout);

  return EXIT_SUCCESS;
}

// end

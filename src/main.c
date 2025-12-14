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
  printf("SHOW__sieve_eratosthenes__uint64\n");
  printf("--------------------------------\n");
  SHOW__sieve_eratosthenes__uint64();
  fflush(stdout);

  printf("\n");
  printf("SHOW__nth_prime__uint64\n");
  printf("-----------------------\n");
  SHOW__nth_prime__uint64();
  fflush(stdout);

  printf("\n(end)\n");
  
  return EXIT_SUCCESS;
}

// end

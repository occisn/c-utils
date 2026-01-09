#include "integers_primes.h"
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for memset

/**
 * Finds the largest prime factor of a given unsigned 64-bit integer.
 *
 * This function uses an optimized trial division algorithm:
 * 1. First removes all factors of 2 (the only even prime)
 * 2. Then removes all factors of 3
 * 3. Finally checks only numbers of the form 6k±1 (where k ≥ 1), since all
 *    primes greater than 3 can be expressed in this form
 *
 * The algorithm repeatedly divides n by each prime factor found, effectively
 * computing the complete prime factorization while only tracking the largest.
 *
 * @param n The number to factorize (must be a positive integer)
 *
 * @return The largest prime factor of n.
 * Special case: returns 0 if n < 2
 *
 * @example
 *   largest_prime_factor_uint64(28)      returns 7   (28 = 2² × 7)
 *
 * (v1 available in occisn/c-utils GitHub repository)
 */
uint64_t largest_prime_factor_uint64(uint64_t n)
{
  uint64_t largest = 0;

  if (n < 2) {
    return 0;
  }

  // Remove all factors of 2
  while (n % 2 == 0) {
    largest = 2;
    n /= 2;
  }

  // Remove all factors of 3
  while (n % 3 == 0) {
    largest = 3;
    n /= 3;
  }

  // Now n is odd and not divisible by 3.
  // Test divisors of the form 6k-1 and 6k+1.
  uint64_t i = 5;
  while (i * i <= n) {

    // Check i = 6k - 1
    if (n % i == 0) {
      largest = i;
      n /= i;
    }
    // Check i+2 = 6k + 1
    else if (n % (i + 2) == 0) {
      largest = i + 2;
      n /= (i + 2);
    } else {
      i += 6;
    }
  }

  // If n is still > 1, it is prime
  if (n > 1)
    largest = n;

  return largest;
}

int SHOW_largest_prime_factor_uint64(void)
{
  const uint64_t n = 10001;
  uint64_t largest_prime_factor = largest_prime_factor_uint64(n);
  if (largest_prime_factor == 0) {
    printf("largest_prime_factor called with a parameter < 2\n");
    return EXIT_FAILURE;
  }
  printf("Largest prime factor of %" PRIu64 " is %" PRIu64 ".\n", n, largest_prime_factor_uint64(n));
  return EXIT_SUCCESS;
}

// ===

/**
 * Allocates and returns an array of prime factors of n.
 *
 * @param n        The integer to factorize (n >= 2).
 * @param count_out Pointer to size_t to receive the number of factors.
 * @param multiplicity If true, includes repeated primes; if false, only distinct primes.
 * @return Pointer to dynamically allocated array of prime factors.
 *         Returns NULL if memory allocation fails or n < 2.
 *         Caller is responsible for freeing the returned array.
 *
 * Example usage:
 * @code
 *    const uint64_t n = 9223372036854775808ULL; // 2^63
 *    size_t count;
 *    uint64_t *factors = factorize_uint64(n, &count, false);
 *    if (factors == NULL) {
 *       printf("Problem in factorization\n");
 *       return EXIT_FAILURE;
 *   } else {
 *      printf("Prime factors of %" PRIu64 ":\n", n);
 *      for (size_t i = 0; i < count; i++) {
 *      printf("%" PRIu64 "\n", factors[i]);
 *  }
 */
uint64_t *factorize_uint64(uint64_t n, size_t *count_out, bool multiplicity)
{
  *count_out = 0;
  if (n < 2)
    return NULL;

  size_t cap = 8;
  uint64_t *factors = malloc(cap * sizeof(uint64_t));
  if (!factors)
    return NULL;

#define PUSH_FACTOR(p)                                          \
  do {                                                          \
    if (*count_out == cap) {                                    \
      cap *= 2;                                                 \
      uint64_t *tmp = realloc(factors, cap * sizeof(uint64_t)); \
      if (!tmp)                                                 \
        goto failure;                                           \
      factors = tmp;                                            \
    }                                                           \
    factors[(*count_out)++] = (p);                              \
  } while (0)

  // (1) factor out 2
  if (multiplicity) {
    while ((n & 1ULL) == 0) {
      PUSH_FACTOR(2);
      n >>= 1;
    }
  } else if ((n & 1ULL) == 0) {
    PUSH_FACTOR(2);
    while ((n & 1ULL) == 0)
      n >>= 1;
  }

  // (2) odd primes
  uint64_t limit = (uint64_t)sqrtl((long double)n);
  for (uint64_t p = 3; p <= limit; p += 2) {
    if (multiplicity) {
      while (n % p == 0) {
        PUSH_FACTOR(p);
        n /= p;
        limit = (uint64_t)sqrtl((long double)n);
      }
    } else if (n % p == 0) {
      PUSH_FACTOR(p);
      while (n % p == 0)
        n /= p;
      limit = (uint64_t)sqrtl((long double)n);
    }
  }

  // (3) remainder
  if (n > 1) {
    PUSH_FACTOR(n);
  }

#undef PUSH_FACTOR
  return factors;

failure:
  free(factors);
  return NULL;
}

int SHOW_factorize_uint64(void)
{
  // const uint64_t n = 18446744073709551615ULL;  // 2^64 - 1
  // const uint64_t n = 9223372036854775808ULL; // 2^63
  const uint64_t n = 614889782588491410ULL; // 64-bit inteeger with the most different prime factors
  // const uint64_t n = 18446744073709551557ULL; // largest 64-bit prime
  size_t count;

  uint64_t *factors = factorize_uint64(n, &count, true);

  if (factors == NULL) {
    printf("Problem in factorization\n");
    return EXIT_FAILURE;
  }
  printf("%zu prime factor(s) of %" PRIu64 ":\n", count, n);
  printf("%" PRIu64, factors[0]);
  for (size_t i = 1; i < count; i++) {
    printf(" %" PRIu64, factors[i]);
  }
  printf("\n");
  free(factors);
  return EXIT_SUCCESS;
}

// ===

/**
 * Checks whether an integer is prime
 *
 * @param n        The integer to test
 * @return true/false
 */
bool is_prime_uint64(uint64_t n)
{
  if (n < 2)
    return false; // 0 and 1 are not prime
  if (n <= 3)
    return true; // 2 and 3 are prime
  if ((n % 2) == 0 || (n % 3) == 0)
    return false;

  // Test divisors of the form 6k ± 1 up to sqrt(n)
  uint64_t limit = (uint64_t)sqrtl((long double)n);
  for (uint64_t i = 5; i <= limit; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0)
      return false;
  }
  return true;
}

int SHOW_is_prime_uint64(void)
{
  uint64_t numbers[] = {2, 3, 4, 17, 19, 20, 97};
  // 18446744073709551557ULL
  for (size_t i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++) {
    uint64_t n = numbers[i];
    printf("%" PRIu64 " is %s\n", n, is_prime_uint64(n) ? "prime" : "not prime");
  }
  return EXIT_SUCCESS;
}

// ===

/**
 * Computes the Sieve of Eratosthenes up to n (exclusive)
 * and counts the number of primes.
 *
 * @param n         Upper limit (exclusive)
 * @return Pointer to dynamically allocated bool array where:
 *         is_prime[i] == true if i is prime, false otherwise.
 *         Returns NULL if n < 2 or memory allocation fails.
 *         Caller is responsible for freeing the array.
 *
 * (v1 available in occisn/c-utils GitHub repository)
 */
bool *sieve_eratosthenes_uint64(uint64_t n)
{
  if (n < 2)
    return NULL;

  bool *is_prime = malloc(n * sizeof(bool));
  if (!is_prime)
    return NULL;

  for (uint64_t i = 0; i < n; i++)
    is_prime[i] = true;
  is_prime[0] = is_prime[1] = false;

  uint64_t limit = (uint64_t)sqrtl((long double)n);
  for (uint64_t p = 2; p <= limit; p++) {
    if (is_prime[p]) {
      for (uint64_t multiple = p * p; multiple < n; multiple += p) {
        is_prime[multiple] = false;
      }
    }
  }

  return is_prime;
}

int SHOW_sieve_eratosthenes_uint64(void)
{
  const uint64_t n = 100;
  bool *is_prime = sieve_eratosthenes_uint64(n);

  if (is_prime == NULL) {
    printf("sieve_eratosthenes: memory allocation failed or n < 2\n");
    return EXIT_FAILURE;
  }

  printf("Primes below %" PRIu64 ":\n", n);
  for (uint64_t i = 2; i < n; i++) {
    if (is_prime[i])
      printf("%" PRIu64 " ", i);
  }
  printf("\n");

  free(is_prime); // <------- important
  return EXIT_SUCCESS;
}

// ===

/**
 * Returns n-th prime
 *
 * @param n
 * @return n-th prime or 0 if failure
 */
uint64_t nth_prime_uint64(uint64_t n)
{

  if (n < 1) {
    return 0;
  }
  
  // Initial upper bound estimate for n-th prime
  double estimate = (n >= 6) ? n * (log(n) + log(log(n))) : 15;
  uint64_t limit = (uint64_t)estimate + 1;

  bool *is_prime = sieve_eratosthenes_uint64(limit);
  if (is_prime == NULL) {
    printf("Construction of sieve failed.\n");
    return EXIT_FAILURE;
  }

  uint64_t nth_prime;

  if (n == 1) {
    nth_prime = 2;
  } else {

    size_t count = 0; // count 2
    size_t i = 0;
    for (i = 0; i < limit; i++) {
      if (is_prime[i])
        count++;
      if (count == n)
        break;
    }

    if (count < n) {
      printf("Sieve is not big enough.\n");
      goto failure;
    }

    nth_prime = i;
  }

  free(is_prime);
  return nth_prime;

failure:
  free(is_prime);
  return EXIT_FAILURE;
}

int SHOW_nth_prime_uint64(void)
{
  const uint64_t n = 1000;
  uint64_t nth_prime = nth_prime_uint64(n);
  if (nth_prime == 0) {
    printf("nth_prime: problem with nth prime calculation\n");
    return EXIT_FAILURE;
  }
  printf("%" PRIu64 "-th prime is %" PRIu64 "\n", n, nth_prime);
  return EXIT_SUCCESS;
}

// === end

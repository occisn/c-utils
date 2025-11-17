#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h> // for memset
#include "integers_primes.h"

// ===
// ===
// === Largest prime factor
// ===

/* Calculate largest prime factor of n (uint64_t)
   (v1 available in occisn/c-utils GitHub repository)*/
uint64_t largest_prime_factor__uint64(uint64_t n) {
  uint64_t largest = 0;

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
    }
    else {
      i += 6;
    }
  }

  // If n is still > 1, it is prime
  if (n > 1)
    largest = n;

  return largest;
}

// ===
// ===
// === Prime factorization
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
 *    uint64_t *factors = factorize__uint64(n, &count, false);
 *    if (factors == NULL) {
 *       printf("Problem in factorization\n");
 *       return EXIT_FAILURE;
 *   } else {
 *      printf("Prime factors of %llu:\n", (unsigned long long)n);
 *      for (size_t i = 0; i < count; i++) {
 *      printf("%llu\n", (unsigned long long)factors[i]);
 *  }
 */
uint64_t *factorize__uint64(uint64_t n, size_t *count_out, bool multiplicity) {
  *count_out = 0;
  if (n < 2) return NULL;

  size_t cap = 8;
  uint64_t *factors = malloc(cap * sizeof(uint64_t));
  if (!factors) return NULL;

#define PUSH_FACTOR(p)                                          \
  do {                                                          \
    if (*count_out == cap) {                                    \
      cap *= 2;                                                 \
      uint64_t *tmp = realloc(factors, cap * sizeof(uint64_t)); \
      if (!tmp) goto failure;                                   \
      factors = tmp;                                            \
    }                                                           \
    factors[(*count_out)++] = (p);                              \
  } while(0)

  // (1) factor out 2
  if (multiplicity) {
    while ((n & 1ULL) == 0) {
      PUSH_FACTOR(2);
      n >>= 1;
    }
  } else if ((n & 1ULL) == 0) {
    PUSH_FACTOR(2);
    while ((n & 1ULL) == 0) n >>= 1;
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
      while (n % p == 0) n /= p;
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

int SHOW__factorize__uint64(void) {
  // const uint64_t n = 18446744073709551615ULL;  // 2^64 - 1
  // const uint64_t n = 9223372036854775808ULL; // 2^63
  const uint64_t n = 614889782588491410ULL; // 64-bit inteeger with the most different prime factors
  // const uint64_t n = 18446744073709551557ULL; // largest 64-bit prime
  size_t count;

  uint64_t *factors = factorize__uint64(n, &count, true);

  if (factors == NULL) {
    printf("Problem in factorization\n");
    return EXIT_FAILURE;
  } else {
    printf("%zu prime factor(s) of %llu:\n", count, (unsigned long long)n);
    for (size_t i = 0; i < count; i++) {
      printf("%" PRIu64 "\n", factors[i]);
    }
  }
  free(factors);
  return EXIT_SUCCESS;
}

// ===
// ===
// === Primality test
// ===

/**
 * Checks whether an integer is prime
 *
 * @param n        The integer to test
 * @return true/false
 *
 * Example usage:
 * @code
 *    const uint64_t n = 17ULL;
 *    printf("%" PRIu64 " is %s\n", n, is_prime__uint64(n) ? "prime" : "not prime");
 */
bool is_prime__uint64(uint64_t n) {
  if (n < 2) return false;       // 0 and 1 are not prime
  if (n <= 3) return true;       // 2 and 3 are prime
  if ((n % 2) == 0 || (n % 3) == 0) return false;

  // Test divisors of the form 6k ± 1 up to sqrt(n)
  uint64_t limit = (uint64_t)sqrtl((long double)n);
  for (uint64_t i = 5; i <= limit; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0)
      return false;
  }
  return true;
}

int SHOW__is_prime__uint64(void) {
  uint64_t numbers[] = {2, 3, 4, 17, 19, 20, 97, 18446744073709551557ULL};
  for (size_t i = 0; i < sizeof(numbers)/sizeof(numbers[0]); i++) {
    uint64_t n = numbers[i];
    printf("%" PRIu64 " is %s\n", n, is_prime__uint64(n) ? "prime" : "not prime");
  }
  return EXIT_SUCCESS;
}

// ===
// ===
// === Sieve of Eratosthenes (two versions)
// ===

/**
 * Computes the Sieve of Eratosthenes up to n (exclusive)
 * and counts the number of primes.
 *
 * @param n         Upper limit (exclusive)
 * @param prime_count_out Pointer to size_t to store the number of primes found
 * @return Pointer to dynamically allocated bool array where:
 *         is_prime[i] == true if i is prime, false otherwise.
 *         Returns NULL if n < 2 or memory allocation fails.
 *         Caller is responsible for freeing the array.
 */
bool *sieve_eratosthenes__simple__uint64(uint64_t n, size_t *prime_count_out) {
  *prime_count_out = 0;
  if (n < 2) return NULL;

  bool *is_prime = malloc(n * sizeof(bool));
  if (!is_prime) return NULL;

  for (uint64_t i = 0; i < n; i++) is_prime[i] = true;
  is_prime[0] = is_prime[1] = false;

  uint64_t limit = (uint64_t)sqrtl((long double)n);
  for (uint64_t p = 2; p <= limit; p++) {
    if (is_prime[p]) {
      for (uint64_t multiple = p * p; multiple < n; multiple += p) {
        is_prime[multiple] = false;
      }
    }
  }

  // Count the primes
  size_t count = 0;
  for (uint64_t i = 2; i < n; i++) {
    if (is_prime[i]) count++;
  }

  *prime_count_out = count;
  return is_prime;
}

/* List of primes below n */
int SHOW_1__sieve_eratosthenes__simple__uint64(void) {
  const uint64_t n = 100;
  size_t prime_count;
  bool *is_prime = sieve_eratosthenes__simple__uint64(n, &prime_count);

  if (is_prime == NULL) {
    printf("Memory allocation failed or n < 2\n");
    return EXIT_FAILURE;
  }

  printf("Primes below %" PRIu64 " (%zu primes):\n", n, prime_count);
  for (uint64_t i = 2; i < n; i++) {
    if (is_prime[i]) printf("%" PRIu64 " ", i);
  }
  printf("\n");

  free(is_prime);
  return EXIT_SUCCESS;
}

/* The n-th prime */
int SHOW_2__sieve_eratosthenes__simple__uint64(void) {

  const uint64_t k = 100000000; // 100 M
  // 15; // result should be 47
  
  uint64_t n = (k >= 6) ? k * (log(k) + log(log(k))) : 15;
  size_t prime_count;
  bool *is_prime = sieve_eratosthenes__simple__uint64(n, &prime_count);

  if (is_prime == NULL) {
    printf("Memory allocation failed or n < 2\n");
    goto failure;
  }

  if (prime_count < k) {
    printf("Sieve is not big enough.\n");
    goto failure;
  }
  
  uint64_t count = 0;
  size_t i = 0;
  for (i = 0; i < n; i++) {
    if (is_prime[i]) {
      count++;
      if (count == k) break;
    }
  }
  if (count < k) {
    printf("count < k\n");
    goto failure;
  }
  uint64_t nth_prime = i;  
    
  printf("%" PRIu64 "-th prime is %" PRIu64 "\n", k, nth_prime);
    
  free(is_prime);
  return EXIT_SUCCESS;

 failure:
  free(is_prime);
  return EXIT_FAILURE;
  
}


/**
 * Computes the Sieve of Eratosthenes up to n (exclusive) using a bit array.
 * Only odd numbers are stored. The prime 2 is handled separately.
 *
 * @param n                 Upper limit (exclusive)
 * @param prime_count_out   Pointer to size_t to store the number of primes found
 * @param array_size_out Pointer to size_t to store the size of the array
 * @return Pointer to dynamically allocated bit array representing odd numbers:
 *         bit k == 1 means (2*k + 3) is prime.
 *         Returns NULL if n < 2 or allocation fails.
 *         Caller is responsible for freeing the array.
 */
uint8_t *sieve_eratosthenes__odd_bit__uint64(uint64_t n, size_t *prime_count_out, size_t *array_size_out) {
  *prime_count_out = 0;
  if (n < 2) return NULL;

  if (n == 2) {
    *prime_count_out = 1;
    return NULL; // no odd numbers to store
  }

  uint64_t odd_count = (n - 3) / 2 + 1; // number of odd numbers >=3 and < n
  size_t byte_count = (odd_count + 7) / 8;

  uint8_t *bits = malloc(byte_count);
  if (!bits) return NULL;

  memset(bits, 0xFF, byte_count); // set all bits to 1 (prime)
    
  uint64_t limit = (uint64_t)sqrtl((long double)n);
  for (uint64_t i = 0; 2*i + 3 <= limit; i++) {
    if (bits[i >> 3] & (1 << (i & 7))) {
      uint64_t p = 2*i + 3;
      uint64_t start = (p*p - 3) / 2; // index in bit array
      for (uint64_t j = start; j < odd_count; j += p) {
        bits[j >> 3] &= ~(1 << (j & 7)); // mark as composite
      }
    }
  }

  // Count primes
  size_t count = 1; // count 2
  for (uint64_t i = 0; i < odd_count; i++) {
    if (bits[i >> 3] & (1 << (i & 7))) count++;
  }

  *prime_count_out = count;
  *array_size_out = odd_count;
  return bits;
}

/* List of primes below n */
int SHOW_1__sieve_eratosthenes__odd_bit__uint64(void) {
  const uint64_t n = 1000;
    
  size_t prime_count;
  size_t array_size;
  uint8_t *bits = sieve_eratosthenes__odd_bit__uint64(n, &prime_count, &array_size);
  if (bits == NULL) {
    printf("Construction of sieve failed.\n");
    return EXIT_FAILURE;
  }

  printf("Primes below %llu (%zu primes):\n", (unsigned long long)n, prime_count);
  printf("2 "); // handle prime 2 separately
  for (uint64_t i = 3; i < n; i += 2) {

    bool is_prime;
    if (i == 2) is_prime = true;
    if (i < 2 || (i & 1) == 0) is_prime = false;
    uint64_t idx = (i - 3) / 2;
    is_prime = bits[idx >> 3] & (1 << (idx & 7));
        
    if (is_prime) {
      printf("%llu ", (unsigned long long)i);
    }
  }
  printf("\n");

  free(bits);
  return 0;
}

/* The n-th prime */
int SHOW_2__sieve_eratosthenes__odd_bit__uint64(void) {

  const uint64_t n = 100000000; // 100 M

  // Initial upper bound estimate for n-th prime
  double estimate = (n >= 6) ? n * (log(n) + log(log(n))) : 15;
  uint64_t limit = (uint64_t)estimate + 1;
  
  size_t prime_count;
  size_t array_size;
  uint8_t *bits = sieve_eratosthenes__odd_bit__uint64(limit, &prime_count, &array_size);
  if (bits == NULL) {
    printf("Construction of sieve failed.\n");
    return EXIT_FAILURE;
  }

  if (prime_count < n) {
    printf("Sieve is not big enough.\n");
    goto failure;
  }

  uint64_t nth_prime;
 
  if (n == 1) {
    nth_prime = 2;
  } else {

    size_t count = 1; // count 2
    size_t i = 0;
    for (i = 0; i < array_size; i++) {
      if (bits[i >> 3] & (1 << (i & 7))) count++;
      if (count == n) break;
    }

    if (count < n) {
      printf("count < n\n");
      goto failure;
    }

    nth_prime = 2*i+3;
    
  }

  printf("%" PRIu64 "-th prime is %" PRIu64 "\n", n, nth_prime);
  free(bits);
  return EXIT_SUCCESS;

 failure:
  free(bits);
  return EXIT_FAILURE;
}

// ===
// ===
// === List of primes below n
// ===

/**
 * Computes the list of primes below n
 *
 * @param n         Upper limit (exclusive)
 * @param nb_primes Number of primes identified
 * @return Pointer to dynamically allocated uint64_t array where:
 *         Returns NULL if n < 2 or memory allocation fails.
 *         Caller is responsible for freeing the array.
 */
uint64_t *list_of_primes_below__uint64(uint64_t n, size_t *nb_primes) {

  *nb_primes = 0;
  size_t prime_count;
  size_t array_size;
  uint8_t *bits = sieve_eratosthenes__odd_bit__uint64(n, &prime_count, &array_size);
  if (bits == NULL) {
    printf("Construction of sieve failed.\n");
    return NULL;
  }
  *nb_primes = prime_count;

  uint64_t *primes = malloc(n * sizeof(uint64_t));
  if (!primes) {
    printf("Could not allocate memory for primes\n");
    goto failure;
  }
  
  primes[0] = 2;
  size_t count = 1;

  for (uint64_t i = 3; i < n; i += 2) {

    bool is_prime;
    if (i == 2) is_prime = true;
    if (i < 2 || (i & 1) == 0) is_prime = false;
    uint64_t idx = (i - 3) / 2;
    is_prime = bits[idx >> 3] & (1 << (idx & 7));
        
    if (is_prime) {
      primes[count++] = 2*idx+3;
    }
  }

  if (count != prime_count) {
    printf("count != prime_count\n");
    goto failure;
  }
  
  free(bits);
  return primes;

 failure:
  free(bits);
  return NULL;
}

int SHOW__list_of_primes_below__uint64()
{
  // const uint64_t n = 100; // result = 25
  const uint64_t n = 1000000; // 1 M --> result = 78498 
  
  size_t nb_primes = 0;
  uint64_t *primes = list_of_primes_below__uint64(n, &nb_primes);
  if (primes == NULL) {
    printf("Primes array is NULL.\n");
    return EXIT_FAILURE;
  }
  printf("Nb of primes below %" PRIu64 " = %zu:\n", n, nb_primes);
  for (size_t i=0; i<nb_primes; i++) {
    printf("   %" PRIu64 "\n", primes[i]);
  }
  printf("Nb of primes below %" PRIu64 " = %zu:\n", n, nb_primes);
  
  free(primes);
  return EXIT_SUCCESS;
}


// ===
// ===
// === n-th prime
// ===

/**
 * Returns n-th prime
 *
 * @param n   
 * @return n-th prime or 0 if failure
 */
uint64_t nth_prime__uint64(uint64_t n) {

  // Initial upper bound estimate for n-th prime
  double estimate = (n >= 6) ? n * (log(n) + log(log(n))) : 15;
  uint64_t limit = (uint64_t)estimate + 1;
  
  size_t prime_count;
  size_t array_size;
  uint8_t *bits = sieve_eratosthenes__odd_bit__uint64(limit, &prime_count, &array_size);
  if (bits == NULL) {
    printf("Construction of sieve failed.\n");
    return EXIT_FAILURE;
  }

  if (prime_count < n) {
    printf("Sieve is not big enough.\n");
    goto failure;
  }

  uint64_t nth_prime;
 
  if (n == 1) {
    nth_prime = 2;
  } else {

    size_t count = 1; // count 2
    size_t i = 0;
    for (i = 0; i < array_size; i++) {
      if (bits[i >> 3] & (1 << (i & 7))) count++;
      if (count == n) break;
    }

    if (count < n) {
      printf("count < n\n");
      goto failure;
    }

    nth_prime = 2*i+3;
  }

  free(bits);
  return nth_prime;

 failure:
  free(bits);
  return EXIT_FAILURE;
}

int SHOW__nth_prime__uint64(void)
{
  // const uint64_t n = 15; // result = 47
  const uint64_t n = 100000000; // 1 M --> result = 2,038,074,743
  uint64_t nth_prime = nth_prime__uint64(n);
  if (nth_prime == 0) {
    printf("Problem with nth prime calculation\n");
    return EXIT_FAILURE;
  }
  printf("%" PRIu64 "-th prime is %" PRIu64 "\n", n, nth_prime);
  return EXIT_SUCCESS;
}

// end

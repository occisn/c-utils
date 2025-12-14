#ifndef INTEGERS_PRIMES_H
#define INTEGERS_PRIMES_H

#include <inttypes.h>

uint64_t largest_prime_factor__uint64(uint64_t n);
int SHOW__largest_prime_factor__uint64(void);

uint64_t *factorize__uint64(uint64_t n, size_t *count_out, bool multiplicity);
int SHOW__factorize__uint64(void);

bool is_prime__uint64(uint64_t n);
int SHOW__is_prime__uint64(void);

bool *sieve_eratosthenes__simple__uint64(uint64_t n, size_t *prime_count_out);
int SHOW_1__sieve_eratosthenes__simple__uint64(void);
int SHOW_2__sieve_eratosthenes__simple__uint64(void);

uint8_t *sieve_eratosthenes__odd_bit__uint64(uint64_t n, size_t *prime_count_out, size_t *array_size_out);
int SHOW_1__sieve_eratosthenes__odd_bit__uint64(void);
int SHOW_2__sieve_eratosthenes__odd_bit__uint64(void);

uint64_t *list_of_primes_below__uint64(uint64_t n, size_t *nb_primes);
int SHOW__list_of_primes_below__uint64();

uint64_t nth_prime__uint64(uint64_t n);
int SHOW__nth_prime__uint64();

#endif

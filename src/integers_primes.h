#ifndef INTEGERS_PRIMES_H
#define INTEGERS_PRIMES_H

#include <inttypes.h>
#include <stdbool.h>

uint64_t largest_prime_factor__uint64(uint64_t n);
uint64_t *factorize__uint64(uint64_t n, size_t *count_out, bool multiplicity); 
bool is_prime__uint64(uint64_t n);
bool *sieve_eratosthenes__simple__uint64(uint64_t n, size_t *prime_count_out);
uint8_t *sieve_eratosthenes__odd_bit__uint64(uint64_t n, size_t *prime_count_out, size_t *array_size_out);
uint64_t *list_of_primes_below__uint64(uint64_t n, size_t *nb_primes);
uint64_t nth_prime__uint64(uint64_t n);

#endif

#pragma once

#include <inttypes.h>
#include <stdbool.h>

uint64_t largest_prime_factor_uint64(uint64_t n);
int SHOW_largest_prime_factor_uint64(void);

uint64_t *factorize_uint64(uint64_t n, size_t *count_out, bool multiplicity);
int SHOW_factorize_uint64(void);

bool is_prime_uint64(uint64_t n);
int SHOW_is_prime_uint64(void);

bool *sieve_eratosthenes_uint64(uint64_t n);
int SHOW_sieve_eratosthenes_uint64(void);

uint64_t nth_prime_uint64(uint64_t n);
int SHOW_nth_prime_uint64(void);

// end

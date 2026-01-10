#pragma once

#include <inttypes.h>
#include <stdbool.h>

uint64_t largest_prime_factor_uint64(uint64_t n);
bool SHOW_largest_prime_factor_uint64(void);

uint64_t *factorize_uint64(uint64_t n, size_t *count_out, bool multiplicity);
bool SHOW_factorize_uint64(void);

bool is_prime_uint64(uint64_t n);
bool SHOW_is_prime_uint64(void);

bool *sieve_eratosthenes_uint64(uint64_t n);
bool SHOW_sieve_eratosthenes_uint64(void);

bool nth_prime_uint64(uint64_t n, uint64_t *result);
bool SHOW_nth_prime_uint64(void);

// end

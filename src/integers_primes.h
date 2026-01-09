#pragma once

#include <inttypes.h>

uint64_t largest_prime_factor__uint64(uint64_t n);
int SHOW__largest_prime_factor__uint64(void);

uint64_t *factorize__uint64(uint64_t n, size_t *count_out, bool multiplicity);
int SHOW__factorize__uint64(void);

bool is_prime__uint64(uint64_t n);
int SHOW__is_prime__uint64(void);

bool *sieve_eratosthenes__uint64(uint64_t n);
int SHOW__sieve_eratosthenes__uint64(void);

uint64_t nth_prime__uint64(uint64_t n);
int SHOW__nth_prime__uint64();

// end

#include "integers_primes.h"
#include "unity.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

void test_largest_prime_factor__uint64(void)
{
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, largest_prime_factor__uint64(2), "Largest prime factor of 2 should be 2");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(3, largest_prime_factor__uint64(3), "Largest prime factor of 3 should be 3");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, largest_prime_factor__uint64(5), "Largest prime factor of 5 should be 5");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(7, largest_prime_factor__uint64(7), "Largest prime factor of 7 should be 7");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(11, largest_prime_factor__uint64(11), "Largest prime factor of 11 should be 11");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(13, largest_prime_factor__uint64(13), "Largest prime factor of 13 should be 13");

  TEST_ASSERT_EQUAL_UINT64_MESSAGE(97, largest_prime_factor__uint64(97), "Largest prime factor of prime 97 should be itself");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(101, largest_prime_factor__uint64(101), "Largest prime factor of prime 101 should be itself");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(997, largest_prime_factor__uint64(997), "Largest prime factor of prime 997 should be itself");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(9973, largest_prime_factor__uint64(9973), "Largest prime factor of prime 9973 should be itself");

  TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, largest_prime_factor__uint64(4), "Largest prime factor of 4 (2^2) should be 2");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, largest_prime_factor__uint64(8), "Largest prime factor of 8 (2^3) should be 2");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, largest_prime_factor__uint64(16), "Largest prime factor of 16 (2^4) should be 2");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, largest_prime_factor__uint64(1024), "Largest prime factor of 1024 (2^10) should be 2");

  TEST_ASSERT_EQUAL_UINT64_MESSAGE(3, largest_prime_factor__uint64(9), "Largest prime factor of 9 (3^2) should be 3");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(3, largest_prime_factor__uint64(27), "Largest prime factor of 27 (3^3) should be 3");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(3, largest_prime_factor__uint64(81), "Largest prime factor of 81 (3^4) should be 3");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(3, largest_prime_factor__uint64(243), "Largest prime factor of 243 (3^5) should be 3");

  TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, largest_prime_factor__uint64(25), "Largest prime factor of 25 (5^2) should be 5");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, largest_prime_factor__uint64(125), "Largest prime factor of 125 (5^3) should be 5");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(7, largest_prime_factor__uint64(49), "Largest prime factor of 49 (7^2) should be 7");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(11, largest_prime_factor__uint64(121), "Largest prime factor of 121 (11^2) should be 11");

  TEST_ASSERT_EQUAL_UINT64_MESSAGE(3, largest_prime_factor__uint64(6), "Largest prime factor of 6 (2*3) should be 3");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, largest_prime_factor__uint64(10), "Largest prime factor of 10 (2*5) should be 5");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(7, largest_prime_factor__uint64(14), "Largest prime factor of 14 (2*7) should be 7");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(7, largest_prime_factor__uint64(21), "Largest prime factor of 21 (3*7) should be 7");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(11, largest_prime_factor__uint64(33), "Largest prime factor of 33 (3*11) should be 11");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(13, largest_prime_factor__uint64(65), "Largest prime factor of 65 (5*13) should be 13");

  TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, largest_prime_factor__uint64(30), "Largest prime factor of 30 (2*3*5) should be 5");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(7, largest_prime_factor__uint64(42), "Largest prime factor of 42 (2*3*7) should be 7");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(11, largest_prime_factor__uint64(66), "Largest prime factor of 66 (2*3*11) should be 11");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(13, largest_prime_factor__uint64(78), "Largest prime factor of 78 (2*3*13) should be 13");

  TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, largest_prime_factor__uint64(100), "Largest prime factor of 100 (2^2*5^2) should be 5");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(7, largest_prime_factor__uint64(196), "Largest prime factor of 196 (2^2*7^2) should be 7");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(11, largest_prime_factor__uint64(242), "Largest prime factor of 242 (2*11^2) should be 11");

  TEST_ASSERT_EQUAL_UINT64_MESSAGE(7, largest_prime_factor__uint64(35), "Largest prime factor of 35 (5*7, both 6k-1) should be 7");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(11, largest_prime_factor__uint64(55), "Largest prime factor of 55 (5*11) should be 11");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(17, largest_prime_factor__uint64(85), "Largest prime factor of 85 (5*17) should be 17");

  TEST_ASSERT_EQUAL_UINT64_MESSAGE(11, largest_prime_factor__uint64(77), "Largest prime factor of 77 (7*11, both 6k+1) should be 11");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(13, largest_prime_factor__uint64(91), "Largest prime factor of 91 (7*13) should be 13");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(19, largest_prime_factor__uint64(133), "Largest prime factor of 133 (7*19) should be 19");

  TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, largest_prime_factor__uint64(15), "Largest prime factor of 15 (3*5, largest is 6k+1) should be 5");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(13, largest_prime_factor__uint64(39), "Largest prime factor of 39 (3*13) should be 13");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(23, largest_prime_factor__uint64(115), "Largest prime factor of 115 (5*23) should be 23");

  TEST_ASSERT_EQUAL_UINT64_MESSAGE(19, largest_prime_factor__uint64(323), "Largest prime factor of 323 (17*19) should be 19");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(13, largest_prime_factor__uint64(325), "Largest prime factor of 325 (5^2*13) should be 13");

  TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, largest_prime_factor__uint64(4), "Largest prime factor of 4 should be 2");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(3, largest_prime_factor__uint64(6), "Largest prime factor of 6 should be 3");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, largest_prime_factor__uint64(8), "Largest prime factor of 8 should be 2");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(3, largest_prime_factor__uint64(9), "Largest prime factor of 9 should be 3");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, largest_prime_factor__uint64(10), "Largest prime factor of 10 should be 5");

  TEST_ASSERT_EQUAL_UINT64_MESSAGE(101, largest_prime_factor__uint64(10100), "Largest prime factor of 10100 (2^2*5^2*101) should be 101");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(127, largest_prime_factor__uint64(1270), "Largest prime factor of 1270 (2*5*127) should be 127");

  TEST_ASSERT_EQUAL_UINT64_MESSAGE(97, largest_prime_factor__uint64(89 * 97), "Largest prime factor of 89*97 should be 97");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(103, largest_prime_factor__uint64(97 * 103), "Largest prime factor of 97*103 should be 103");

  // Test with numbers close to uint64_t limits
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(1000000007ULL, largest_prime_factor__uint64(1000000007ULL), "Large prime 1000000007 should be its own largest prime factor");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(999999937ULL, largest_prime_factor__uint64(2ULL * 999999937ULL), "Largest prime factor of 2*999999937 should be 999999937");

  // These specifically test the 6k-1 and 6k+1 checking logic
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(17, largest_prime_factor__uint64(17 * 2), "Largest prime factor of 17*2 (6k-1 form) should be 17");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(19, largest_prime_factor__uint64(19 * 2), "Largest prime factor of 19*2 (6k+1 form) should be 19");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(23, largest_prime_factor__uint64(23 * 3), "Largest prime factor of 23*3 (6k-1 form) should be 23");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(31, largest_prime_factor__uint64(31 * 5), "Largest prime factor of 31*5 (6k+1 form) should be 31");

  // Numbers where the algorithm needs to iterate through multiple 6k±1 values
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(37, largest_prime_factor__uint64(37 * 2), "Largest prime factor of 37*2 should be 37");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(41, largest_prime_factor__uint64(41 * 3), "Largest prime factor of 41*3 should be 41");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(43, largest_prime_factor__uint64(43 * 5), "Largest prime factor of 43*5 should be 43");
}

void test_factorize__uint64(void)
{
  size_t count;
  uint64_t *factors;

  // Test 1: n < 2 should return NULL
  factors = factorize__uint64(0, &count, false);
  TEST_ASSERT_NULL_MESSAGE(factors, "n=0 should return NULL");

  factors = factorize__uint64(1, &count, false);
  TEST_ASSERT_NULL_MESSAGE(factors, "n=1 should return NULL");

  // Test 2: n = 2 (smallest prime)
  factors = factorize__uint64(2, &count, false);
  TEST_ASSERT_NOT_NULL_MESSAGE(factors, "n=2 should not return NULL");
  TEST_ASSERT_EQUAL_size_t_MESSAGE(1, count, "n=2 should have 1 distinct factor");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, factors[0], "n=2 factor should be 2");
  free(factors);

  // Test 3: n = 4 (2^2) with multiplicity=false
  factors = factorize__uint64(4, &count, false);
  TEST_ASSERT_NOT_NULL_MESSAGE(factors, "n=4 should not return NULL");
  TEST_ASSERT_EQUAL_size_t_MESSAGE(1, count, "n=4 should have 1 distinct factor");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, factors[0], "n=4 distinct factor should be 2");
  free(factors);

  // Test 4: n = 4 (2^2) with multiplicity=true
  factors = factorize__uint64(4, &count, true);
  TEST_ASSERT_NOT_NULL_MESSAGE(factors, "n=4 with multiplicity should not return NULL");
  TEST_ASSERT_EQUAL_size_t_MESSAGE(2, count, "n=4 with multiplicity should have 2 factors");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, factors[0], "n=4 first factor should be 2");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, factors[1], "n=4 second factor should be 2");
  free(factors);

  // Test 5: n = 15 (3 * 5) with multiplicity=false
  factors = factorize__uint64(15, &count, false);
  TEST_ASSERT_NOT_NULL_MESSAGE(factors, "n=15 should not return NULL");
  TEST_ASSERT_EQUAL_size_t_MESSAGE(2, count, "n=15 should have 2 distinct factors");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(3, factors[0], "n=15 first factor should be 3");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, factors[1], "n=15 second factor should be 5");
  free(factors);

  // Test 6: n = 12 (2^2 * 3) with multiplicity=false
  factors = factorize__uint64(12, &count, false);
  TEST_ASSERT_NOT_NULL_MESSAGE(factors, "n=12 should not return NULL");
  TEST_ASSERT_EQUAL_size_t_MESSAGE(2, count, "n=12 should have 2 distinct factors");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, factors[0], "n=12 first distinct factor should be 2");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(3, factors[1], "n=12 second distinct factor should be 3");
  free(factors);

  // Test 7: n = 12 (2^2 * 3) with multiplicity=true
  factors = factorize__uint64(12, &count, true);
  TEST_ASSERT_NOT_NULL_MESSAGE(factors, "n=12 with multiplicity should not return NULL");
  TEST_ASSERT_EQUAL_size_t_MESSAGE(3, count, "n=12 with multiplicity should have 3 factors");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, factors[0], "n=12 factor[0] should be 2");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, factors[1], "n=12 factor[1] should be 2");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(3, factors[2], "n=12 factor[2] should be 3");
  free(factors);

  // Test 8: Prime number n = 17
  factors = factorize__uint64(17, &count, false);
  TEST_ASSERT_NOT_NULL_MESSAGE(factors, "n=17 (prime) should not return NULL");
  TEST_ASSERT_EQUAL_size_t_MESSAGE(1, count, "n=17 (prime) should have 1 factor");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(17, factors[0], "n=17 factor should be 17");
  free(factors);

  // Test 9: Larger composite n = 100 (2^2 * 5^2) with multiplicity=false
  factors = factorize__uint64(100, &count, false);
  TEST_ASSERT_NOT_NULL_MESSAGE(factors, "n=100 should not return NULL");
  TEST_ASSERT_EQUAL_size_t_MESSAGE(2, count, "n=100 should have 2 distinct factors");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, factors[0], "n=100 first distinct factor should be 2");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, factors[1], "n=100 second distinct factor should be 5");
  free(factors);

  // Test 10: Larger composite n = 100 (2^2 * 5^2) with multiplicity=true
  factors = factorize__uint64(100, &count, true);
  TEST_ASSERT_NOT_NULL_MESSAGE(factors, "n=100 with multiplicity should not return NULL");
  TEST_ASSERT_EQUAL_size_t_MESSAGE(4, count, "n=100 with multiplicity should have 4 factors");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, factors[0], "n=100 factor[0] should be 2");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, factors[1], "n=100 factor[1] should be 2");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, factors[2], "n=100 factor[2] should be 5");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, factors[3], "n=100 factor[3] should be 5");
  free(factors);

  // Test 11: Large power of 2: 2^10 = 1024 with multiplicity=true
  factors = factorize__uint64(1024, &count, true);
  TEST_ASSERT_NOT_NULL_MESSAGE(factors, "n=1024 should not return NULL");
  TEST_ASSERT_EQUAL_size_t_MESSAGE(10, count, "n=1024 (2^10) with multiplicity should have 10 factors");
  for (size_t i = 0; i < count; i++) {
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, factors[i], "All factors of 1024 should be 2");
  }
  free(factors);

  // Test 12: Product of first few primes n = 30 (2 * 3 * 5)
  factors = factorize__uint64(30, &count, false);
  TEST_ASSERT_NOT_NULL_MESSAGE(factors, "n=30 should not return NULL");
  TEST_ASSERT_EQUAL_size_t_MESSAGE(3, count, "n=30 should have 3 distinct factors");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, factors[0], "n=30 factor[0] should be 2");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(3, factors[1], "n=30 factor[1] should be 3");
  TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, factors[2], "n=30 factor[2] should be 5");
  free(factors);
}

void test_is_prime__uint64(void)
{
  // Test edge cases: 0 and 1 are not prime
  TEST_ASSERT_FALSE_MESSAGE(is_prime__uint64(0), "0 should not be prime");
  TEST_ASSERT_FALSE_MESSAGE(is_prime__uint64(1), "1 should not be prime");

  // Test small primes
  TEST_ASSERT_TRUE_MESSAGE(is_prime__uint64(2), "2 should be prime");
  TEST_ASSERT_TRUE_MESSAGE(is_prime__uint64(3), "3 should be prime");
  TEST_ASSERT_TRUE_MESSAGE(is_prime__uint64(5), "5 should be prime");
  TEST_ASSERT_TRUE_MESSAGE(is_prime__uint64(7), "7 should be prime");
  TEST_ASSERT_TRUE_MESSAGE(is_prime__uint64(11), "11 should be prime");
  TEST_ASSERT_TRUE_MESSAGE(is_prime__uint64(13), "13 should be prime");

  // Test small composites
  TEST_ASSERT_FALSE_MESSAGE(is_prime__uint64(4), "4 should not be prime (2×2)");
  TEST_ASSERT_FALSE_MESSAGE(is_prime__uint64(6), "6 should not be prime (2×3)");
  TEST_ASSERT_FALSE_MESSAGE(is_prime__uint64(8), "8 should not be prime (2×4)");
  TEST_ASSERT_FALSE_MESSAGE(is_prime__uint64(9), "9 should not be prime (3×3)");
  TEST_ASSERT_FALSE_MESSAGE(is_prime__uint64(10), "10 should not be prime (2×5)");
  TEST_ASSERT_FALSE_MESSAGE(is_prime__uint64(12), "12 should not be prime (2×6)");
  TEST_ASSERT_FALSE_MESSAGE(is_prime__uint64(15), "15 should not be prime (3×5)");

  // Test composites with form 6k±1 (tricky cases)
  TEST_ASSERT_FALSE_MESSAGE(is_prime__uint64(25), "25 should not be prime (5×5)");
  TEST_ASSERT_FALSE_MESSAGE(is_prime__uint64(35), "35 should not be prime (5×7)");
  TEST_ASSERT_FALSE_MESSAGE(is_prime__uint64(49), "49 should not be prime (7×7)");
  TEST_ASSERT_FALSE_MESSAGE(is_prime__uint64(77), "77 should not be prime (7×11)");
  TEST_ASSERT_FALSE_MESSAGE(is_prime__uint64(91), "91 should not be prime (7×13)");

  // Test larger primes
  TEST_ASSERT_TRUE_MESSAGE(is_prime__uint64(17), "17 should be prime");
  TEST_ASSERT_TRUE_MESSAGE(is_prime__uint64(19), "19 should be prime");
  TEST_ASSERT_TRUE_MESSAGE(is_prime__uint64(23), "23 should be prime");
  TEST_ASSERT_TRUE_MESSAGE(is_prime__uint64(29), "29 should be prime");
  TEST_ASSERT_TRUE_MESSAGE(is_prime__uint64(31), "31 should be prime");
  TEST_ASSERT_TRUE_MESSAGE(is_prime__uint64(97), "97 should be prime");
  TEST_ASSERT_TRUE_MESSAGE(is_prime__uint64(101), "101 should be prime");

  // Test three-digit primes and composites
  TEST_ASSERT_TRUE_MESSAGE(is_prime__uint64(997), "997 should be prime");
  TEST_ASSERT_FALSE_MESSAGE(is_prime__uint64(1000), "1000 should not be prime");

  // Test larger numbers
  TEST_ASSERT_TRUE_MESSAGE(is_prime__uint64(7919), "7919 should be prime");
  TEST_ASSERT_FALSE_MESSAGE(is_prime__uint64(7920), "7920 should not be prime");

  // Test even larger primes
  TEST_ASSERT_TRUE_MESSAGE(is_prime__uint64(104729), "104729 should be prime");
  TEST_ASSERT_TRUE_MESSAGE(is_prime__uint64(1299709), "1299709 should be prime");

  // Test very large prime
  TEST_ASSERT_TRUE_MESSAGE(is_prime__uint64(15485863), "15485863 should be prime (millionth prime)");

  // Test large composites
  TEST_ASSERT_FALSE_MESSAGE(is_prime__uint64(1000000), "1000000 should not be prime");
  TEST_ASSERT_FALSE_MESSAGE(is_prime__uint64(15485864), "15485864 should not be prime");
}

#include "unity.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

void test_sieve_eratosthenes__simple__uint64(void)
{
  size_t prime_count;
  bool *sieve;

  // Test: n < 2 should return NULL
  sieve = sieve_eratosthenes__simple__uint64(0, &prime_count);
  TEST_ASSERT_NULL_MESSAGE(sieve, "n=0 should return NULL");
  TEST_ASSERT_EQUAL_UINT_MESSAGE(0, prime_count, "n=0 should have prime_count=0");

  sieve = sieve_eratosthenes__simple__uint64(1, &prime_count);
  TEST_ASSERT_NULL_MESSAGE(sieve, "n=1 should return NULL");
  TEST_ASSERT_EQUAL_UINT_MESSAGE(0, prime_count, "n=1 should have prime_count=0");

  // Test: n=2 should return array with no primes
  sieve = sieve_eratosthenes__simple__uint64(2, &prime_count);
  TEST_ASSERT_NOT_NULL_MESSAGE(sieve, "n=2 should return valid array");
  TEST_ASSERT_EQUAL_UINT_MESSAGE(0, prime_count, "n=2 should have 0 primes");
  TEST_ASSERT_FALSE_MESSAGE(sieve[0], "0 should not be prime");
  TEST_ASSERT_FALSE_MESSAGE(sieve[1], "1 should not be prime");
  free(sieve);

  // Test: n=3 should find one prime (2)
  sieve = sieve_eratosthenes__simple__uint64(3, &prime_count);
  TEST_ASSERT_NOT_NULL_MESSAGE(sieve, "n=3 should return valid array");
  TEST_ASSERT_EQUAL_UINT_MESSAGE(1, prime_count, "n=3 should have 1 prime");
  TEST_ASSERT_TRUE_MESSAGE(sieve[2], "2 should be prime");
  free(sieve);

  // Test: n=10 should find 4 primes (2, 3, 5, 7)
  sieve = sieve_eratosthenes__simple__uint64(10, &prime_count);
  TEST_ASSERT_NOT_NULL_MESSAGE(sieve, "n=10 should return valid array");
  TEST_ASSERT_EQUAL_UINT_MESSAGE(4, prime_count, "n=10 should have 4 primes");
  TEST_ASSERT_TRUE_MESSAGE(sieve[2], "2 should be prime");
  TEST_ASSERT_TRUE_MESSAGE(sieve[3], "3 should be prime");
  TEST_ASSERT_FALSE_MESSAGE(sieve[4], "4 should not be prime");
  TEST_ASSERT_TRUE_MESSAGE(sieve[5], "5 should be prime");
  TEST_ASSERT_FALSE_MESSAGE(sieve[6], "6 should not be prime");
  TEST_ASSERT_TRUE_MESSAGE(sieve[7], "7 should be prime");
  TEST_ASSERT_FALSE_MESSAGE(sieve[8], "8 should not be prime");
  TEST_ASSERT_FALSE_MESSAGE(sieve[9], "9 should not be prime");
  free(sieve);

  // Test: n=30 should find 10 primes (2,3,5,7,11,13,17,19,23,29)
  sieve = sieve_eratosthenes__simple__uint64(30, &prime_count);
  TEST_ASSERT_NOT_NULL_MESSAGE(sieve, "n=30 should return valid array");
  TEST_ASSERT_EQUAL_UINT_MESSAGE(10, prime_count, "n=30 should have 10 primes");
  TEST_ASSERT_TRUE_MESSAGE(sieve[2], "2 should be prime");
  TEST_ASSERT_TRUE_MESSAGE(sieve[11], "11 should be prime");
  TEST_ASSERT_TRUE_MESSAGE(sieve[29], "29 should be prime");
  TEST_ASSERT_FALSE_MESSAGE(sieve[4], "4 should not be prime");
  TEST_ASSERT_FALSE_MESSAGE(sieve[15], "15 should not be prime");
  TEST_ASSERT_FALSE_MESSAGE(sieve[25], "25 should not be prime");
  free(sieve);

  // Test: n=100 should find 25 primes
  sieve = sieve_eratosthenes__simple__uint64(100, &prime_count);
  TEST_ASSERT_NOT_NULL_MESSAGE(sieve, "n=100 should return valid array");
  TEST_ASSERT_EQUAL_UINT_MESSAGE(25, prime_count, "n=100 should have 25 primes");
  TEST_ASSERT_TRUE_MESSAGE(sieve[97], "97 should be prime");
  TEST_ASSERT_FALSE_MESSAGE(sieve[91], "91 should not be prime (7*13)");
  free(sieve);

  // Test: n=1000 should find 168 primes
  sieve = sieve_eratosthenes__simple__uint64(1000, &prime_count);
  TEST_ASSERT_NOT_NULL_MESSAGE(sieve, "n=1000 should return valid array");
  TEST_ASSERT_EQUAL_UINT_MESSAGE(168, prime_count, "n=1000 should have 168 primes");
  TEST_ASSERT_TRUE_MESSAGE(sieve[997], "997 should be prime");
  TEST_ASSERT_FALSE_MESSAGE(sieve[999], "999 should not be prime (27*37)");
  free(sieve);
}

void test_sieve_eratosthenes__odd_bit__uint64(void)
{
  size_t prime_count, array_size;
  uint8_t *bits;

  // Test: n < 2 should return NULL
  bits = sieve_eratosthenes__odd_bit__uint64(0, &prime_count, &array_size);
  TEST_ASSERT_NULL_MESSAGE(bits, "n=0 should return NULL");
  TEST_ASSERT_EQUAL_MESSAGE(0, prime_count, "n=0 should have prime_count=0");
  
  bits = sieve_eratosthenes__odd_bit__uint64(1, &prime_count, &array_size);
  TEST_ASSERT_NULL_MESSAGE(bits, "n=1 should return NULL");
  TEST_ASSERT_EQUAL_MESSAGE(0, prime_count, "n=1 should have prime_count=0");

  // Test: n = 2 (only prime 2 exists, but no odd numbers to store)
  bits = sieve_eratosthenes__odd_bit__uint64(2, &prime_count, &array_size);
  TEST_ASSERT_NULL_MESSAGE(bits, "n=2 should return NULL (no odd numbers)");
  TEST_ASSERT_EQUAL_MESSAGE(1, prime_count, "n=2 should count prime 2");

  // Test: n = 3 (function counts primes 2 and 3)
  bits = sieve_eratosthenes__odd_bit__uint64(3, &prime_count, &array_size);
  TEST_ASSERT_NOT_NULL_MESSAGE(bits, "n=3 should return non-NULL array");
  TEST_ASSERT_EQUAL_MESSAGE(2, prime_count, "n=3 counts primes 2 and 3");
  TEST_ASSERT_EQUAL_MESSAGE(1, array_size, "n=3 should have array_size=1");
  free(bits);

  // Test: n = 10 (primes: 2, 3, 5, 7)
  bits = sieve_eratosthenes__odd_bit__uint64(10, &prime_count, &array_size);
  TEST_ASSERT_NOT_NULL_MESSAGE(bits, "n=10 should return non-NULL array");
  TEST_ASSERT_EQUAL_MESSAGE(4, prime_count, "n=10 should have 4 primes (2,3,5,7)");
  TEST_ASSERT_EQUAL_MESSAGE(4, array_size, "n=10 should have 4 odd numbers (3,5,7,9)");
  
  // Verify: 3 is prime (index 0, value 2*0+3=3)
  TEST_ASSERT_TRUE_MESSAGE(bits[0] & (1 << 0), "3 should be marked as prime");
  // Verify: 5 is prime (index 1, value 2*1+3=5)
  TEST_ASSERT_TRUE_MESSAGE(bits[0] & (1 << 1), "5 should be marked as prime");
  // Verify: 7 is prime (index 2, value 2*2+3=7)
  TEST_ASSERT_TRUE_MESSAGE(bits[0] & (1 << 2), "7 should be marked as prime");
  // Verify: 9 is composite (index 3, value 2*3+3=9)
  TEST_ASSERT_FALSE_MESSAGE(bits[0] & (1 << 3), "9 should be marked as composite");
  free(bits);

  // Test: n = 30 (primes: 2,3,5,7,11,13,17,19,23,29 = 10 primes)
  bits = sieve_eratosthenes__odd_bit__uint64(30, &prime_count, &array_size);
  TEST_ASSERT_NOT_NULL_MESSAGE(bits, "n=30 should return non-NULL array");
  TEST_ASSERT_EQUAL_MESSAGE(10, prime_count, "n=30 should have 10 primes");
  TEST_ASSERT_EQUAL_MESSAGE(14, array_size, "n=30 should have 14 odd numbers (3 to 29)");
  
  // Verify some primes and composites
  // 3 is prime (index 0)
  TEST_ASSERT_TRUE_MESSAGE(bits[0] & (1 << 0), "3 should be prime");
  // 9 is composite (index 3, 2*3+3=9)
  TEST_ASSERT_FALSE_MESSAGE(bits[0] & (1 << 3), "9 should be composite (3*3)");
  // 11 is prime (index 4, 2*4+3=11)
  TEST_ASSERT_TRUE_MESSAGE(bits[0] & (1 << 4), "11 should be prime");
  // 15 is composite (index 6, 2*6+3=15)
  TEST_ASSERT_FALSE_MESSAGE(bits[0] & (1 << 6), "15 should be composite (3*5)");
  // 25 is composite (index 11, 2*11+3=25)
  TEST_ASSERT_FALSE_MESSAGE(bits[11 >> 3] & (1 << (11 & 7)), "25 should be composite (5*5)");
  // 29 is prime (index 13, 2*13+3=29)
  TEST_ASSERT_TRUE_MESSAGE(bits[13 >> 3] & (1 << (13 & 7)), "29 should be prime");
  free(bits);

  // Test: n = 100 (should have 25 primes up to 100)
  bits = sieve_eratosthenes__odd_bit__uint64(100, &prime_count, &array_size);
  TEST_ASSERT_NOT_NULL_MESSAGE(bits, "n=100 should return non-NULL array");
  TEST_ASSERT_EQUAL_MESSAGE(25, prime_count, "n=100 should have 25 primes");
  free(bits);

  // Test: n = 1000 (should have 168 primes up to 1000)
  bits = sieve_eratosthenes__odd_bit__uint64(1000, &prime_count, &array_size);
  TEST_ASSERT_NOT_NULL_MESSAGE(bits, "n=1000 should return non-NULL array");
  TEST_ASSERT_EQUAL_MESSAGE(168, prime_count, "n=1000 should have 168 primes");
  free(bits);
}

void test_list_of_primes_below__uint64(void)
{
    size_t nb_primes;
    uint64_t *primes;

    // Test 3: n = 10 (should return [2, 3, 5, 7])
    primes = list_of_primes_below__uint64(10, &nb_primes);
    if (primes != NULL) {
        TEST_ASSERT_EQUAL_size_t_MESSAGE(4, nb_primes, "n=10 should have 4 primes");
        if (nb_primes >= 4) {
            TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, primes[0], "n=10: primes[0] should be 2");
            TEST_ASSERT_EQUAL_UINT64_MESSAGE(3, primes[1], "n=10: primes[1] should be 3");
            TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, primes[2], "n=10: primes[2] should be 5");
            TEST_ASSERT_EQUAL_UINT64_MESSAGE(7, primes[3], "n=10: primes[3] should be 7");
        }
        free(primes);
    } else {
        TEST_FAIL_MESSAGE("n=10 returned NULL unexpectedly");
    }

    // Test 4: n = 20 (should return [2, 3, 5, 7, 11, 13, 17, 19])
    primes = list_of_primes_below__uint64(20, &nb_primes);
    if (primes != NULL) {
        TEST_ASSERT_EQUAL_size_t_MESSAGE(8, nb_primes, "n=20 should have 8 primes");
        if (nb_primes >= 8) {
            uint64_t expected[] = {2, 3, 5, 7, 11, 13, 17, 19};
            for (size_t i = 0; i < 8; i++) {
                char msg[50];
                snprintf(msg, sizeof(msg), "n=20: primes[%zu] should be %llu", i, (unsigned long long)expected[i]);
                TEST_ASSERT_EQUAL_UINT64_MESSAGE(expected[i], primes[i], msg);
            }
        }
        free(primes);
    } else {
        TEST_FAIL_MESSAGE("n=20 returned NULL unexpectedly");
    }

    // Test 5: n = 100 (verify count)
    primes = list_of_primes_below__uint64(100, &nb_primes);
    if (primes != NULL) {
        TEST_ASSERT_EQUAL_size_t_MESSAGE(25, nb_primes, "n=100 should have 25 primes");
        if (nb_primes > 0) {
            TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, primes[0], "n=100: first prime should be 2");
        }
        if (nb_primes == 25) {
            TEST_ASSERT_EQUAL_UINT64_MESSAGE(97, primes[24], "n=100: last prime should be 97");
        }
        free(primes);
    } else {
        TEST_FAIL_MESSAGE("n=100 returned NULL unexpectedly");
    }
}

void test_nth_prime__uint64(void)
{
    // Test first prime (n=1)
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(2, nth_prime__uint64(1), 
                                     "1st prime should be 2");
    
    // Test first few primes
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(3, nth_prime__uint64(2), 
                                     "2nd prime should be 3");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(5, nth_prime__uint64(3), 
                                     "3rd prime should be 5");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(7, nth_prime__uint64(4), 
                                     "4th prime should be 7");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(11, nth_prime__uint64(5), 
                                     "5th prime should be 11");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(13, nth_prime__uint64(6), 
                                     "6th prime should be 13");
    
    // Test additional cases
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(29, nth_prime__uint64(10), 
                                     "10th prime should be 29");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(97, nth_prime__uint64(25), 
                                     "25th prime should be 97");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(541, nth_prime__uint64(100), 
                                     "100th prime should be 541");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(1223, nth_prime__uint64(200), 
                                     "200th prime should be 1223");
    TEST_ASSERT_EQUAL_UINT64_MESSAGE(7919, nth_prime__uint64(1000), 
                                     "1000th prime should be 7919");
    
}

// end

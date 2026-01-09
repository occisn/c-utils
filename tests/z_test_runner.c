#include "unity.h"

// From test_integers.c
void test_gcd_int(void);
void test_lcm_int(void);
void test_gcd_lcm_relationship(void);

// From test_integers_digits.c
void test_reverse_number_int(void);

// From test_integers_primes.c
void test_largest_prime_factor_uint64(void);
void test_factorize_uint64(void);
void test_is_prime_uint64(void);
void test_sieve_eratosthenes_uint64(void);
void test_nth_prime_uint64(void);

void setUp(void)
{
  //
}

void tearDown(void)
{
  //
}

int main(void)
{
  UNITY_BEGIN();

  // test on 'integers'
  RUN_TEST(test_gcd_int);
  RUN_TEST(test_lcm_int);
  RUN_TEST(test_gcd_lcm_relationship);

  // test on 'integers_digits'
  RUN_TEST(test_reverse_number_int);

  // tests on 'integers_primes'
  RUN_TEST(test_largest_prime_factor_uint64);
  RUN_TEST(test_factorize_uint64);
  RUN_TEST(test_is_prime_uint64);
  RUN_TEST(test_sieve_eratosthenes_uint64);
  RUN_TEST(test_nth_prime_uint64);

  return UNITY_END();
}

// end

#include "unity.h"

// From test_integers.c
void test_gcd__int(void);
void test_lcm__int(void);
void test_gcd_lcm_relationship(void);

// From test_integers_primes.c
void test_largest_prime_factor__uint64(void);
void test_factorize__uint64(void);
void test_is_prime__uint64(void);
void test_sieve_eratosthenes__uint64(void);
void test_nth_prime__uint64(void);

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
  RUN_TEST(test_gcd__int);
  RUN_TEST(test_lcm__int);
  RUN_TEST(test_gcd_lcm_relationship);

  // tests on 'integers_primes'
  RUN_TEST(test_largest_prime_factor__uint64);
  RUN_TEST(test_factorize__uint64);
  RUN_TEST(test_is_prime__uint64);
  RUN_TEST(test_sieve_eratosthenes__uint64);
  RUN_TEST(test_nth_prime__uint64);
  
  return UNITY_END();
}

// end

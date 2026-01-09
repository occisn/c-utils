#include "integers.h"
#include "unity.h"

void test_gcd_int(void)
{
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, gcd_int(7, 13), "GCD of two coprime numbers should be 1");
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, gcd_int(17, 19), "GCD of two prime numbers should be 1");
  TEST_ASSERT_EQUAL_INT_MESSAGE(6, gcd_int(12, 18), "GCD of 12 and 18 should be 6");
  TEST_ASSERT_EQUAL_INT_MESSAGE(4, gcd_int(8, 12), "GCD of 8 and 12 should be 4");
  TEST_ASSERT_EQUAL_INT_MESSAGE(5, gcd_int(15, 25), "GCD of 15 and 25 should be 5");
  TEST_ASSERT_EQUAL_INT_MESSAGE(5, gcd_int(5, 15), "GCD when one number divides the other should be the smaller number");
  TEST_ASSERT_EQUAL_INT_MESSAGE(7, gcd_int(7, 49), "GCD when first number divides second should be the first number");
  TEST_ASSERT_EQUAL_INT_MESSAGE(10, gcd_int(10, 100), "GCD of 10 and 100 should be 10");
  TEST_ASSERT_EQUAL_INT_MESSAGE(5, gcd_int(5, 5), "GCD of identical numbers should be the number itself");
  TEST_ASSERT_EQUAL_INT_MESSAGE(42, gcd_int(42, 42), "GCD of same numbers should equal the number");
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, gcd_int(1, 5), "GCD with 1 should always be 1");
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, gcd_int(100, 1), "GCD with 1 should always be 1 (reversed)");
  TEST_ASSERT_EQUAL_INT_MESSAGE(5, gcd_int(0, 5), "GCD of 0 and n should be n");
  TEST_ASSERT_EQUAL_INT_MESSAGE(10, gcd_int(10, 0), "GCD of n and 0 should be n");
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, gcd_int(0, 0), "GCD of 0 and 0 should be 0");
  TEST_ASSERT_EQUAL_INT_MESSAGE(gcd_int(12, 18), gcd_int(18, 12), "GCD should be commutative");
  TEST_ASSERT_EQUAL_INT_MESSAGE(gcd_int(7, 21), gcd_int(21, 7), "GCD should be commutative (reversed arguments)");
  TEST_ASSERT_EQUAL_INT_MESSAGE(1, gcd_int(1000000007, 1000000009), "GCD of large coprime numbers should be 1");
  TEST_ASSERT_EQUAL_INT_MESSAGE(12345, gcd_int(12345 * 7, 12345 * 11), "GCD of multiples should be the common factor");
  TEST_ASSERT_EQUAL_INT_MESSAGE(4, gcd_int(4, 8), "GCD of 4 and 8 should be 4");
  TEST_ASSERT_EQUAL_INT_MESSAGE(16, gcd_int(16, 32), "GCD of 16 and 32 should be 16");
}

void test_lcm_int(void)
{
  TEST_ASSERT_EQUAL_INT_MESSAGE(21, lcm_int(3, 7), "LCM of two coprime numbers should be their product");
  TEST_ASSERT_EQUAL_INT_MESSAGE(143, lcm_int(11, 13), "LCM of two prime numbers should be their product");
  TEST_ASSERT_EQUAL_INT_MESSAGE(12, lcm_int(4, 6), "LCM of 4 and 6 should be 12");
  TEST_ASSERT_EQUAL_INT_MESSAGE(36, lcm_int(12, 18), "LCM of 12 and 18 should be 36");
  TEST_ASSERT_EQUAL_INT_MESSAGE(60, lcm_int(15, 20), "LCM of 15 and 20 should be 60");
  TEST_ASSERT_EQUAL_INT_MESSAGE(15, lcm_int(5, 15), "LCM when one number divides the other should be the larger number");
  TEST_ASSERT_EQUAL_INT_MESSAGE(49, lcm_int(7, 49), "LCM when first number divides second should be the second number");
  TEST_ASSERT_EQUAL_INT_MESSAGE(100, lcm_int(10, 100), "LCM of 10 and 100 should be 100");
  TEST_ASSERT_EQUAL_INT_MESSAGE(5, lcm_int(5, 5), "LCM of identical numbers should be the number itself");
  TEST_ASSERT_EQUAL_INT_MESSAGE(42, lcm_int(42, 42), "LCM of same numbers should equal the number");
  TEST_ASSERT_EQUAL_INT_MESSAGE(5, lcm_int(1, 5), "LCM with 1 should be the other number");
  TEST_ASSERT_EQUAL_INT_MESSAGE(100, lcm_int(100, 1), "LCM with 1 should be the other number (reversed)");
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, lcm_int(0, 5), "LCM with 0 should be 0");
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, lcm_int(10, 0), "LCM with 0 should be 0 (reversed)");
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, lcm_int(0, 0), "LCM of 0 and 0 should be 0");
  TEST_ASSERT_EQUAL_INT_MESSAGE(lcm_int(12, 18), lcm_int(18, 12), "LCM should be commutative");
  TEST_ASSERT_EQUAL_INT_MESSAGE(lcm_int(7, 21), lcm_int(21, 7), "LCM should be commutative (reversed arguments)");
  TEST_ASSERT_EQUAL_INT_MESSAGE(8, lcm_int(4, 8), "LCM of 4 and 8 should be 8");
  TEST_ASSERT_EQUAL_INT_MESSAGE(32, lcm_int(16, 32), "LCM of 16 and 32 should be 32");

  // Test that the int64_t cast helps prevent overflow
  TEST_ASSERT_EQUAL_INT_MESSAGE(46410, lcm_int(30, 1547), "LCM calculation should handle potential overflow with int64_t cast");
}

void test_gcd_lcm_relationship(void)
{
  // For any two numbers: a * b = gcd(a,b) * lcm(a,b)
  int a = 12;
  int b = 18;
  TEST_ASSERT_EQUAL_INT_MESSAGE(a * b, gcd_int(a, b) * lcm_int(a, b), "a*b = lcm*gcd (1)");

  a = 15;
  b = 25;
  TEST_ASSERT_EQUAL_INT_MESSAGE(a * b, gcd_int(a, b) * lcm_int(a, b), "a*b = lcm*gcd (2)");
}

// end

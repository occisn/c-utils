#include "integers_primes.h"
#include "unity.h"

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

// end

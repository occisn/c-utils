#include "integers.h"
#include <stdint.h>

/**
 * Computes the greatest common divisor (GCD) of two integers using the
 * Euclidean algorithm.
 *
 * The GCD is the largest positive integer that divides both numbers without
 * a remainder. This implementation uses the iterative version of Euclid's
 * algorithm, which repeatedly replaces the larger number with the remainder
 * of dividing the larger by the smaller until one number becomes zero.
 *
 * @param a First integer (should be non-negative)
 * @param b Second integer (should be non-negative)
 *
 * @return The GCD of a and b. Returns a if b is 0, or b if a is 0.
 *
 * @example
 *   gcd__int(12, 15) returns 3
 *
 * (v1 available in occisn/c-utils GitHub repository)
 */
int gcd__int(int a, int b)
{
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

/**
 * Computes the least common multiple (LCM) of two integers.
 *
 * The LCM is the smallest positive integer that is divisible by both a and b.
 * This function uses the relationship: lcm(a, b) = (a × b) / gcd(a, b).
 *
 * The multiplication is performed using int64_t to prevent intermediate overflow,
 * but the final result is cast back to int, which may still overflow for large
 * inputs.
 *
 * @param a First integer (supposed to be positive)
 * @param b Second integer (supposed to be positive)
 *
 * @return The LCM of a and b. Returns 0 if either input is 0.
 *
 * @warning The result may overflow if (a × b) / gcd(a, b) exceeds INT_MAX.
 *          For large inputs, consider using a 64-bit return type.
 *
 * @note If either a or b is 0, the LCM is mathematically undefined, so the
 *       function returns 0 by convention.
 * @note This function depends on gcd__int() to compute the greatest common divisor.
 *
 * @example
 *   lcm__int(12, 18)   returns 36
 *
 * @see gcd__int()
 *
 * (v2 available in occisn/c-utils GitHub repository)
 */
int lcm__int(int a, int b)
{
  if (a == 0 || b == 0)
    return 0;
  return (int)((int64_t)a * b / gcd__int(a, b));
}

// === end

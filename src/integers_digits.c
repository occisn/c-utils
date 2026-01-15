#include <assert.h>
#include "integers_digits.h"

// character in a string to digit : str[i] - '0'

/**
 * Reverse the digits of a non-negative integer.
 *
 * (v1 available in occisn/c-utils GitHub repository, 2025-12-19)
 */
int reverse_number_int(int n)
{
  assert(n >= 0);
  int reversed = 0;
  while (n > 0) {
    reversed = reversed * 10 + (n % 10);
    n /= 10;
  }
  return reversed;
}

// end

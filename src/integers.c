#include <stdint.h>
#include "integers.h"

/**
 * Compute gcd
 *
 * (v1 available in occisn/c-utils GitHub repository)
 */
int gcd_int(int a, int b)
{
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

/**
 * Compute lcm
 *
 * (v2 available in occisn/c-utils GitHub repository)
 */
int lcm_int(int a, int b)
{
  if (a == 0 || b == 0)
    return 0;
  return (int)((int64_t)a * b / gcd_int(a, b));
}

// === end

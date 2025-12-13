#include "integers.h"
#include <stdint.h>

// ===
// ===
// === gcd and lcm
// ===

/* Calculate GCD
   parameters are supposed to be positive
   (v1 available in occisn/c-utils GitHub repository)*/
int gcd__int(int a, int b)
{
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }
  return a;
}

/* Function to calculate LCM
   parameters are supposed to be positive
   Requires gcd__int()
 (v2 available in occisn/c-utils GitHub repository) */
int lcm__int(int a, int b)
{
  if (a == 0 || b == 0)
    return 0;
  return (int)((int64_t)a * b / gcd__int(a, b));
}

// end

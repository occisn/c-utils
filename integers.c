#include <stdio.h>
#include <stdint.h>

/* Calculate GCD
 (v1 available in occisn/c-utils GitHub repository)*/
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/* Calculate LCM
 (v1 available in occisn/c-utils GitHub repository)*/
uint64_t lcm(uint64_t a, uint64_t b) {
    return (a * b) / gcd(a, b);  
}

int main(void) {
  // nothing
  return 0;
}

// end

#include <stdint.h>

/* Calculate GCD
 (v1 available in occisn/c-utils GitHub repository)*/
int gcd__int(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/* Calculate LCM
   Requires gcd__int()
 (v1 available in occisn/c-utils GitHub repository)*/
int lcm__int(int a, int b) {
    return (a * b) / gcd__int(a, b);  
}

/* Calculate largest prime factor of n (uint64_t)
 (v1 available in occisn/c-utils GitHub repository)*/
uint64_t largest_prime_factor__uint64(uint64_t n) {
    uint64_t largest = 0;

    // Remove all factors of 2
    while (n % 2 == 0) {
        largest = 2;
        n /= 2;
    }

    // Remove all factors of 3
    while (n % 3 == 0) {
        largest = 3;
        n /= 3;
    }

    // Now n is odd and not divisible by 3.
    // Test divisors of the form 6k-1 and 6k+1.
    uint64_t i = 5;
    while (i * i <= n) {

        // Check i = 6k - 1
        if (n % i == 0) {
            largest = i;
            n /= i;
        }
        // Check i+2 = 6k + 1
        else if (n % (i + 2) == 0) {
            largest = i + 2;
            n /= (i + 2);
        }
        else {
            i += 6;
        }
    }

    // If n is still > 1, it is prime
    if (n > 1)
        largest = n;

    return largest;
}

int main(void) {
  // nothing
  return 0;
}

// end

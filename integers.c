#include <stdio.h>

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

}

int main(void) {
  // nothing
  return 0;
}

// end

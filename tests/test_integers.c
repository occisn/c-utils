#include "../unity/unity.h"
#include "../src/integers.h"

void setUp(void) {
    // runs before each test
}

void tearDown(void) {
    // runs after each test
}

void test_gcd__int(void) {
    TEST_ASSERT_EQUAL_INT(5, gcd__int(10,15));
}


int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_gcd__int);
    return UNITY_END();
}

// end

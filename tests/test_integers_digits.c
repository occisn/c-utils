#include "integers_digits.h"
#include "unity.h"

void test_reverse_number(void)
{
    /* Single digit */
    TEST_ASSERT_EQUAL_INT(7, reverse_number(7));

    /* Multiple digits */
    TEST_ASSERT_EQUAL_INT(321, reverse_number(123));

    /* Trailing zeros */
    TEST_ASSERT_EQUAL_INT(21, reverse_number(1200));

    /* Palindrome number */
    TEST_ASSERT_EQUAL_INT(1221, reverse_number(1221));

    /* Zero input */
    TEST_ASSERT_EQUAL_INT(0, reverse_number(0));
}

// nd

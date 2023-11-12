#include "numbers_tests.h"

TestSuite numbers_suite {"Numbers TS"};

void numbers_tests() {
    TEST_CASE(numbers_suite, "Testing the construction of a Number", [] {
        auto natural = Natural(1);
        assertEquals(natural.number(), 1u);

        auto integer = Integer(7);
        assertEquals(integer.number(), 7);
        auto from_natural = Integer(natural);
        assertEquals(from_natural.number(), 1);

        auto rational = Rational(5, 2);
        assertEquals(rational.numerator().number(), 5);
        assertEquals(rational.denominator().number(), 2); // TODO simplify these when
        // the equality operators are implemented
    });

    TEST_CASE(numbers_suite, "Arithmetic operations with Naturals", [] {
        auto one_natural = Natural(5);
        auto other_natural = Natural(2);

        assertEquals((one_natural + other_natural).number(), 7u);
        assertEquals((one_natural - other_natural).number(), 3u);
        assertEquals((one_natural * other_natural).number(), 10u);
        // TODO division
    });

    TEST_CASE(numbers_suite, "Arithmetic operations with Integers", [] {
        auto one_integer = Integer(10);
        auto other_integer = Integer(20);

        assertEquals((one_integer + other_integer).number(), 30);
        assertEquals((one_integer - other_integer).number(), -10);
        assertEquals((one_integer * other_integer).number(), 200);
        // TODO division
    });
}

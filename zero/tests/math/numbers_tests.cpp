#include "numbers_tests.h"

using namespace zero::math;

TestSuite numbers_suite {"Numbers TS"};

/// Compile time tests for numbers
static_assert(Number<Natural>);
static_assert(Number<Integer>);
static_assert(Number<Rational>);
static_assert(!Number<std::string>);

void numbers_tests() {
    TEST_CASE(numbers_suite, "Testing the construction of a Number", [] {
        auto natural = Natural(1);
        assertEquals(natural.number(), 1u);

        auto integer = Integer(7);
        assertEquals(integer, 7);
        auto from_natural = Integer(natural);
        assertEquals(from_natural, 1);

        auto rational = Rational(5, 2);
        assertEquals(rational.numerator(), 5);
        assertEquals(rational.denominator(), 2);
    });

    TEST_CASE(numbers_suite, "Arithmetic operations with Naturals", [] {
        auto one_natural = Natural(5);
        auto other_natural = Natural(2);

        assertEquals(one_natural + other_natural, 7u);
        assertEquals(one_natural - other_natural, 3u);
        assertEquals(one_natural * other_natural, 10u);
        // TODO division
    });

    TEST_CASE(numbers_suite, "Arithmetic operations with Integers", [] {
        auto one_integer = Integer(10);
        auto other_integer = Integer(20);

        assertEquals(one_integer + other_integer, 30);
        assertEquals(one_integer - other_integer, -10);
        assertEquals(one_integer * other_integer, 200);
        // TODO division
    });
}

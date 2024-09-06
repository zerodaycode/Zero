#include "numbers_tests.h"

using namespace zero::math;

TestSuite numbers_suite {"Numbers TS"};

/// Compile time tests for numbers
static_assert(Number<Natural>);
static_assert(Number<Integer>);
static_assert(Number<Rational>);
static_assert(!Number<std::string>);

void numbers_tests() {
    TEST_CASE(numbers_suite, "Testing the Numbers types construction", [] {
        auto natural = Natural(1);
        assertEquals(1u, natural.number());

        auto integer = Integer(7);
        assertEquals(7, integer);
        auto from_natural = Integer(natural);
        assertEquals(1, from_natural);

        auto rational = Rational(5, 2);
        assertEquals(5, rational.numerator());
        assertEquals(2, rational.denominator());
    });

    TEST_CASE(numbers_suite, "Arithmetic operations with Naturals", [] {
        auto one_natural = Natural(5);
        auto other_natural = Natural(2);

        assertEquals(7u, one_natural + other_natural);
        assertEquals(3u, one_natural - other_natural);
        assertEquals(10u, one_natural * other_natural);
        // TODO division
    });

    TEST_CASE(numbers_suite, "Arithmetic operations with Integers", [] {
        auto one_integer = Integer(10);
        auto other_integer = Integer(20);

        assertEquals(30, one_integer + other_integer);
        assertEquals(-10, one_integer - other_integer);
        assertEquals(200, one_integer * other_integer);
        // TODO division
    });

    TEST_CASE(numbers_suite, "Arithmetic operations with Rationals (like fractions)", [] {
        auto one_rational = Rational(8, 2);
        auto other_rational = Rational(4, 2);

        auto rational_addition = one_rational + other_rational;
        assertEquals(Rational(12, 2), rational_addition);

        auto rational_subtraction = one_rational - other_rational;
        assertEquals(Rational(4, 2), rational_subtraction);

        auto rational_multiplication = one_rational * other_rational;
        assertEquals(Rational(32, 4), rational_multiplication);
    });

    TEST_CASE(numbers_suite, "Arithmetic operations with Rationals (unlike fractions)", [] {
        auto one_rational = Rational(3, 2);
        auto other_rational = Rational(5, 4);

        auto rational_addition = one_rational + other_rational;
        assertEquals(Rational(11, 4), rational_addition);

        auto rational_subtraction = one_rational - other_rational;
        assertEquals(Rational(1, 4), rational_subtraction);

        auto rational_multiplication = one_rational * other_rational;
        assertEquals(Rational(15, 8), rational_multiplication);

        auto integer_times_rational = Integer(3) * other_rational;
        assertEquals(Rational(15, 4), integer_times_rational);
        
        auto rational_times_integer = one_rational * Integer(7);
        assertEquals(Rational(21, 2), rational_times_integer);
    });
}

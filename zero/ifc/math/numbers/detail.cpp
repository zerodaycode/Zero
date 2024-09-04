module math:numbers.detail;

import std;
import math.ops;
import math.symbols;

import :numbers.general;
import :numbers.naturals;
import :numbers.integers;
import :numbers.rationals;

using namespace zero::math;

/// Private helper function to perform the common logic for addition and subtraction
/// @param rhs The rational number to be added or subtracted.
/// \param sign
/// @return The sum of the two rational numbers.
///
/// This method handles both like and unlike fractions. If the denominators of
/// the two fractions are equal, it directly adds the numerators. Otherwise, it
/// finds the least common multiple (LCM) of the denominators and scales the
/// numerators to have the LCM as the common denominator before adding.
// TODO: move to the future impl module
[[nodiscard]] Rational sum_or_subtract(const Rational& lhs, const Rational& rhs, int sign) {
    if (lhs == rhs) {  // Like fractions
        return {static_cast<int>(lhs.numerator()) + sign * static_cast<int>(rhs.numerator()),
            static_cast<int>(lhs.denominator())
        };
    } else {  // Unlike fractions
        const int lhs_numerator     = static_cast<int>(lhs.numerator());
        const int rhs_numerator     = sign * static_cast<int>(rhs.numerator());
        const int lhs_denominator   = static_cast<int>(lhs.denominator());
        const int rhs_denominator   = static_cast<int>(rhs.denominator());

        // Get their lcd by finding their lcm
        const auto lcd = zero::math::lcm(lhs_denominator, rhs_denominator);

        // Scale numerators to have the common denominator (lcm)
        const int numerator = (lhs_numerator * (lcd / lhs_denominator)) + (rhs_numerator * (lcd / rhs_denominator));

        return {numerator, lcd};
    }
}
            /*++++++++ Operator overloads implementations ++++++++++*/
/*+++++++++++++++++ Integers +++++++++++++++++*/

/* // Arithmetic
[[nodiscard]] Rational Integer::operator*(const Rational rhs) const noexcept {
    return {_number * rhs.numerator().number(), rhs.denominator().number()};
}
[[nodiscard]] Rational Integer::operator/(const Integer rhs) const noexcept { // TODO: wrong impl, this always should return a Rational?
    return {static_cast<signed int>(_number), static_cast<signed int>(rhs.number())};
} */
// Equality

            /*+++++++++++++++++ Rationals +++++++++++++++++*/
// Arithmetic

// Addition operator
[[nodiscard]] Rational Rational::operator+(const Rational rhs) const {
    return sum_or_subtract(*this, rhs, 1);
}
// Subtraction operator
[[nodiscard]] Rational Rational::operator-(const Rational rhs) const {
    return sum_or_subtract(*this, rhs, -1);
}
/* [[nodiscard]] Rational Rational::operator*(const Integer rhs) const {
    return Rational(_numerator * rhs, _denominator);
} */
[[nodiscard]] Rational Rational::operator*(const Rational rhs) const {
    return Rational(
        _numerator * rhs.numerator(), _denominator * rhs.denominator()
    );
}


// Equality

// TODO should we check that 4/2 is the same as 2/1 right? Or we should maintain the difference and explicitly
// say that 4/2 aren't the same Rational number as 2/1?
[[nodiscard]] bool Rational::operator==(const Rational rhs) const noexcept {
    return _numerator == rhs.numerator() && _denominator == rhs.denominator();
}



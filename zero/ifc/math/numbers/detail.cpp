module math:numbers.detail;

import std;
import math.ops;
import math.symbols;

import :numbers.general;
import :numbers.naturals;
import :numbers.integers;
import :numbers.rationals;

using namespace zero::math;

            /*++++++++ Operator overloads implementations ++++++++++*/

/*+++++++++++++++++ Naturals +++++++++++++++++*/
// Arithmetic
/* [[nodiscard]] Natural Natural::operator+(const Natural rhs) const noexcept {
    return Natural(_number + rhs.number());
}
/// TODO: should we do something about the values < 1?
/// Definetly yes, and now that we have a common base via CRTP,
/// we can override the impl on naturals to provide custom behaviour
///
[[nodiscard]] Natural Natural::operator-(const Natural rhs) const noexcept  {
    return Natural(_number - rhs.number());
}

[[nodiscard]] Natural Natural::operator*(const Natural rhs) const noexcept {
    return Natural(_number * rhs.number());
}
[[nodiscard]] Rational Natural::operator/(const Natural rhs) const noexcept {
    return {static_cast<signed int>(_number), static_cast<signed int>(rhs.number())};
} */
// Equality
/* [[nodiscard]] bool Natural::operator==(const Natural rhs) const noexcept {
    return _number == rhs.number();
}
[[nodiscard]] bool Natural::operator==(const unsigned int rhs) const noexcept {
    return _number == rhs;
} */

/*+++++++++++++++++ Integers +++++++++++++++++*/

// Arithmetic
[[nodiscard]] Integer Integer::operator+(const Integer rhs) const noexcept {
    return Integer(_number + rhs.number());
}
[[nodiscard]] Integer Integer::operator-(const Integer rhs) const noexcept {
    return Integer(_number - rhs.number());
}
[[nodiscard]] Integer Integer::operator*(const Integer rhs) const noexcept {
    return Integer(_number * rhs.number());
}
[[nodiscard]] Rational Integer::operator*(const Rational rhs) const noexcept {
    return {_number * rhs.numerator().number(), rhs.denominator().number()};
}
[[nodiscard]] Rational Integer::operator/(const Integer rhs) const noexcept { // TODO: wrong impl, this always should return a Rational?
    return {static_cast<signed int>(_number), static_cast<signed int>(rhs.number())};
}
// Equality
[[nodiscard]] bool Integer::operator==(const Integer rhs) const noexcept {
    return _number == rhs.number();
}
[[nodiscard]] bool Integer::operator==(const int rhs) const noexcept {
    return _number == rhs;
}

            /*+++++++++++++++++ Rationals +++++++++++++++++*/
// Arithmetic

// Addition operator
[[nodiscard]] Rational Rational::operator+(const Rational rhs) const {
    return this->sum_or_subtract(rhs, 1);
}
// Subtraction operator
[[nodiscard]] Rational Rational::operator-(const Rational rhs) const {
    return this->sum_or_subtract(rhs, -1);
}
[[nodiscard]] Rational Rational::operator*(const Integer rhs) const {
    return Rational(_numerator * rhs, _denominator);
}
[[nodiscard]] Rational Rational::operator*(const Rational rhs) const {
    return Rational(
        _numerator * rhs.numerator(), _denominator * rhs.denominator()
    );
}

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
[[nodiscard]] Rational Rational::sum_or_subtract(const Rational& rhs, int sign) const {
    if (_denominator == rhs.denominator()) {  // Like fractions
        return {static_cast<int>(_numerator) + sign * static_cast<int>(rhs.numerator()),
            static_cast<int>(_denominator)
        };
    } else {  // Unlike fractions
        const int lhs_numerator     = static_cast<int>(_numerator);
        const int rhs_numerator     = sign * static_cast<int>(rhs._numerator);
        const int lhs_denominator   = static_cast<int>(_denominator);
        const int rhs_denominator   = static_cast<int>(rhs._denominator);

        // Get their lcd by finding their lcm
        const auto lcd = zero::math::lcm(_denominator.number(), rhs.denominator().number());

        // Scale numerators to have the common denominator (lcm)
        const int numerator = (lhs_numerator * (lcd / lhs_denominator)) + (rhs_numerator * (lcd / rhs_denominator));

        return {numerator, lcd};
    }
}

// Equality

// TODO should we check that 4/2 is the same as 2/1 right? Or we should maintain the difference and explicitly
// say that 4/2 aren't the same Rational number as 2/1?
[[nodiscard]] bool Rational::operator==(const Rational rhs) const noexcept {
    return _numerator == rhs.numerator() && _denominator == rhs.denominator();
}

export module math:numbers.rationals;

import std;
import math.ops;
import math.symbols;

import :general;
import :numbers.general;
import :numbers.naturals;
import :numbers.integers;

export namespace zero::math {
    /// @brief A type that represents rational numbers of the form: ℚ = {a, b ∈ ℤ, b ≠ 0}
    ///
    /// The Rational class encapsulates a fraction with an integer numerator and denominator.
    /// Rational numbers are represented as ratios of integers, where the numerator belongs to ℤ
    /// (the set of integers) and the denominator belongs to ℤ excluding zero.
    ///
    /// @note The class uses the Integer type to represent both the numerator and denominator.
    ///
    /// Example usage:
    /// @code
    /// Rational r1(1, 2);      // Represents the fraction 1/2
    /// Rational r2(3, -4);     // Represents the fraction -3/4
    /// Rational r;             // Forbidden. Default constructor is not defined. Compile time error.
    /// @endcode
    ///
    /// @apiNote The rational type allows the construction of fractions which are undefined, like (x, 0) x/0,
    /// where the denominator is equals to zero, or even 0/0, and the operations are not checked, which this will
    /// lead directly to **undefined behaviour**
    class Rational {
    private:
        Integer _numerator;      ///< The numerator of the rational number, belonging to ℤ.
        Integer _denominator;    ///< The denominator of the rational number, belonging to ℤ, NOT excluding the zero.
    public:
        constexpr static MathSymbol symbol = MathSymbol::Rationals;

        /* template<Numerical L, Numerical R>
        [[nodiscard]] constexpr Rational(L&& numerator, R&& denominator) noexcept
            : _numerator(static_cast<Integer>(std::forward<L>(numerator))),
            _denominator(static_cast<Integer>(std::forward<R>(denominator))) {}
*/
        template<Numerical L, Numerical R>
        [[nodiscard]] constexpr Rational(const L& numerator, const R& denominator) noexcept
            : _numerator(static_cast<Integer>(numerator)), _denominator(static_cast<Integer>(denominator)) {}

        [[nodiscard]] constexpr Rational(const Rational& other) noexcept = default;
        [[nodiscard]] constexpr Rational(Rational&& other) noexcept = default; 

        /// @return a {@link Integer} with the value of the numerator for this rational
        [[nodiscard]] constexpr Integer numerator() const noexcept { return _numerator; }

        /// @return a {@link Integer} with the value of the denominator for this rational
        [[nodiscard]] constexpr Integer denominator() const noexcept { return _denominator; }

        // TODO Add a method to reduce fractions

        // Arithmetic operator overloads
        [[nodiscard]] Rational operator+(const Rational rhs) const;
        [[nodiscard]] Rational operator-(const Rational rhs) const;
        [[nodiscard]] Rational operator*(const Rational rhs) const;

        // TODO complete arithmetic overloads
        // Comparison operator overloads
        [[nodiscard]] bool operator==(Rational rhs) const noexcept;

        // Printable
        friend std::ostream &operator<<(std::ostream& os, const Rational& rhs) {
            os << rhs._numerator;
            os << MathSymbol::DivisionSlash;
            os << rhs._denominator;
            return os;
        }
    };
}

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
    /* return Rational(
        _numerator * rhs.numerator(), _denominator * rhs.denominator()
    ); */
    return Rational(1, rhs.numerator()); // FIXME: provisional while refactoring
}


// Equality

// TODO should we check that 4/2 is the same as 2/1 right? Or we should maintain the difference and explicitly
// say that 4/2 aren't the same Rational number as 2/1?
[[nodiscard]] bool Rational::operator==(const Rational rhs) const noexcept {
    // return _numerator == rhs.numerator() && _denominator == rhs.denominator();
    return _numerator.number() == rhs.numerator().number() && _denominator.number() == rhs.denominator().number();
}



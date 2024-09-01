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

        [[nodiscard]] constexpr Rational(int numerator, int denominator) noexcept
            : _numerator(numerator), _denominator(denominator) {}

        [[nodiscard]] Rational(Natural numerator, Natural denominator) noexcept
            : _numerator(static_cast<Natural>(numerator)), _denominator(static_cast<Natural>(denominator)) {}

        [[nodiscard]] Rational(Integer numerator, Integer denominator) noexcept
            : _numerator(numerator), _denominator(denominator) {}

        /// @return a {@link Integer} with the value of the numerator for this rational
        [[nodiscard]] Integer numerator() const noexcept { return _numerator; }

        /// @return a {@link Integer} with the value of the denominator for this rational
        [[nodiscard]] Integer denominator() const noexcept { return _denominator; }

        // TODO Add a method to reduce fractions

        // Arithmetic operator overloads
        [[nodiscard]] Rational operator+(const Rational rhs) const;
        [[nodiscard]] Rational operator-(const Rational rhs) const;
        [[nodiscard]] Rational operator*(const Integer rhs) const;
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

    private: // TODO: move to an standalone helper
        [[nodiscard]] Rational sum_or_subtract(const Rational &rhs, int sign) const;
    };
}

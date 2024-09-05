/// This module provides strong types over the most common sets of numbers in mathematics

export module math:numbers;

import std;
import math.symbols;

export import :numbers.naturals;
export import :numbers.integers;
export import :numbers.rationals;
export import :general;

import math.ops;

export namespace zero::math {


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


    template <Numerical L, Numerical R>
    constexpr auto operator+(const L& lhs, const R& rhs) noexcept {
        if constexpr (std::is_same_v<L, Rational> || std::is_same_v<R, Rational>) {
            const Rational _lhs = static_cast<Rational>(lhs);
            const Rational _rhs = static_cast<Rational>(rhs);
            const auto op = [&](auto a, auto b) { return sum_or_subtract(a, b, 1) ; };
            return arithmetic_op(lhs, rhs, op);
        }
        else
            return arithmetic_op(lhs, rhs, [](auto a, auto b) { return a + b; });
    }

    template <Numerical L, Numerical R>
    constexpr auto operator-(const L& lhs, const R& rhs) noexcept {
        return arithmetic_op(lhs, rhs, [](auto a, auto b) { return a - b; });
    }

    // TODO: rationals + and - must be used with they our logic

    template <Numerical L, Numerical R>
    constexpr auto operator*(const L& lhs, const R& rhs) noexcept {
        return arithmetic_op(lhs, rhs, [](auto a, auto b) { return a * b; });
    }

    template <Numerical L, Numerical R>
    constexpr bool operator==(const L& lhs, const R& rhs) noexcept {
        return arithmetic_op(lhs, rhs, [](auto a, auto b) { return a == b; });
    }

    // Helper to extract the inner value of a Number type or avoid the method
    // call if it's a primitive (std::is_arithmetic_v).
    template <typename T>
    constexpr auto normalize(const T& value) noexcept {
        if constexpr (std::is_arithmetic_v<T> || std::is_same_v<T, Rational>)
            return value; // Return primitive arithmetic types and Rationals as-is
        else
            return value.number(); 
    }


    // Generalized arithmetic operation helper
    template <typename L, typename R, typename Op>
    constexpr auto arithmetic_op(const L& lhs, const R& rhs, Op op) noexcept {
        if constexpr (std::is_same_v<L, Rational> && std::is_same_v<R, Rational>) {
            // Special handling for Rational types to preserve precision
            return Rational(op(lhs.numerator(), rhs.numerator()), 
                            op(lhs.denominator(), rhs.denominator()));
        } else if constexpr (std::is_same_v<L, Rational>) {
            // Left operand is Rational, handle accordingly
            return Rational(op(lhs.numerator(), normalize(rhs)), lhs.denominator());
        } else if constexpr (std::is_same_v<R, Rational>) {
            // Right operand is Rational, handle accordingly
            return Rational(op(normalize(lhs), rhs.numerator()), rhs.denominator());
        } else {
            // Handle all other cases
            return op(normalize(lhs), normalize(rhs));
        }
    }
}


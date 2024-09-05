/// This module provides strong types over the most common sets of numbers in mathematics

export module math:numbers;

import std;
import math.symbols;

export import :numbers.naturals;
export import :numbers.integers;
export import :numbers.rationals;
export import :general;

export namespace zero::math {

    template <Numerical L, Numerical R>
    constexpr auto operator+(const L& lhs, const R& rhs) noexcept {
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


/// This module provides strong types over the most common sets of numbers in mathematics

export module math:numbers;

import std;
import math.symbols;

export import :numbers.naturals;
export import :numbers.integers;
export import :numbers.rationals;
export import :general;

export namespace zero::math {
// Primary template for multiplying two Numbers
/* template <Number N, Number O>
constexpr auto operator*(const N& lhs, const O& rhs) noexcept {
    if constexpr (std::is_same_v<N, Rational> && std::is_same_v<O, Rational>) {
        // Both are Rationals
        return Rational(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
    } else if constexpr (std::is_same_v<N, Rational>) {
        // LHS is Rational, RHS is a different Number type
        return Rational(lhs.numerator() * rhs.number(), lhs.denominator());
    } else if constexpr (std::is_same_v<O, Rational>) {
        // RHS is Rational, LHS is a different Number type
        return Rational(lhs.number() * rhs.numerator(), rhs.denominator());
    } else {
        // Both are non-Rational Numbers
        return N(lhs.number() * rhs.number());
    }
}

// Overload for Rational and arithmetic types
template <typename T>
constexpr auto operator*(const Rational& lhs, const T& rhs) noexcept
    requires std::is_arithmetic_v<T> {
    return Rational(lhs.numerator() * rhs, lhs.denominator());
}

// Overload for arithmetic types and Rational
template <typename T>
constexpr auto operator*(const T& lhs, const Rational& rhs) noexcept
    requires std::is_arithmetic_v<T> {
    return Rational(lhs * rhs.numerator(), rhs.denominator());
}

// Overload for Number and arithmetic types (covers Integer * int, etc.)
template <Number N, typename T>
constexpr auto operator*(const N& lhs, const T& rhs) noexcept
    requires std::is_arithmetic_v<T> {
    return N(lhs.number() * rhs);
}

// Overload for arithmetic types and Number
template <typename T, Number O>
constexpr auto operator*(const T& lhs, const O& rhs) noexcept
    requires std::is_arithmetic_v<T> {
    return O(lhs * rhs.number());
} */

// Helper to normalize non-Rational types
template <typename T>
constexpr auto normalize(const T& value) noexcept {
    if constexpr (std::is_arithmetic_v<T>) {
        return value; // Return primitive arithmetic types as-is
    } else if constexpr (!std::is_same_v<T, Rational>) {
        return value.number(); // For custom types like Integer, Natural, etc.
    } else {
        // For Rational, don't normalize to preserve exact values
        return value; 
    }
}

template <typename L, typename R>
constexpr auto operator*(const L& lhs, const R& rhs) noexcept {
    return arithmetic_op(lhs, rhs, [](auto a, auto b) { return a * b; });
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


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
template <Number N, Number O>
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
}
}


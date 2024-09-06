/// This module provides strong types over the most common sets of numbers in
/// mathematics

export module math:numbers;

import std;
import math.symbols;

export import :numbers.naturals;
export import :numbers.integers;
export import :numbers.rationals;
export import :general;
import :numbers.detail;

import math.ops;

export namespace zero::math {
// Operator overloads for mixed-type arithmetic involving Rational
template <Numerical L, Numerical R>
constexpr auto operator+(const L &lhs, const R &rhs) noexcept {
  auto op = [](const auto &a, const auto &b) {
    if constexpr (EitherRational<L, R>) {
      return rational_add_or_subtract(a, b, 1); // Special logic for Rational addition
    } else {
      return a + b; // Generic addition
    }
  };
  return arithmetic_op(lhs, rhs, op);
}

template <Numerical L, Numerical R>
constexpr auto operator-(const L &lhs, const R &rhs) noexcept {
  auto op = [](const auto &a, const auto &b) {
    if constexpr (EitherRational<L, R>) {
      return rational_add_or_subtract(a, b, -1); // Special logic for Rational subtraction
    } else {
      return a - b; // Generic subtraction
    }
  };
  return arithmetic_op(lhs, rhs, op);
}

template <Numerical L, Numerical R>
constexpr auto operator*(const L &lhs, const R &rhs) noexcept {
  auto op = [](const auto &a, const auto &b) {
    if constexpr (std::is_same_v<std::decay_t<decltype(a)>, Rational> &&
                  std::is_same_v<std::decay_t<decltype(b)>, Rational>) {
      // Multiplication for Rational types
      return Rational(a.numerator() * b.numerator(),
                      a.denominator() * b.denominator());
    } else if constexpr (std::is_same_v<std::decay_t<decltype(a)>, Rational>) {
      return Rational(a.numerator() * normalize(b), a.denominator());
    } else if constexpr (std::is_same_v<std::decay_t<decltype(b)>, Rational>) {
      return Rational(normalize(a) * b.numerator(), b.denominator());
    } else {
      return normalize(a) * normalize(b); // Generic multiplication
    }
  };
  return arithmetic_op(lhs, rhs, op);
}

template <Numerical L, Numerical R>
constexpr bool operator==(const L &lhs, const R &rhs) noexcept {
  auto op = [](const auto &a, const auto &b) {
    if constexpr (EitherRational<L, R>) {
      // Equality check for Rational types
      return a.numerator() == b.numerator() &&
             a.denominator() == b.denominator();
    } else if constexpr (std::is_same_v<std::decay_t<decltype(a)>, Rational>) {
      return a == Rational(b);
    } else if constexpr (std::is_same_v<std::decay_t<decltype(b)>, Rational>) {
      return Rational(a) == b;
    } else {
      return a == b; // Generic equality check
    }
  };
  return arithmetic_op(lhs, rhs, op);
}
} // namespace zero::math

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
template <Numerical L, Numerical R>
constexpr auto operator+(const L &lhs, const R &rhs) noexcept {
  auto op = [](const auto &a, const auto &b) {
    if constexpr (EitherRational<L, R>) {
      return rational_add_or_subtract(a, b, 1); // Special logic for Rational addition
    } else {
      return a + b;
    }
  };
  return arithmetic_op(lhs, rhs, op);
}

template <Numerical L, Numerical R>
constexpr auto operator-(const L &lhs, const R &rhs) noexcept {
  auto op = [](const auto &a, const auto &b) {
    if constexpr (EitherRational<L, R>) {
      return rational_add_or_subtract(a, b, -1);
    } else {
      return a - b;
    }
  };
  return arithmetic_op(lhs, rhs, op);
}

template <Numerical L, Numerical R>
constexpr auto operator*(const L &lhs, const R &rhs) noexcept {
  auto op = [](const auto &a, const auto &b) {
    if constexpr (EitherRational<L, R>) {
      return rational_mult(a, b);
    } else {
      return normalize(a) * normalize(b);
    }
  };
  return arithmetic_op(lhs, rhs, op);
}

template <Numerical L, Numerical R>
constexpr bool operator==(const L &lhs, const R &rhs) noexcept {
  auto op = [](const auto &a, const auto &b) {
    if constexpr (std::is_same_v<std::decay_t<decltype(a)>, Rational> &&
                  std::is_same_v<std::decay_t<decltype(b)>, Rational>) {
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

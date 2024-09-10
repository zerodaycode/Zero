/// This module provides strong types over the most common sets of numbers in
/// mathematics

export module math:numbers;

import std;
import math.symbols;

export import :numbers.naturals;
export import :numbers.integers;
export import :numbers.rationals;
export import :numbers.reals;
export import :general;

import :numbers.detail;

export namespace zero::math {

// TODO: on the rational operations between Rational and a non-rational,
// we can definitely make the impl simpler by promoting the non rational
// to Rational (standalone templated helper that casts both to rationals
// maybe without if constexpr branches)

template <Numerical L, Numerical R>
constexpr auto operator+(const L &lhs, const R &rhs) noexcept {
  auto op = [](const auto &a, const auto &b) {
    if constexpr (EitherRational<L, R>)
      return rational_add_or_subtract(a, b, ArithmeticOperation::Add);
    else
      return a + b;
  };
  return arithmetic_op(lhs, rhs, op);
}

template <Numerical L, Numerical R>
constexpr auto operator-(const L &lhs, const R &rhs) noexcept {
  auto op = [](const auto &a, const auto &b) {
    if constexpr (EitherRational<L, R>)
      return rational_add_or_subtract(a, b, ArithmeticOperation::Subtract);
    else
      return a - b;
  };
  return arithmetic_op(lhs, rhs, op);
}

template <Numerical L, Numerical R>
constexpr auto operator*(const L &lhs, const R &rhs) noexcept {
  auto op = [](const auto &a, const auto &b) {
    if constexpr (EitherRational<L, R>)
      return rational_multiplication(a, b);
    else
      return a * b;
  };
  return arithmetic_op(lhs, rhs, op);
}

template <Numerical L, Numerical R>
constexpr auto operator/(const L &lhs, const R &rhs) noexcept {
  auto op = [](const auto &a, const auto &b) {
    if constexpr (EitherRational<L, R>)
      return rational_division(a, b);
    else
      return a / b;
  };
  return arithmetic_op(lhs, rhs, op);
}

template <Numerical L, Numerical R>
constexpr bool operator==(const L &lhs, const R &rhs) noexcept {
  auto op = [](const auto &a, const auto &b) {
    if constexpr (EitherRational<L, R>)
      return rational_equality(a, b);
    else
      return a == b;
  };
  return arithmetic_op(lhs, rhs, op);
}

template <Number N> std::ostream &operator<<(std::ostream &os, const N &n) {
  os << n.number();
  return os;
}
} // namespace zero::math

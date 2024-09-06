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
// Generalized arithmetic operation helper using lambdas
template <typename L, typename R, typename Op>
constexpr auto arithmetic_op(const L &lhs, const R &rhs, Op op) noexcept {
  if constexpr (std::is_same_v<L, Rational> || std::is_same_v<R, Rational>) {
    // Handle Rational cases separately by calling the specialized logic
    return op(lhs, rhs);
  } else {
    // Handle all other cases
    return op(normalize(lhs), normalize(rhs));
  }
}

// Operator overloads for mixed-type arithmetic involving Rational
template <Numerical L, Numerical R>
constexpr auto operator+(const L &lhs, const R &rhs) noexcept {
  auto op = [](const auto &a, const auto &b) {
    if constexpr (std::is_same_v<L, Rational> ||
                  std::is_same_v<R, Rational>) {
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
    if constexpr (std::is_same_v<std::decay_t<decltype(a)>, Rational> ||
                  std::is_same_v<std::decay_t<decltype(b)>, Rational>) {
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


// Helper function to sum or subtract two Rationals
[[nodiscard]] constexpr Rational
sum_or_subtract(const Rational &lhs, const Rational &rhs, int sign) noexcept {
  if (lhs.denominator() == rhs.denominator()) { // Like fractions
    return {lhs.numerator() + sign * rhs.numerator(), lhs.denominator()};
  } else { // Unlike fractions
    const int lhs_numerator = lhs.numerator().number();
    const int rhs_numerator = sign * rhs.numerator();
    const int lhs_denominator = lhs.denominator().number();
    const int rhs_denominator = rhs.denominator().number();

    // Get their LCD by finding their LCM
    const auto lcd = zero::math::lcm(lhs_denominator, rhs_denominator);

    // Scale numerators to have the common denominator (LCM)
    const int numerator = (lhs_numerator * (lcd / lhs_denominator)) +
                          (rhs_numerator * (lcd / rhs_denominator));

    return {numerator, lcd};
  }
}
} // namespace zero::math

module math:numbers.detail;

import std;
import math.ops;
import math.symbols;

import :numbers.naturals;
import :numbers.integers;
import :numbers.rationals;

#if defined(__clang__) // TODO: clang seems to be unable to resolve templates
                       // declared on internal partitions, so they must be
                       // 'exported' (even tho the module itself isn't being
                       // exported (module :numbers.detail), so this macro
                       // provisionally normalize the access of the template
                       // Number(s) operations to the implementation details
                       // internal module partition
export namespace zero::math {
#elif defined(_MSC_VER)
using namespace zero::math;
#endif

template <typename L, typename R>
concept EitherRational =
    std::is_same_v<L, Rational> || std::is_same_v<R, Rational>;

// Helper to extract the inner value of a Number type or avoid the method
// call if it's a primitive (std::is_arithmetic_v).
template <typename T> constexpr auto normalize(const T &value) noexcept {
  if constexpr (std::is_arithmetic_v<T> || std::is_same_v<T, Rational>)
    return value; // Return primitive arithmetic types and Rationals as-is
  else
    return value.number();
}

// Generalized arithmetic operation helper using lambdas
template <typename L, typename R, typename Op>
constexpr auto arithmetic_op(const L &lhs, const R &rhs, Op op) noexcept {
  if constexpr (EitherRational<L, R>)
    return op(lhs, rhs);
  else
    return op(normalize(lhs), normalize(rhs));
}

// Specialized addition and subtraction for Rational types
template <typename L, typename R>
constexpr auto rational_add_or_subtract(const L &lhs, const R &rhs, int sign) noexcept {
  if constexpr (std::is_same_v<L, Rational> && std::is_same_v<R, Rational>) {
    return sum_or_subtract(lhs, rhs, sign);
  } else if constexpr (std::is_same_v<L, Rational>) {
    return sum_or_subtract(lhs, Rational(rhs), sign);
  } else if constexpr (std::is_same_v<R, Rational>) {
    return sum_or_subtract(Rational(lhs), rhs, sign);
  }
}

template <typename L, typename R>
constexpr auto rational_mult(const L &lhs, const R &rhs) noexcept {
    if constexpr (std::is_same_v<std::decay_t<decltype(lhs)>, Rational> &&
                  std::is_same_v<std::decay_t<decltype(rhs)>, Rational>) {
      return Rational(lhs.numerator() * rhs.numerator(),
                      lhs.denominator() * rhs.denominator());
    } else if constexpr (std::is_same_v<std::decay_t<decltype(lhs)>, Rational>) {
      return Rational(lhs.numerator() * normalize(rhs), lhs.denominator());
    } else if constexpr (std::is_same_v<std::decay_t<decltype(rhs)>, Rational>) {
      return Rational(normalize(lhs) * rhs.numerator(), rhs.denominator());
    } 
}

// Helper function to sum or subtract two Rationals
[[nodiscard]] constexpr Rational
sum_or_subtract(const Rational &lhs, const Rational &rhs, int sign) noexcept {
  const int lhs_numerator = lhs.numerator().number();
  const int rhs_numerator = sign * rhs.numerator().number();
  const int lhs_denominator = lhs.denominator().number();
  const int rhs_denominator = rhs.denominator().number();

  if (lhs_denominator == rhs_denominator) { // Like fractions
    return {lhs_numerator + rhs_numerator, lhs_denominator};
  } else { // Unlike fractions
    // Get their LCD by finding their LCM
    const auto lcd = zero::math::lcm(lhs_denominator, rhs_denominator);

    // Scale numerators to have the common denominator (LCM)
    const int numerator = (lhs_numerator * (lcd / lhs_denominator)) +
                          (rhs_numerator * (lcd / rhs_denominator));

    return {numerator, lcd};
  }
}

#if defined(__clang__)
}
#endif

module math:numbers.detail;

import std;
import math.ops;
import math.symbols;

import :numbers.general;
import :numbers.naturals;
import :numbers.integers;
import :numbers.rationals;


#if defined(__clang__) // TODO: clang18 seems to be unable to resolve templates declared
                       // on internal partitions, so they must be 'exported' (even tho the module itself isn't being
                       // exported (module :numbers.detail), so this macro provisionally normalize the access of the
                       // template Number(s) operations to the implementation details internal module partition
    export namespace zero::math {
#elif defined(_MSC_VER)
    using namespace zero::math;
#endif

// Helper to extract the inner value of a Number type or avoid the method
// call if it's a primitive (std::is_arithmetic_v).
template <typename T> constexpr auto normalize(const T &value) noexcept {
  if constexpr (std::is_arithmetic_v<T> || std::is_same_v<T, Rational>)
    return value; // Return primitive arithmetic types and Rationals as-is
  else
    return value.number();
}

// Specialized addition and subtraction for Rational types
template <typename L, typename R>
constexpr auto rational_add_or_subtract(const L &lhs, const R &rhs, int sign) noexcept {
  // Ensure one of them is a Rational
  if constexpr (std::is_same_v<L, Rational> && std::is_same_v<R, Rational>) {
    return sum_or_subtract(lhs, rhs, sign);
  } else if constexpr (std::is_same_v<L, Rational>) {
    // LHS is Rational, RHS is a different numeric type
    Rational normalized_rhs = Rational(rhs); // Convert rhs to Rational
    return sum_or_subtract(lhs, normalized_rhs, sign);
  } else if constexpr (std::is_same_v<R, Rational>) {
    // RHS is Rational, LHS is a different numeric type
    Rational normalized_lhs = Rational(lhs); // Convert lhs to Rational
    return sum_or_subtract(normalized_lhs, rhs, sign);
  }
}

#if defined(__clang__)
}
#endif

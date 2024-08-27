export module math.numbers:numbers.concepts;

import std;
import math.symbols;
import :general;

export namespace zero::math {
    /// Concept to act as an interface for the abstract concept of 'number' in mathematics.
    /// In particular, this interface represents a kind of number that belongs to a concrete set of numbers,
    /// for example, the naturals, the integers, the reals, the complex numbers...
    template <typename T>
    concept Number = (
        std::is_same_v<T, Natural> ||
        std::is_same_v<T, Integer> ||
        std::is_same_v<T, Rational> ||
        std::is_same_v<T, Irrational> ||
        std::is_same_v<T, Real> ||
        std::is_same_v<T, Complex>
    ) && requires {
        T::symbol;  /* Check if 'T' has a static member named 'symbol' */
        { T::symbol } -> std::same_as<const MathSymbol&>;  // Check if 'T::symbol' has the type MathSymbol
    };
}

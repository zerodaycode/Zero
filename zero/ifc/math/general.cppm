/**
 * @brief Contains general types/concepts/operations that are meant to be
 * shared across the multiple partitions of the module math
 */

export module math:general;

import std;
import math.symbols;

export namespace zero::math {
    /// Compile time constants for represent an arithmetic operation via literal constants
    enum class ArithmeticOperation {
        Add,
        Subtract,
        Multiply,
        Divide
    };

    /// Forward declarations of the 'Numbers types', so they can be shared across different
    /// module partitions of 'math'
    class Natural;
    class Integer;
    class Rational;
    class Irrational;
    template<typename T = double> class Real;
    class Complex;

    /// Concept to act as an interface for the abstract concept of 'number' in mathematics.
    /// In particular, this interface represents a kind of number that belongs to a concrete set of numbers,
    /// for example, the naturals, the integers, the reals, the complex numbers...
    template <typename T>
    concept Number = ((
        std::is_same_v<T, Natural> ||
        std::is_same_v<T, Integer> ||
        std::is_same_v<T, Rational> ||
        std::is_same_v<T, Irrational> ||
        std::is_same_v<T, Real<>> ||
        std::is_same_v<T, Complex>
    ) && requires {
        T::symbol;  /* Check if 'T' has a static member named 'symbol' */
        { T::symbol } -> std::same_as<const MathSymbol&>;  // Check if 'T::symbol' has the type MathSymbol
    } );

    template <typename T>
    concept Numerical = Number<std::remove_cvref_t<T>> || std::is_arithmetic_v<std::remove_cvref_t<T>>;
}

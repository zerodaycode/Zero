/// This module provides strong types over the most common sets of numbers in mathematics

export module math.numbers;

import std;

export {
    // Forward declarations
    class Natural;
    class Integer;
    class Rational;
    class Irrational;
    class Real;
    class Complex;

    // TODO concept Number
    // TODO adding the set symbols for every type

    /// A positive integer number
    class Natural {
        unsigned int _number;
    public:
        [[nodiscard]] constexpr explicit Natural(unsigned int value) noexcept : _number(value) {}

        /// @return an {@link unsigned int}, which is the value stored in the type, being only a positive integer number
        [[nodiscard]] inline constexpr unsigned int number() const noexcept { return _number; }

        // Arithmetic operator overloads
        [[nodiscard]] inline constexpr Natural operator+(Natural rhs) const noexcept;
        [[nodiscard]] inline constexpr Natural operator-(Natural rhs) const noexcept;
        [[nodiscard]] inline constexpr Natural operator*(Natural rhs) const noexcept;
        [[nodiscard]] inline constexpr Rational operator/(Natural rhs) const noexcept;
    };

    /// A whole real number
    class Integer {
        signed int _number;
    public:
        [[nodiscard]] constexpr explicit Integer(signed int value) noexcept : _number(value) {}
        [[nodiscard]] constexpr explicit Integer(const Natural value) noexcept
            : _number(static_cast<signed int>(value.number())) {}

        /// @return a {@link signed int}, which is the value stored in the type, being a whole number (integer)
        [[nodiscard]] inline constexpr signed int number() const noexcept { return _number; }

        // Arithmetic operator overloads
        [[nodiscard]] inline constexpr Integer operator+(Integer rhs) const noexcept;
        [[nodiscard]] inline constexpr Integer operator-(Integer rhs) const noexcept;
        [[nodiscard]] inline constexpr Integer operator*(Integer rhs) const noexcept;
        [[nodiscard]] inline constexpr Rational operator/(Integer rhs) const noexcept;
    };

    /// @brief A type that represents rational numbers of the form: ℚ = {a, b ∈ ℤ, b ≠ 0}
    ///
    /// The Rational class encapsulates a fraction with an integer numerator and denominator.
    /// Rational numbers are represented as ratios of integers, where the numerator belongs to ℤ
    /// (the set of integers) and the denominator belongs to ℤ excluding zero.
    ///
    /// @note The class uses the Integer type to represent both the numerator and denominator.
    ///
    /// Example usage:
    /// @code
    /// Rational r1(1, 2);      // Represents the fraction 1/2
    /// Rational r2(3, -4);     // Represents the fraction -3/4
    /// Rational r;             // Forbidden. Default constructor is not defined. Compile time error.
    /// @endcode
    ///
    /// @apiNote The rational type allows the construction of fractions which are undefined, like (x, 0) x/0,
    /// where the denominator is equals to zero, or even 0/0, and the operations are not checked, which this will
    /// lead directly to **undefined behaviour**
    class Rational {
    private:
        Integer _numerator;      ///< The numerator of the rational number, belonging to ℤ.
        Integer _denominator;    ///< The denominator of the rational number, belonging to ℤ, NOT excluding the zero.
    public:
        [[nodiscard]] constexpr Rational(int numerator, int denominator) noexcept
            : _numerator(numerator), _denominator(denominator) {}
        [[nodiscard]] constexpr Rational(Natural numerator, Natural denominator) noexcept
            : _numerator(static_cast<Natural>(numerator)), _denominator(static_cast<Natural>(denominator)) {}
        [[nodiscard]] constexpr Rational(Integer numerator, Integer denominator) noexcept
            : _numerator(numerator), _denominator(denominator) {}

        /// @return a {@link Integer} with the value of the numerator for this rational
        [[nodiscard]] inline constexpr Integer numerator() const noexcept { return _numerator; }
        /// @return a {@link Integer} with the value of the denominator for this rational
        [[nodiscard]] inline constexpr Integer denominator() const noexcept { return _denominator; }

//        [[nodiscard]] inline constexpr Rational operator+(const Rational rhs) const {
//            if constexpr (_denominator == rhs.denominator()) // TODO impl the eq of integers as constexpr for this to work
//                return Rational(_number + rhs.number()); // Like fractions
//            else { // Unlike fractions
//                const auto lcm = zero::math::lcm(_denominator, rhs.denominator());
//
//                return Rational(_number + rhs.number());
//            }
//        }
    };

//
//    class Real {
//        double number; // TODO handle rationals and irrationals with std::variant?
//    };
//
//    class Complex {
//        Real real;
//        Real imaginary;
//    };


//    /**
//     * Concept to act as an interface for the abstract concept of 'number' in mathematics.
//     * In particular, this interface represents a kind of number that belongs to a concrete set of numbers,
//     * for example, the naturals, the integers, the reals, the complexes...
//     *
}

// TODO move this ones to an internal module partition?? or to a module implementation better?

            /*++++++++ Operator overloads implementations ++++++++++*/
/*+++++++++++++++++ Naturals +++++++++++++++++*/
[[nodiscard]] inline constexpr Natural Natural::operator+(const Natural rhs) const noexcept {
    return Natural(_number + rhs.number());
}
/// TODO should we do something about the values < 1?
[[nodiscard]] inline constexpr Natural Natural::operator-(const Natural rhs) const noexcept  {
    return Natural(_number - rhs.number());
}

[[nodiscard]] inline constexpr Natural Natural::operator*(const Natural rhs) const noexcept {
    return Natural(_number * rhs.number());
}
[[nodiscard]] inline constexpr Rational Natural::operator/(const Natural rhs) const noexcept {
    return {static_cast<signed int>(_number), static_cast<signed int>(rhs.number())};
}

            /*+++++++++++++++++ Integers +++++++++++++++++*/
[[nodiscard]] inline constexpr Integer Integer::operator+(const Integer rhs) const noexcept {
    return Integer(_number + rhs.number());
}
[[nodiscard]] inline constexpr Integer Integer::operator-(const Integer rhs) const noexcept {
    return Integer(_number - rhs.number());
}
[[nodiscard]] inline constexpr Integer Integer::operator*(const Integer rhs) const noexcept {
    return Integer(_number * rhs.number());
}
[[nodiscard]] inline constexpr Rational Integer::operator/(const Integer rhs) const noexcept {
    return {static_cast<signed int>(_number), static_cast<signed int>(rhs.number())};
}

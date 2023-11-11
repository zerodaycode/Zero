/**
 * This module provides strong types over the most common sets of numbers in mathematics
 */

export module math.numbers;

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
        [[nodiscard]] constexpr explicit Natural(unsigned int value) : _number(value) {}
        [[nodiscard]] constexpr explicit Natural(int value) : _number(static_cast<unsigned int>(value)) {}

        /// @return an {@link unsigned int}, which is the value stored in the type, being only a positive integer number
        [[nodiscard]] inline constexpr unsigned int number() const { return _number; }

        // Operators
        // TODO handle values < 1 (should this return an Integer right?)
        [[nodiscard]] inline constexpr Natural operator+(Natural rhs) const;
        // TODO subtract two naturals which result < 1 should return an Integer?
        [[nodiscard]] inline constexpr Natural operator-(Natural rhs) const;
        [[nodiscard]] inline constexpr Natural operator*(Natural rhs) const;
        [[nodiscard]] inline constexpr Rational operator/(Natural rhs) const;
    };

    // TODO handle the different combinations of arithmetic operations between types

    /// A whole real number
    class Integer {
        signed int _number;
    public:
        [[nodiscard]] constexpr explicit Integer(signed int value) : _number(value) {}
        /// @return a {@link signed int}, which is the value stored in the type, being a whole number (integer)
        [[nodiscard]] inline constexpr signed int number() const { return _number; }

        [[nodiscard]] inline constexpr Integer operator+(Integer rhs) const;
        [[nodiscard]] inline constexpr Integer operator-(Integer rhs) const;
        [[nodiscard]] inline constexpr Integer operator*(Integer rhs) const;
        [[nodiscard]] inline constexpr Rational operator/(Integer rhs) const;
    };

    class Rational {
    private:
        signed int _numerator; // TODO members should be integers
        signed int _denominator;
    public:
        [[nodiscard]] constexpr Rational(signed int numerator, signed int denominator)
                : _numerator(numerator), _denominator(denominator) {}

        [[nodiscard]] inline constexpr signed int numerator() const { return _numerator; }
        [[nodiscard]] inline constexpr signed int denominator() const { return _denominator; }

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

            /*++++++++ Operator overloads implementations ++++++++++*/
            // TODO move this ones to an internal module partition?? or to a module implementation better?
/*+++++++++++++++++ Naturals +++++++++++++++++*/
[[nodiscard]] inline constexpr Natural Natural::operator+(const Natural rhs) const {
    return Natural(_number + rhs.number());
}
[[nodiscard]] inline constexpr Natural Natural::operator-(const Natural rhs) const {
    return Natural(_number - rhs.number());
}
[[nodiscard]] inline constexpr Natural Natural::operator*(const Natural rhs) const {
    return Natural(_number * rhs.number());
}
[[nodiscard]] inline constexpr Rational Natural::operator/(const Natural rhs) const {
    return {static_cast<signed int>(_number), static_cast<signed int>(rhs.number())};
}

            /*+++++++++++++++++ Integers +++++++++++++++++*/
[[nodiscard]] inline constexpr Integer Integer::operator+(const Integer rhs) const {
    return Integer(_number + rhs.number());
}
[[nodiscard]] inline constexpr Integer Integer::operator-(const Integer rhs) const {
    return Integer(_number - rhs.number());
}
[[nodiscard]] inline constexpr Integer Integer::operator*(const Integer rhs) const {
    return Integer(_number * rhs.number());
}
[[nodiscard]] inline constexpr Rational Integer::operator/(const Integer rhs) const {
    return {static_cast<signed int>(_number), static_cast<signed int>(rhs.number())};
}

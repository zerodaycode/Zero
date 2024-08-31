export module math.numbers:naturals;

import std;
import math.symbols;

import :general;
import :numbers.concepts;

export namespace zero::math {
    /// A positive integer number
    class Natural: public NumberBase<Natural> {
    private:
        // TODO. shouldn't be unsigned. we may decide what kind of thing we do
        // with signedness
        unsigned int _number;
    public:
        constexpr static MathSymbol symbol { MathSymbol::Naturals };

        [[nodiscard]] constexpr explicit Natural(unsigned int value) noexcept : _number(value) {}

        /// @return an {@link unsigned int}, which is the value stored in the type, being only a positive integer number
        [[nodiscard]] constexpr unsigned int number() const noexcept { return _number; }

        // Arithmetic operator overloads
        /* [[nodiscard]] Natural operator+(Natural rhs) const noexcept;
        [[nodiscard]] Natural operator-(Natural rhs) const noexcept;
        [[nodiscard]] Natural operator*(Natural rhs) const noexcept;
        [[nodiscard]] Rational operator/(Natural rhs) const noexcept; */
        // Comparison operator overloads
        // [[nodiscard]] bool operator==(Natural rhs) const noexcept;
        [[nodiscard]] bool operator==(unsigned int rhs) const noexcept {
            return _number == rhs;
        }
        // Printable // TODO: please, add a concept for this operators
        friend std::ostream& operator<<(std::ostream& os, const Natural& rhs) {
            os << rhs._number;
            return os;
        }
    };
}


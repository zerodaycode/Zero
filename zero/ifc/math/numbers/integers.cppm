export module math:numbers.integers;

import std;
import math.ops;
import math.symbols;

import :general;
import :numbers.general;
import :numbers.naturals;

export namespace zero::math {
    /// A whole (non decimal nor fraction) real number
    class Integer: public NumberBase<Integer> {
    private:
        signed int _number;
    public:
        constexpr static MathSymbol symbol { MathSymbol::Integers };

        // TODO: explicit templated constructor constrained by Numerical?
        // TODO: document in the public API that any decimal number will be truncated
        [[nodiscard]] constexpr explicit Integer(const int value) noexcept : _number(value) {}
        [[nodiscard]] explicit Integer(const Natural value) noexcept
            : _number(static_cast<signed int>(value.number())) {}

        /// @return a {@link signed int}, which is the value stored in the type, being a whole number (integer)
        [[nodiscard]] constexpr signed int number() const noexcept { return _number; }

        // Arithmetic operator overloads
        /* [[nodiscard]] Rational operator*(Rational rhs) const noexcept;
        [[nodiscard]] Rational operator/(Integer rhs) const noexcept; // TODO: this can't be noexcept */
        // Comparison operator overloads

        /* [[nodiscard]] constexpr bool operator==(const int rhs) const noexcept {
            return _number == rhs;
        } */
        // Explicit conversion operators
        [[nodiscard]] constexpr explicit operator int() const { return _number; }
        // Printable
        friend std::ostream& operator<<(std::ostream& os, const Integer& rhs) {
            os << rhs._number;
            return os;
        }
    };

}

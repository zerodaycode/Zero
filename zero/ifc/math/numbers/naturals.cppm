export module math:numbers.naturals;

import std;
import math.symbols;

import :general;
import :numbers.general;

export namespace zero::math {
    /// A positive integer number
    class Natural {
    private:
        // TODO: shouldn't be unsigned. we may decide what kind of thing we do
        // with signedness
        unsigned int _number;
    public:
        constexpr static MathSymbol symbol { MathSymbol::Naturals };

        [[nodiscard]] constexpr explicit Natural(unsigned int value) noexcept : _number(value) {}

        /// @returns an {@link unsigned int}, which is the value stored in the type, being only a positive integer number
        [[nodiscard]] constexpr unsigned int number() const noexcept { return _number; }

        /// TODO: should we do something about the values < 1?
        /// Definetly yes, and now that we have a common base via CRTP,
        /// we can override the impl on naturals to provide custom behaviour
        ///
        /* [[nodiscard]] Natural Natural::operator-(const Natural rhs) const noexcept  {
            return Natural(_number - rhs.number());
        } */
        /// @overload
        /* [[nodiscard]] bool operator==(unsigned int rhs) const noexcept {
            return _number == rhs; // TODO: I think that we don't need this one
        } */
        // Printable // TODO: please, add a concept for this operators
        friend std::ostream& operator<<(std::ostream& os, const Natural& rhs) {
            os << rhs._number;
            return os;
        }
    };
}


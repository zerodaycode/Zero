export module math:numbers.naturals;

import std;
import math.symbols;

import :general;

export namespace zero::math {
    /// A positive integer number
    class Natural {
    private:
        // TODO: shouldn't be unsigned. we may decide what kind of thing we do
        // with signedness
        int _number;
    public:
        constexpr static MathSymbol symbol { MathSymbol::Naturals };

        [[nodiscard]] constexpr explicit Natural(const int value) noexcept : _number(value) {}

        /// @returns an {@link unsigned int}, which is the value stored in the type, being only a positive integer number
        [[nodiscard]] constexpr int number() const noexcept { return _number; }

        /// TODO: should we do something about the values < 1?
        /// Maybe promote them to Integer or just throw?
        /* [[nodiscard]] Natural Natural::operator-(const Natural rhs) const noexcept  {
            return Natural(_number - rhs.number());
        } */
    };
}



export module math:numbers.reals;

import std;
import math.ops;
import math.symbols;

import :general;
import :numbers.naturals;
import :numbers.integers;
import :numbers.rationals;

export namespace zero::math {

    template<typename T>
    class Real {
    private:
        T _number;
    public:
        constexpr static MathSymbol symbol = MathSymbol::Reals;

        [[nodiscard]] constexpr Real(const T& value) noexcept : _number{value} {}
        [[nodiscard]] constexpr Real(const Real& other) noexcept = default;
        [[nodiscard]] constexpr Real(Real&& other) noexcept = default; 
        [[nodiscard]] constexpr T number() const noexcept { return _number; }
    };
}

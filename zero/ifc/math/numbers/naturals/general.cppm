/// module partition for hold mostly forward declaration of the 'numerical types'
export module math.numbers:general;

import std;
import math.ops;
import math.symbols;

export namespace zero::math {
    // Forward declarations
    class Natural;
    class Integer;
    class Rational;
    class Irrational;
    class Real;
    class Complex;

    template<typename Derived>
    class NumberBase {
        // TODO: ensure in our concept (or create another) that all the Number(s) contains
        // a fixed name member (like _value or _number), normalized, so we can access it
    private:
        friend Derived;
        NumberBase() = default;
        
        auto _self() -> Derived& {
            return static_cast<Derived&>(*this);
        }

        auto _self() const -> const Derived& {
            return static_cast<const Derived&>(*this);
        }
    public:
        // Addition
        [[nodiscard]] Derived operator+(const Derived& rhs) const noexcept {
            return Derived(_self().number() + rhs.number());
        }

        // Subtraction
        [[nodiscard]] Derived operator-(const Derived& rhs) const noexcept {
            return Derived(_self().number() - rhs.number());
        }

        // Multiplication
        [[nodiscard]] Derived operator*(const Derived& rhs) const noexcept {
            return Derived(_self().number() * rhs.number());
        }

        // Division
        [[nodiscard]] Derived operator/(const Derived& rhs) const noexcept {
            return Derived(_self().number() / rhs.number());
        }

        [[nodiscard]] constexpr bool operator==(const Derived& rhs) const noexcept {
            if constexpr (std::is_same_v<Derived, Natural>)
                return static_cast<Natural>(_self().number()) == rhs;
            else
                return static_cast<int>(_self().number()) == rhs;
        }
        /* [[nodiscard]] constexpr bool operator==(const int rhs) const noexcept {
            return static_cast<int>(_self().number()) == rhs;
        } */
    };

}

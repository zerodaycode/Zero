/// module partition for hold mostly forward declaration of the 'numerical types'
export module math:numbers.general;

import std;
import :general;
import math.ops;
import math.symbols;

export namespace zero::math {
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
            return _self().number() == rhs.number();
        }
    };

}

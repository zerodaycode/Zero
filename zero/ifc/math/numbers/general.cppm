/// module partition for hold mostly forward declaration of the 'numerical types'
export module math:numbers.general;

import std;

import :general;

import math.ops;
import math.symbols;

export namespace zero::math {
    template<typename Derived> // can't constraint it with Number since ATM only fwd decls
    class NumberBase {
        // TODO: ensure in our concept (or create another) that all the Number(s) contains
        // a fixed name member (like _value or _number), normalized, so we can access it
    private:
        friend Derived;
        NumberBase() = default;
        
        inline constexpr auto _self() -> Derived& {
            return static_cast<Derived&>(*this);
        }

        inline constexpr auto _self() const -> const Derived& {
            return static_cast<const Derived&>(*this);
        }
    public:

        [[nodiscard]] constexpr auto number() const noexcept -> int {
            return _self().number();
        }
        // Addition
        [[nodiscard]] constexpr auto operator+(const Derived& rhs) const noexcept -> Derived {
            return Derived(_self().number() + rhs.number());
        }

        // Subtraction
        [[nodiscard]] constexpr auto operator-(const Derived& rhs) const noexcept -> Derived {
            return Derived(_self().number() - rhs.number());
        }

        // Multiplication
        [[nodiscard]] constexpr auto operator*(const Derived& rhs) const noexcept -> Derived {
            return Derived(_self().number() * rhs.number());
        }

        // Division
        // TODO: removed the noexcept, since division by Zero must return std::expect or just throw
        [[nodiscard]] constexpr auto operator/(const Derived& rhs) const -> Derived {
            return Derived(_self().number() / rhs.number());
        }

        // Basic equality
        [[nodiscard]] constexpr auto operator==(const Derived& rhs) noexcept -> bool {
            return _self().number() == rhs.number();
        }

        [[nodiscard]] constexpr auto operator==(const int rhs) const noexcept -> bool {
            return _self().number() == rhs;
        }
    };

    /* [[nodiscard]] constexpr auto operator==(const Derived& rhs) noexcept -> bool {
        return _self().number() == rhs.number();
    } */
}


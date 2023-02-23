/**
 * @brief Module for design types and behavior associated with Physical Quantities.
 * 
 * A physical quantity can be undestand as a real world magnitude, related with
 * their units in the international system
 */

export module physics:quantities;
import :ratios;
import std;

export namespace zero::physics {
    template<typename T>
    struct unit_symbol {
        using symbol = T;
    };

    template<typename T>
    concept Symbol = requires {
        typename T::symbol;
    };
    
    template<typename T, Ratio prefix, Symbol S>
    struct base_unit {};

    // template<typename T>
    class base_magnitude {};

    struct kg: unit_symbol<kg> {};

    class mass: public base_magnitude {};

    struct Kilogram: public mass {
        using ratio = Kilo;
    };

    template <typename Parent, typename Child>
    concept ValidUnitForDimension = std::is_base_of_v<Parent, Child>;

    template <typename D, typename R>
        requires (ValidUnitForDimension<D, R>)
    class quantity {
    public:
        double amount;
        quantity() : amount(0) {}
        constexpr quantity(double val) : amount(val) {}

        // template<typename U>
        // constexpr quantity<D, R>(const quantity<D, U>& other) : amount(other.amount) {}

        template<typename U>
        constexpr auto operator+(const quantity<D, U>& other) 
            -> quantity<D, std::conditional_t<(R::ratio::value > U::ratio::value), R, U>>
        {
            if constexpr (R::ratio::value > U::ratio::value)
                return quantity<D, R>(amount + other.amount);
            else
                return quantity<D, U>(amount + other.amount);
        }

        // template <typename T>
        friend std::ostream& operator<<(std::ostream& os, const quantity& q) {
            os << q.amount;
            return os;
        }

        // template<typename U>
        // constexpr auto operator>(const quantity<D, U>& other) -> quantity<decltype(D - R)> {
        //     return quantity<D, decltype(D  R)>(amount - other.amount);
        // }

        // template<typename U>
        // constexpr auto operator-(const quantity<D, U>& other) -> quantity<decltype(amount - other.amount)> {
        //     return quantity<D, decltype(amount - other.amount)>(amount - other.amount);
        // }

        // template<typename U>
        // constexpr auto operator*(const U& other) -> quantity<D, decltype(amount * other.amount)> {
        //     return quantity<D, decltype(amount * other.amount)>(amount * other.amount);
        // }

        // template<typename U>
        // constexpr auto operator/(const U& other) -> base_magnitude<decltype(amount / other.amount)> {
        //     return base_magnitude<decltype(amount / other.amount)>(amount / other.amount);
        // }
    };
    
    // template<typename T>
    // class length : public base_magnitude<meter_unit<T>> {
    // public:
    //     using base_magnitude<meter_unit<T>>::base_magnitude;
    // };

    // template<typename T>
    // class time : public base_magnitude<millisecond_unit<T>> {
    // public:
    //     using base_magnitude<millisecond_unit<T>>::base_magnitude;
    // };
}

static_assert(zero::physics::Symbol<zero::physics::kg>);
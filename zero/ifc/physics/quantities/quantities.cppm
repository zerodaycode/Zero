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
    
    struct kg: unit_symbol<kg> {};
    struct hg: unit_symbol<hg> {};
    struct m: unit_symbol<m> {};


    template<Ratio prefix, Symbol S>
    struct base_unit {};

    template<Ratio prefix, Symbol S>
    class base_magnitude {};

    template <Ratio R, Symbol S>
    class mass: public base_magnitude<R, S> {};
    template<Ratio R, Symbol S>
    class length : public base_magnitude<R, S> {};

    template <typename T>
    concept Magnitude = requires {
        typename T::dimension;
        typename T::ratio;
    };

    template <typename T, typename R>
    concept SameMagnitude = requires {
        requires Magnitude<T> && Magnitude<R>;
        requires std::is_same_v<typename T::dimension, typename R::dimension>;
    };

    struct Kilogram: public mass<Kilo, kg> {
        using dimension = mass;
        using ratio = Kilo;
    };
    struct Hectogram: public mass<Hecto, hg> {
        using dimension = mass;
        using ratio = Hecto;
    };

    struct Meter: public length<Root, m> {
        using dimension = length;
        using ratio = Hecto;
    };

    // template <typename Magnitude1, typename Magnitude2>
    // concept ValidUnitForDimension = requires {
    //     Magnitude<typename Magnitude1::dimension, typename Magnitude2::ratio>;
    // };
    // requires {
    //     requires Magnitude<
    //         typename Magnitude1::dimension,
    //         typename Magnitude1::ratio> 
    //     && Magnitude<
    //         typename Magnitude2::dimension,
    //         typename Magnitude2::ratio>;
    // } && std::is_same_v<
    //     typename Magnitude1::dimension,
    //     typename Magnitude2::dimension>;

    template <typename R>
    class quantity {
    public:
        double amount;
        quantity() : amount(0) {}
        constexpr quantity(double val) : amount(val) {}

        // template<typename U>
        // constexpr quantity<D, R>(const quantity<D, U>& other) : amount(other.amount) {}

        template<typename U>
        requires SameMagnitude<R, U>
        constexpr auto operator+(const quantity<U>& other) 
            -> quantity<std::conditional_t<(R::ratio::value > U::ratio::value), R, U>>
        {
            if constexpr (R::ratio::value > U::ratio::value)
                return quantity<R>(amount + other.amount);
            else
                return quantity<U>(amount + other.amount);
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
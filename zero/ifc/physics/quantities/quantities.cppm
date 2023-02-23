/**
 * @brief Module for design types and behavior associated with Physical Quantities.
 * 
 * A physical quantity can be undestand as a real world magnitude, related with
 * their units in the international system
 */

export module physics:quantities;
import :ratios;

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

    template<typename T>
    class base_magnitude {
    public:
        double amount;
        base_magnitude() : amount(0) {}
        constexpr base_magnitude(double val) : amount(val) {}

        template<typename U>
        constexpr base_magnitude(const base_magnitude<U>& other) : amount(other.amount) {}

        template<typename U>
        constexpr auto operator+(const base_magnitude<U>& other) -> base_magnitude<decltype(amount + other.amount)> {
            return base_magnitude<decltype(amount + other.amount)>(amount + other.amount);
        }

        template<typename U>
        constexpr auto operator-(const base_magnitude<U>& other) -> base_magnitude<decltype(amount - other.amount)> {
            return base_magnitude<decltype(amount - other.amount)>(amount - other.amount);
        }

        template<typename U>
        constexpr auto operator*(const U& other) -> base_magnitude<decltype(amount * other.amount)> {
            return base_magnitude<decltype(amount * other.amount)>(amount * other.amount);
        }

        template<typename U>
        constexpr auto operator/(const U& other) -> base_magnitude<decltype(amount / other.amount)> {
            return base_magnitude<decltype(amount / other.amount)>(amount / other.amount);
        }
    };

    // template<typename T>
    // using gram_unit = base_unit<Ratio<0>, T>;

    struct kg: unit_symbol<kg> {};
    
    template<typename T>
    using kilogram_unit = base_unit<T, Kilo, kg>;

    // template<typename T>
    // using millimeter_unit = unit_with_prefix<Ratio<-3>, T>;

    // template<typename T>
    // using meter_unit = unit_with_prefix<Ratio<0>, T>;

    // template<typename T>
    // using millisecond_unit = unit_with_prefix<Ratio<-3>, T>;

    template<typename T>
    class mass : public base_magnitude<kilogram_unit<T>> {
    public:
        using base_magnitude<kilogram_unit<T>>::base_magnitude;
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
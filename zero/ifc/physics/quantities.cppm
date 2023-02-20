/**
 * @brief Module for design types and behavior associated with Physical Quantities.
 * 
 * A physical quantity can be undestand as a real world magnitude, related with
 * their units in the international system
 */

export module physics:quantities;

export namespace zero::physics {
    template<typename T>
    struct base_unit {
        using unit_type = T;
    };


    template<typename T>
    concept simbol = requires {
        typename T::simbol;
    };

    template <int r>
    struct Ratio {
        using ratio = decltype(r);
    };

    template<simbol U1, simbol U2>
    struct unit_multiply;
    template<simbol U1, simbol U2>
    using unit_multiply_t = typename unit_multiply<U1, U2>::type;
    template<simbol U1, simbol U2>
    struct unit_multiply {
        using type = unit_multiply_t<typename U1::unit_type, typename U2::unit_type>;
    };



    template<typename T>
    class base_magnitude {
    public:
        double amount;
        base_magnitude() : amount(0) {}
        constexpr base_magnitude(double val) : amount(val) {}

        template<typename U>
        constexpr base_magnitude(const base_magnitude<U>& other) : amount(other.amount) {}

        template<typename T1, typename T2>
        friend constexpr auto operator+(const base_magnitude<T1>& lhs, const base_magnitude<T2>& rhs) -> base_magnitude<decltype(lhs.value + rhs.value)> {
            return base_magnitude<decltype(lhs.value + rhs.value)>(lhs.value + rhs.value);
        }
    };

    template <typename T1, typename T2>
    constexpr auto operator+(const base_magnitude<T1>& lhs, const base_magnitude<T2>& rhs) -> base_magnitude<decltype(lhs.value() + rhs.value())>;

    template<typename T>
    struct unit_simbol {
        using simbol = T;
    };

    template <typename Derived, typename T>
    struct unit_with_prefix : public base_unit<T> {
        using base_unit<T>::base_unit;
        using ratio = typename Derived::ratio;
    };

    template<typename T>
    using gram_unit = unit_with_prefix<Ratio<0>, T>;

    template<typename T>
    using kilogram_unit = unit_with_prefix<Ratio<3>, T>;

    template<typename T>
    using millimeter_unit = unit_with_prefix<Ratio<-3>, T>;

    template<typename T>
    using meter_unit = unit_with_prefix<Ratio<0>, T>;

    template<typename T>
    using millisecond_unit = unit_with_prefix<Ratio<-3>, T>;

    template<typename T>
    class mass : public base_magnitude<kilogram_unit<T>> {
    public:
        using base_magnitude<kilogram_unit<T>>::base_magnitude;
    };

    

    template<typename T>
    class length : public base_magnitude<meter_unit<T>> {
    public:
        using base_magnitude<meter_unit<T>>::base_magnitude;
    };

    template<typename T>
    class time : public base_magnitude<millisecond_unit<T>> {
    public:
        using base_magnitude<millisecond_unit<T>>::base_magnitude;
    };
}

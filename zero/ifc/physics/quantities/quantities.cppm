
/**
 * @brief Module for design types and behavior associated with Physical Quantities.
 * 
 * A physical quantity can be understand as a real world magnitude, related with
 * their units in the international system
 */
export module physics:quantities;
import :ratios;
import :quantities.symbols;

import std;
import concepts;

export namespace zero::physics {
    template<Ratio prefix, Symbol S>
    struct base_unit {};

    template<typename Derived>
    class base_magnitude {};

    template <Ratio R, Symbol S>
    class mass: public base_magnitude<mass<R, S>>, public base_unit<R, S>{};
    template<Ratio R, Symbol S>
    class length: public base_magnitude<mass<R, S>>, public base_unit<R, S>{};

    template <typename T>
    concept Magnitude = requires {
        typename T::dimension;
        typename T::ratio;
        typename T::symbol;
    };

    template <typename T, typename R>
    concept SameDimension = requires {
        requires Magnitude<T> && Magnitude<R>;
        requires zero::concepts::SameTemplate<
            typename T::dimension,
            typename R::dimension
        >;
    };

    struct Kilogram: public mass<Kilo, kg> {
        using dimension = mass;
        using ratio = Kilo;
        using symbol = kg;
    };
    struct Hectogram: public mass<Hecto, hg> {
        using dimension = mass;
        using ratio = Hecto;
        using symbol = hg;
    };

    struct Meter: public length<Root, m> {
        using dimension = length;
        using ratio = Hecto;
        using symbol = m;
    };

    template <typename T>
    concept ValidAmountType = (std::is_integral_v<T> || std::is_floating_point_v<T>)
        && !std::is_same_v<T, char>;

    template <Magnitude M, ValidAmountType T = double>
    struct quantity {
        T amount;
        constexpr quantity<M, T>() noexcept = default;
        constexpr explicit quantity<M, T>(T val) noexcept : amount(val) {}
    };

    /**
     * @brief Addition of two scalar values, given in the form of a pair of operands
     *
     * @tparam M1 the left hand side of the binary expression
     * @tparam M2 the right hand side of the binary expression
     * @tparam T1 the explicit type of the quantity on the lhs of the binary operator +
     * @tparam T2 the explicit type of the quantity on the rhs of the binary operator +
     *
     * @return the value of add the amount of the two magnitudes, with the return type of
     * the one that has the bigger ratio given their common dimension
     */
    template<Magnitude M1, Magnitude M2, ValidAmountType T1 = double, ValidAmountType T2 = T1>
        requires SameDimension<M1, M2>
    [[nodiscard]] 
    constexpr auto operator+(const quantity<M1, T1>& lhs, const quantity<M2, T2>& rhs)
        -> quantity<std::conditional_t<(M1::ratio::value > M2::ratio::value), M1, M2>>
    {
        if constexpr (M1::ratio::value > M2::ratio::value)
            return quantity<M1, T1>(
                (lhs.amount * M1::ratio::value + rhs.amount * M2::ratio::value) / M1::ratio::value
            );
        else
            return quantity<M2, T2>(
                (lhs.amount * M1::ratio::value + rhs.amount * M2::ratio::value) / M2::ratio::value
            );
    }

    /**
     * @brief Subtraction of two scalar values, given in the form of a pair of operands
     *
     * @tparam M1 the left hand side of the binary expression
     * @tparam M2 the right hand side of the binary expression
     * @tparam T1 the explicit type of the quantity on the lhs of the binary operator +
     * @tparam T2 the explicit type of the quantity on the rhs of the binary operator +
     *
     * @return the value of add the amount of the two magnitudes, with the return type of
     * the one that has the bigger ratio given their common dimension
     */
    template<Magnitude M1, Magnitude M2, ValidAmountType T1 = double, ValidAmountType T2 = T1>
    requires SameDimension<M1, M2>
        [[nodiscard]]
    constexpr auto operator-(const quantity<M1, T1>& lhs, const quantity<M2, T2>& rhs)
        -> quantity<std::conditional_t<(M1::ratio::value > M2::ratio::value), M1, M2>>
    {
        if constexpr (M1::ratio::value > M2::ratio::value)
            return quantity<M1, T1>(
                (lhs.amount * M1::ratio::value - rhs.amount * M2::ratio::value) / M1::ratio::value
            );
        else
            return quantity<M2, T2>(
                (lhs.amount * M1::ratio::value - rhs.amount * M2::ratio::value) / M2::ratio::value
            );
    }

    template<typename M>
    constexpr std::ostream& operator<<(std::ostream& os, const quantity<M>& q) {
        os << q.amount;
        return os;
    }
}

static_assert(zero::physics::Symbol<zero::physics::kg>);
static_assert(zero::physics::Magnitude<zero::physics::Kilogram>);
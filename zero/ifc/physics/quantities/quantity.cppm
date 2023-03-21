/**
 * @brief Module for design types and behavior associated with Physical Quantities.
 * 
 * A physical quantity can be understand as a real world magnitude, related with
 * their units in the international system
 */
export module physics:quantity;

import std;
import concepts;

import :ratios;
import :units;
import :units.symbols;

export namespace zero::physics {
    template <typename T>
    concept Unit = requires {
        // Actually we changed Magnitude in favor or Unit
        // But still not ready to refactor names
        typename T::dimension;
        typename T::ratio;
        typename T::symbol;
    }; // should represent BaseUnit

    template <typename T>
    concept DerivedMagnitude = requires {
        typename T::dimensions;
        typename T::units;
    };

    template <typename T>
    concept Magnitude = Unit<T> || DerivedMagnitude<T>;

//    template<typename... Ts>
//    concept DerivedMagnitudeNO = requires {
//        requires (requires { typename Ts::dimensions; } && ...);
//    };

    // TODO Dev notes: We could extract the arithmetic operations into standalone
    // free template functions, and let the overload of every operator decide
    // which implementation has to call

    template<typename... Types>
    using dimensions = std::tuple<Types...>;

    template <typename T, typename R>
    concept SameDimension = requires {
        requires Magnitude<T> && Magnitude<R>;
        requires std::is_same_v<
            typename T::dimension,
            typename R::dimension
        >;
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
        constexpr auto m1_ratio_v = M1::base_unit::ratio::value;
        constexpr auto m2_ratio_v = M2::base_unit::ratio::value;

        if constexpr (M1::ratio::value > M2::ratio::value)
            return quantity<M1, T1>(
                (lhs.amount * m1_ratio_v + rhs.amount * m2_ratio_v) / m1_ratio_v
            );
        else
            return quantity<M2, T2>(
                (lhs.amount * m1_ratio_v + rhs.amount * m2_ratio_v) / m1_ratio_v
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
        constexpr auto m1_ratio_v = M1::base_unit::ratio::value;
        constexpr auto m2_ratio_v = M2::base_unit::ratio::value;

        if constexpr (M1::ratio::value > M2::ratio::value)
            return quantity<M1, T1>(
                (lhs.amount * m1_ratio_v - rhs.amount * m2_ratio_v) / m1_ratio_v
            );
        else
            return quantity<M2, T2>(
                (lhs.amount * m1_ratio_v - rhs.amount * m2_ratio_v) / m1_ratio_v
            );
    }

    /**
     * @brief The product of two scalar values, given in the form of a pair of operands
     *
     * @tparam M1 the left hand side of the binary expression
     * @tparam M2 the right hand side of the binary expression
     * @tparam T1 the explicit type of the quantity on the lhs of the binary operator +
     * @tparam T2 the explicit type of the quantity on the rhs of the binary operator +
     *
     * @return the value of multiply the amount of the two magnitudes, with the return type of
     * the one that has the bigger ratio given their common dimension
     */
    template<Magnitude M1, Magnitude M2, ValidAmountType T1 = double, ValidAmountType T2 = T1>
        requires SameDimension<M1, M2>
    [[nodiscard]]
    constexpr auto operator*(const quantity<M1, T1>& lhs, const quantity<M2, T2>& rhs)
        -> quantity<std::conditional_t<(M1::ratio::value > M2::ratio::value), M1, M2>>
    {
        constexpr auto m1_ratio_v = M1::base_unit::ratio::value;
        constexpr auto m2_ratio_v = M2::base_unit::ratio::value;

        if constexpr (M1::ratio::value > M2::ratio::value)
            return quantity<M1, T1>(
                (lhs.amount * m1_ratio_v * rhs.amount * m2_ratio_v) / m1_ratio_v
            );
        else
            return quantity<M2, T2>(
                (lhs.amount * m1_ratio_v * rhs.amount * m2_ratio_v) / m1_ratio_v
            );
    }

    /**
     * @brief The division of two scalar values, given in the form of a pair of operands
     *
     * @tparam M1 the left hand side of the binary expression
     * @tparam M2 the right hand side of the binary expression
     * @tparam T1 the explicit type of the quantity on the lhs of the binary operator +
     * @tparam T2 the explicit type of the quantity on the rhs of the binary operator +
     *
     * @return the value of performing a division arithmetic operation between the amount of the two magnitudes,
     * being the return type of the resultant magnitude the one of the magnitude that has the bigger ratio
     */
    template<Magnitude M1, Magnitude M2, ValidAmountType T1 = double, ValidAmountType T2 = T1>
    requires SameDimension<M1, M2>
        [[nodiscard]]
    constexpr auto operator/(const quantity<M1, T1>& lhs, const quantity<M2, T2>& rhs)
        -> quantity<std::conditional_t<(M1::ratio::value > M2::ratio::value), M1, M2>>
    {
        constexpr auto m1_ratio_v = M1::base_unit::ratio::value;
        constexpr auto m2_ratio_v = M2::base_unit::ratio::value;

        if constexpr (M1::ratio::value > M2::ratio::value)
            return quantity<M1, T1>(
                ((lhs.amount * m1_ratio_v) / (rhs.amount * m2_ratio_v)) / m1_ratio_v
            );
        else
            return quantity<M2, T2>(
                ((lhs.amount * m1_ratio_v) / (rhs.amount * m2_ratio_v)) / m2_ratio_v
            );
    }

    /**
     * Sends to an output stream a formatted version of some {@link quantity}
     */
    template<typename M>
    constexpr std::ostream& operator<<(std::ostream& os, const quantity<M>& q) {
        os << q.amount;
        return os;
    }
}

/* Testing our symbols */
static_assert(zero::physics::Symbol<zero::physics::kg>);

/* Testing our base units */
static_assert(zero::physics::Unit<zero::physics::Kilogram>);

/* Testing our derived units */
static_assert(zero::physics::DerivedMagnitude<zero::physics::MetersPerSecond>);

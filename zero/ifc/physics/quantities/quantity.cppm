/**
 * @brief Module for design types and behavior associated with Physical Quantities.
 * 
 * A physical quantity can be understand as a real world magnitude, related with
 * their units in the international system
 */
export module physics:quantity;

import std;
import concepts;
import type_info;
import str_manip;

import :ratios;
import :dimensions;
import :units;
import :units.symbols;
import :units.detail;

export namespace zero::physics {
    template <typename T>
    concept BaseMagnitude = requires {
        BaseUnit<T>;
        BaseDimension<typename T::dimension>;
    };

    template<typename T>
    struct is_base_magnitude : std::false_type {};

    template<typename T>
        requires BaseMagnitude<std::remove_reference_t<T>>
    struct is_base_magnitude<T> : std::true_type {};

    template <typename T>
    concept DerivedMagnitude = requires {
        DerivedUnit<T>;
        DerivedDimension<typename T::self>;
    };

    template <typename T>
    concept Magnitude = is_base_magnitude<T>::value || DerivedMagnitude<T>;

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

    /**
     * A measurable property of a physical body, expressed in the terms of a scalar value with
     * their units
     * @tparam M a type that satisfies the {@link Magnitude} concept
     * @tparam T a valid type for represent the scalar numeric value, constrained by the {@link ValidAmountType} concept
     */
    template <Magnitude M, ValidAmountType T = double>
    struct quantity {
        T amount;
        constexpr quantity<M, T>() noexcept = default;
        constexpr explicit quantity<M, T>(T val) noexcept : amount(val) {}

        template <typename Dummy = void, typename = std::enable_if_t<DerivedMagnitude<M>, Dummy>>
        std::vector<std::string> dimensions() const {
            std::vector<std::string> stringified_dimensions;
            std::apply([&](auto... dim) {
                ((stringified_dimensions.emplace_back(zero::split_str(zero::types::type_name<decltype(dim)>()).back())), ...);
            }, typename M::derived_dimension::dimensions{});
            return stringified_dimensions;
        }

        template <typename Dummy = void, typename = std::enable_if_t<DerivedMagnitude<M>, Dummy>>
        void print_dimensions() const requires DerivedMagnitude<M> {
            std::string dimension_names;
            std::apply([&](auto... dim) {
                (
                    (dimension_names +=
                        zero::split_str(zero::types::type_name<decltype(dim)>(), "::").back() + ", "
                    ), ...
                );
            }, typename M::derived_dimension::dimensions{});
            auto magnitude_str_t = zero::split_str(zero::types::type_name<M>(), "::").back();
            std::cout << magnitude_str_t << " has dimensions of: ["
                << dimension_names.substr(0, dimension_names.size() - 2) << "]\n";
        }
    };

    /**
     * @brief Sum of two scalar values in a binary expression for the - operator
     * @return the resultant scalar value of adding the amount of the two quantities, with
     * the return type of the one that has the bigger ratio given their common dimension
     */
    template<BaseMagnitude M1, BaseMagnitude M2, ValidAmountType T1 = double, ValidAmountType T2 = T1>
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
     * @brief same as the operator+() overload for the {@link BaseMagnitude}, but for {@link DerivedMagnitude}
     */
    template<DerivedMagnitude DM1, DerivedMagnitude DM2, ValidAmountType T1 = double, ValidAmountType T2 = T1>
//        requires SameDimensions // <-- this is a TODO <M1, M2>
    [[nodiscard]]
    constexpr auto operator+(const quantity<DM1, T1>& lhs, const quantity<DM2, T2>& rhs) {
        using dm1_dimensions = typename DM1::derived_dimension::dimensions;
        using dm2_dimensions = typename DM2::derived_dimension::dimensions;

        constexpr double dm1_dimensionality = DM1::dimensionality;
        constexpr double dm2_dimensionality = DM2::dimensionality;

        return (lhs.amount * dm1_dimensionality) + (rhs.amount * dm2_dimensionality);
    }


    /**
     * @brief Subtraction of two scalar values in a binary expression for the - operator
     * @return the resultant scalar value of subtracting the amount of the two quantities, with
     * the return type of the one that has the bigger ratio given their common dimension
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
     * @brief Multiplication of two scalar values in a binary expression for the - operator
     * @return the resultant scalar value of multiply the amount of the two quantities, with
     * the return type of the one that has the bigger ratio given their common dimension
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
     * @brief Division of two scalar values in a binary expression for the - operator
     * @return the resultant scalar value of divide the amount of the two quantities, with
     * the return type of the one that has the bigger ratio given their common dimension
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
static_assert(zero::physics::Magnitude<zero::physics::kilogram>);

/* Testing our derived units */
//static_assert(zero::physics::DerivedUnit<zero::physics::MetersPerSecond>);

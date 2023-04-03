/**
 * @brief Module for design types and behavior associated with Physical Quantities.
 * 
 * A physical quantity can be understand as a real world magnitude, related with
 * their units in the international system
 */
export module physics.quantities:quantity;

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
        DerivedDimension<typename T::derived_dimension>;
    };

    template <typename T>
    concept Magnitude = is_base_magnitude<T>::value || DerivedMagnitude<T>;

    template <typename T, typename R>
    concept SameDimension = requires {
        requires BaseMagnitude<T> && BaseMagnitude<R>;
        requires std::is_same_v<
            typename T::dimension,
            typename R::dimension
        >;
    };

    template <typename T, typename R>
    concept SameDimensions = requires {
        requires DerivedMagnitude<T> && DerivedMagnitude<R>;
        requires std::is_same_v<
            typename T::derived_dimension,
            typename R::derived_dimension
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

        /**
         * Converts a quantity of a dimension to another one with the same dimension
         */
        template <Magnitude Target>
        constexpr auto to() const noexcept -> quantity<Target, T> {
            if constexpr (is_base_magnitude<Target>::value)
                return quantity<Target, T>(amount * (Target::ratio::value / M::ratio::value));
            else
                return quantity<Target, T>((amount * M::dimensionality) / Target::dimensionality);
        }

        /**
         * @return an {@link std::vector} with the dimensions declared for the Magnitude M
         * as {@link std::string}
         */
        template <typename Dummy = void, typename = std::enable_if_t<DerivedMagnitude<M>, Dummy>>
        std::vector<std::string> dimensions() const {
            std::vector<std::string> stringified_dimensions;
            std::apply([&](auto... dim) {
                ((stringified_dimensions.emplace_back(zero::split_str(zero::types::type_name<decltype(dim)>()).back())), ...);
            }, typename M::derived_dimension::dimensions{});
            return stringified_dimensions;
        }

        /**
         * prints a formatted version of the dimensions that are declared for the Magnitude M
         */
        template <typename Dummy = void, typename = std::enable_if_t<DerivedMagnitude<M>, Dummy>>
        void print_dimensions() const requires DerivedMagnitude<M> {
            std::string dimension_names;
            std::apply([&](auto... dim) {
                ((dimension_names +=
                    zero::split_str(zero::types::type_name<decltype(dim)>(), "::").back() + ", "
                ), ...);
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
        constexpr auto m1_ratio_v = M1::ratio::value;
        constexpr auto m2_ratio_v = M2::ratio::value;

        if constexpr (m1_ratio_v > m2_ratio_v)
            return quantity<M1, T1>(
                (lhs.amount * m1_ratio_v + rhs.amount * m2_ratio_v) / m1_ratio_v
            );
        else
            return quantity<M2, T2>(
                (lhs.amount * m1_ratio_v + rhs.amount * m2_ratio_v) / m2_ratio_v
            );
    }

    /**
     * @brief same as the operator+() overload for the {@link BaseMagnitude}, but for {@link DerivedMagnitude}
     */
    template<DerivedMagnitude DM1, DerivedMagnitude DM2, ValidAmountType T1 = double, ValidAmountType T2 = T1>
        requires SameDimensions<DM1, DM2>
    [[nodiscard]]
    consteval auto operator+(const quantity<DM1, T1>& lhs, const quantity<DM2, T2>& rhs) {
        constexpr double dm1_dimensionality = DM1::dimensionality;
        constexpr double dm2_dimensionality = DM2::dimensionality;

        if constexpr (dm1_dimensionality > dm2_dimensionality)
            return quantity<DM1, T1>((lhs.amount * dm1_dimensionality) + (rhs.amount * dm2_dimensionality));
        else
            return quantity<DM2, T2>((lhs.amount * dm1_dimensionality) + (rhs.amount * dm2_dimensionality));
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
        constexpr auto m1_ratio_v = M1::ratio::value;
        constexpr auto m2_ratio_v = M2::ratio::value;

        if constexpr (m1_ratio_v > m2_ratio_v)
            return quantity<M1, T1>(
                (lhs.amount * m1_ratio_v - rhs.amount * m2_ratio_v) / m1_ratio_v
            );
        else
            return quantity<M2, T2>(
                (lhs.amount * m1_ratio_v - rhs.amount * m2_ratio_v) / m2_ratio_v
            );
    }

    /**
     * @brief same as the operator-() overload for the {@link BaseMagnitude}, but for {@link DerivedMagnitude}
     */
    template<DerivedMagnitude DM1, DerivedMagnitude DM2, ValidAmountType T1 = double, ValidAmountType T2 = T1>
        requires SameDimensions<DM1, DM2>
    [[nodiscard]]
    consteval auto operator-(const quantity<DM1, T1>& lhs, const quantity<DM2, T2>& rhs) {
        constexpr double dm1_dimensionality = DM1::dimensionality;
        constexpr double dm2_dimensionality = DM2::dimensionality;

        if constexpr (dm1_dimensionality > dm2_dimensionality)
            return quantity<DM1, T1>((lhs.amount * dm1_dimensionality) - (rhs.amount * dm2_dimensionality));
        else
            return quantity<DM2, T2>((lhs.amount * dm1_dimensionality) - (rhs.amount * dm2_dimensionality));
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
        constexpr auto m1_ratio_v = M1::ratio::value;
        constexpr auto m2_ratio_v = M2::ratio::value;

        if constexpr (m1_ratio_v > m2_ratio_v)
            return quantity<M1, T1>(
                (lhs.amount * m1_ratio_v * rhs.amount * m2_ratio_v) / m1_ratio_v
            );
        else
            return quantity<M2, T2>(
                (lhs.amount * m1_ratio_v * rhs.amount * m2_ratio_v) / m2_ratio_v
            );
    }

    /**
     * @brief same as the operator*() overload for the {@link BaseMagnitude}, but for {@link DerivedMagnitude}
     */
    template<DerivedMagnitude DM1, DerivedMagnitude DM2, ValidAmountType T1 = double, ValidAmountType T2 = T1>
        requires SameDimensions<DM1, DM2>
    [[nodiscard]]
    consteval auto operator*(const quantity<DM1, T1>& lhs, const quantity<DM2, T2>& rhs) {
        constexpr double dm1_dimensionality = DM1::dimensionality;
        constexpr double dm2_dimensionality = DM2::dimensionality;

        if constexpr (dm1_dimensionality > dm2_dimensionality)
            return quantity<DM1, T1>((lhs.amount * dm1_dimensionality) * (rhs.amount * dm2_dimensionality));
        else
            return quantity<DM2, T2>((lhs.amount * dm1_dimensionality) * (rhs.amount * dm2_dimensionality));
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
        constexpr auto m1_ratio_v = M1::ratio::value;
        constexpr auto m2_ratio_v = M2::ratio::value;

        if constexpr (m1_ratio_v > m2_ratio_v)
            return quantity<M1, T1>(
                ((lhs.amount * m1_ratio_v) / (rhs.amount * m2_ratio_v)) / m1_ratio_v
            );
        else
            return quantity<M2, T2>(
                ((lhs.amount * m1_ratio_v) / (rhs.amount * m2_ratio_v)) / m2_ratio_v
            );
    }

    /**
    * @brief same as the operator/() overload for the {@link BaseMagnitude}, but for {@link DerivedMagnitude}
    */
    template<DerivedMagnitude DM1, DerivedMagnitude DM2, ValidAmountType T1 = double, ValidAmountType T2 = T1>
        requires SameDimensions<DM1, DM2>
    [[nodiscard]]
    consteval auto operator/(const quantity<DM1, T1>& lhs, const quantity<DM2, T2>& rhs) {
        constexpr double dm1_dimensionality = DM1::dimensionality;
        constexpr double dm2_dimensionality = DM2::dimensionality;

        if constexpr (dm1_dimensionality > dm2_dimensionality)
            return quantity<DM1, T1>((lhs.amount * dm1_dimensionality) / (rhs.amount * dm2_dimensionality));
        else
            return quantity<DM2, T2>((lhs.amount * dm1_dimensionality) / (rhs.amount * dm2_dimensionality));
    }

    // TODO this template recursive function isn't linking from the details
    // partition module, so it must be in the public API until we found a better solution
    template<typename M, int N = 1>
    void derived_magnitude_symbols(std::string& out) {
        if constexpr (N == 1)
            out += " ";

        using type = typename std::tuple_element<N - 1, typename M::units>::type;
        const auto total_elements = std::tuple_size<typename M::units>::value;
        const int dim_exp = std::tuple_element<N - 1, typename M::derived_dimension::dimensions>::type::dimension_exp;

        auto splitted = zero::split_str(zero::types::type_name<type>(), "::").back();
        auto s_symbol = splitted.substr(0, splitted.length() - 1);

        out += s_symbol;

        if constexpr (dim_exp != 1)
            out += std::to_string(dim_exp);
        if constexpr (total_elements > N)
            out += std::string{"*"};

        if constexpr (N - 1 < total_elements - 1)
            derived_magnitude_symbols<M, N + 1>(out);
    }

    /**
     * Sends to an output stream a formatted version of some {@link quantity}
     */
    template<typename M>
    constexpr std::ostream& operator<<(std::ostream& os, const quantity<M>& q) {
        if constexpr (is_base_magnitude<M>::value)
            os << q.amount << " " << zero::split_str(zero::types::type_name<typename M::symbol>(), "::").back();
        else {
            std::string out;
            derived_magnitude_symbols<M>(out);
            os << q.amount << out;
        }

        return os;
    }
}


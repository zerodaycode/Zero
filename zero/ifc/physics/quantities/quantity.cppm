/**
 * @brief Module for design types and behavior associated with Physical Quantities.
 *
 * A physical quantity can be understood as a real-world magnitude, related with their units in the
 * international system.
 *
 * This module provides a class template called `quantity`, which represents a measurable property
 * of a physical body expressed as a scalar value with its units. The `quantity` class supports
 * various operations such as addition, subtraction, multiplication, and division, as well as unit
 * conversions between different magnitudes.
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
import :quantities.detail;

/**
 * @brief Concept representing a base magnitude, which is an object that can be used to measure a
 * physical quantity.
 *
 * A base magnitude has a dimension and a unit associated with it. This concept is used as a
 * constraint for the `quantity` class template.
 */
template<typename T>
concept BaseMagnitude = requires {
    BaseUnit<T>;
    BaseDimension<typename T::dimension>;
};

/**
 * @brief Concept representing a derived magnitude, which is an object that can be used to measure a
 * physical quantity composed of multiple base magnitudes.
 *
 * A derived magnitude has a dimension and a unit associated with it. This concept is used as a
 * constraint for the `quantity` class template.
 */
template<typename T>
concept DerivedMagnitude = requires {
    DerivedUnit<T>;
    DerivedDimension<typename T::derived_dimension>;
};

/**
 * @brief Concept representing an arbitrary magnitude, which can be either a base or derived
 * magnitude.
 *
 * This concept is used to constrain the types of objects that can be used with the `quantity` class
 * template.
 */
template<typename T>
concept Magnitude = is_base_magnitude<T>::value || DerivedMagnitude<T>;

/**
 * @brief Concept representing two magnitudes with the same dimension.
 *
 * This concept is used as a constraint for operations such as addition and subtraction, where the
 * units of the operands must be compatible.
 */
template<typename T1, typename T2>
concept SameDimension = requires {
    requires BaseMagnitude<T1> && BaseMagnitude<T2>;
    requires std::is_same_v<typename T1::dimension, typename T2::dimension>;
};

/**
 * @brief Concept representing two magnitudes with the same dimension and derived dimension.
 *
 * This concept is used as a constraint for operations such as addition and subtraction, where the
 * units of the operands must be compatible.
 */
template<typename T1, typename T2>
concept SameDimensions = requires {
    requires DerivedMagnitude<T1> && DerivedMagnitude<T2>;
    requires std::is_same_v<typename T1::derived_dimension, typename T2::derived_dimension>;
};

/**
 * @brief Concept representing a valid amount type for the quantity class template.
 *
 * This concept constrains the types of objects that can be used to represent the scalar numeric
 * value associated with a physical quantity.
 */
template<typename T>
concept ValidAmountType =
    (std::is_integral_v<T> || std::is_floating_point_v<T>) && !std::is_same_v<T, char>;

/**
 * @brief Represents a measurable property of a physical body, expressed in terms of a scalar value
 * with their units.
 *
 * The `quantity` class template is the central concept in this module. It provides a way to
 * represent and manipulate physical quantities using various operations such as addition,
 * subtraction, multiplication, and division.
 */
template<Magnitude M, ValidAmountType T = double>
struct quantity {
    /**
     * @brief The scalar numeric value associated with the physical quantity.
     *
     * This member variable represents the actual numerical value of the physical quantity, without
     * any units.
     */
    T amount;

    /**
     * @brief Default constructor for the `quantity` class template.
     *
     * This constructor is used to create an object with a default amount value (usually 0) and no
     * specific unit.
     */
    constexpr quantity<M, T>() noexcept = default;

    /**
     * @brief Explicit constructor for the `quantity` class template.
     *
     * This constructor is used to create an object with a specific amount value and unit. The type
     * of the unit must match the dimension of the magnitude specified in the template parameters.
     *
     * @param val The scalar numeric value associated with the physical quantity.
     */
    constexpr explicit quantity<M, T>(T val) noexcept: amount(val) {}

    /**
     * @brief Converts a quantity of a given dimension to another one with the same dimension.
     *
     * This function is used to perform unit conversions between different magnitudes that have the
     * same dimension. The result is a new `quantity` object with the converted value and units.
     *
     * @tparam Target The target magnitude type, which must be compatible with the original
     * magnitude specified in the template parameters.
     *
     * @return A new `quantity` object with the converted value and units.
     */
    template<Magnitude Target>
    constexpr auto to() const noexcept -> quantity<Target, T> {
        if constexpr (is_base_magnitude<Target>::value)
            return quantity<Target, T>(
                amount * M::ratio::value / Target::ratio::value * M::ratio::base_denominator
                / Target::ratio::base_denominator
            );
        else
            return quantity<Target, T>((amount * M::dimensionality) / Target::dimensionality);
    }

    /**
     * @brief Returns an array of strings representing the dimensions declared for the magnitude
     * specified in the template parameters.
     *
     * This function is used to retrieve information about the units associated with a physical
     * quantity. The result is an array of strings that describe the dimensionality of the quantity.
     *
     * @tparam Dummy A placeholder type parameter (not actually used).
     *
     * @return An array of strings representing the dimensions declared for the magnitude specified
     * in the template parameters.
     */
    template<typename Dummy = void, typename = std::enable_if_t<DerivedMagnitude<M>, Dummy>>
    std::vector<std::string> dimensions() const {
        std::vector<std::string> stringified_dimensions;
        std::apply(
            [&](auto... dim) {
                ((stringified_dimensions.emplace_back(
                     zero::split_str(zero::types::type_name<decltype(dim)>()).back()
                 )),
                 ...);
            },
            typename M::derived_dimension::dimensions {}
        );
        return stringified_dimensions;
    }

    /**
     * @brief Prints a formatted version of the dimensions declared for the magnitude specified in
     * the template parameters.
     *
     * This function is used to display information about the units associated with a physical
     * quantity. The output includes the name of the quantity and its dimensionality, displayed as a
     * list of strings.
     */
    template<typename Dummy = void, typename = std::enable_if_t<DerivedMagnitude<M>, Dummy>>
    void print_dimensions() const
        requires DerivedMagnitude<M>
    {
        std::string dimension_names;
        std::apply(
            [&](auto... dim) {
                ((dimension_names +=
                  zero::split_str(zero::types::type_name<decltype(dim)>(), "::").back() + ", "),
                 ...);
            },
            typename M::derived_dimension::dimensions {}
        );
        auto magnitude_str_t = zero::split_str(zero::types::type_name<M>(), "::").back();
        std::cout << magnitude_str_t << " has dimensions of: ["
                  << dimension_names.substr(0, dimension_names.size() - 2) << "]\n";
    }
};

/**
 * @brief Sums two scalar values in a binary expression for the + operator.
 *
 * This function is used to perform addition operations on `quantity` objects with compatible units.
 * The result is a new `quantity` object with the sum of the amounts and the same unit as the
 * operands.
 *
 * @tparam M1 The type of the first operand, which must be a magnitude.
 * @tparam M2 The type of the second operand, which must be a magnitude and have the same dimension
 * as M1.
 * @tparam T1 The type of the amount associated with the first operand.
 * @tparam T2 The type of the amount associated with the second operand.
 *
 * @return A new `quantity` object with the sum of the amounts and the same unit as the operands.
 */
template<BaseMagnitude M1, BaseMagnitude M2, ValidAmountType T1 = double, ValidAmountType T2 = T1>
    requires SameDimension<M1, M2>
[[nodiscard]]
constexpr auto operator+(const quantity<M1, T1>& lhs, const quantity<M2, T2>& rhs)
    -> quantity<std::conditional_t<(M1::ratio::value > M2::ratio::value), M1, M2>> {
    constexpr auto m1_ratio_v = M1::ratio::value;
    constexpr auto m2_ratio_v = M2::ratio::value;

    if constexpr (m1_ratio_v > m2_ratio_v)
        return quantity<M1, T1>((lhs.amount * m1_ratio_v + rhs.amount * m2_ratio_v) / m1_ratio_v);
    else
        return quantity<M2, T2>((lhs.amount * m1_ratio_v + rhs.amount * m2_ratio_v) / m2_ratio_v);
}

/**
 * @brief Same as the operator+() overload for BaseMagnitude, but for DerivedMagnitude.
 *
 * This function is used to perform addition operations on `quantity` objects with compatible units.
 * The result is a new `quantity` object with the sum of the amounts and the same unit as the
 * operands.
 *
 * @tparam DM1 The type of the first operand, which must be a derived magnitude.
 * @tparam DM2 The type of the second operand, which must be a derived magnitude and have the same
 * dimension as DM1.
 * @tparam T1 The type of the amount associated with the first operand.
 * @tparam T2 The type of the amount associated with the second operand.
 *
 * @return A new `quantity` object with the sum of the amounts and the same unit as the operands.
 */
template<
    DerivedMagnitude DM1,
    DerivedMagnitude DM2,
    ValidAmountType T1 = double,
    ValidAmountType T2 = T1>
    requires SameDimensions<DM1, DM2>
[[nodiscard]]
consteval auto operator+(const quantity<DM1, T1>& lhs, const quantity<DM2, T2>& rhs) {
    constexpr double dm1_dimensionality = DM1::dimensionality;
    constexpr double dm2_dimensionality = DM2::dimensionality;

    if constexpr (dm1_dimensionality > dm2_dimensionality)
        return quantity<DM1, T1>(
            (lhs.amount * dm1_dimensionality) + (rhs.amount * dm2_dimensionality)
        );
    else
        return quantity<DM2, T2>(
            (lhs.amount * dm1_dimensionality) + (rhs.amount * dm2_dimensionality)
        );
}

/**
 * @brief Subtracts two scalar values in a binary expression for the - operator.
 *
 * This function is used to perform subtraction operations on `quantity` objects with compatible
 * units. The result is a new `quantity` object with the difference of the amounts and the same unit
 * as the operands.
 *
 * @tparam M1 The type of the first operand, which must be a magnitude.
 * @tparam M2 The type of the second operand, which must be a magnitude and have the same dimension
 * as M1.
 * @tparam T1 The type of the amount associated with the first operand.
 * @tparam T2 The type of the amount associated with the second operand.
 *
 * @return A new `quantity` object with the difference of the amounts and the same unit as the
 * operands.
 */
template<Magnitude M1, Magnitude M2, ValidAmountType T1 = double, ValidAmountType T2 = T1>
    requires SameDimension<M1, M2>
[[nodiscard]]
constexpr auto operator-(const quantity<M1, T1>& lhs, const quantity<M2, T2>& rhs)
    -> quantity<std::conditional_t<(M1::ratio::value > M2::ratio::value), M1, M2>> {
    constexpr auto m1_ratio_v = M1::ratio::value;
    constexpr auto m2_ratio_v = M2::ratio::value;

    if constexpr (m1_ratio_v > m2_ratio_v)
        return quantity<M1, T1>((lhs.amount * m1_ratio_v - rhs.amount * m2_ratio_v) / m1_ratio_v);
    else
        return quantity<M2, T2>((lhs.amount * m1_ratio_v - rhs.amount * m2_ratio_v) / m2_ratio_v);
}

/**
 * @brief Same as the operator-() overload for BaseMagnitude, but for DerivedMagnitude.
 *
 * This function is used to perform subtraction operations on `quantity` objects with compatible
 * units. The result is a new `quantity` object with the difference of the amounts and the same unit
 * as the operands.
 *
 * @tparam DM1 The type of the first operand, which must be a derived magnitude.
 * @tparam DM2 The type of the second operand, which must be a derived magnitude and have the same
 * dimension as DM1.
 * @tparam T1 The type of the amount associated with the first operand.
 * @tparam T2 The type of the amount associated with the second operand.
 *
 * @return A new `quantity` object with the difference of the amounts and the same unit as the
 * operands.
 */
template<
    DerivedMagnitude DM1,
    DerivedMagnitude DM2,
    ValidAmountType T1 = double,
    ValidAmountType T2 = T1>
    requires SameDimensions<DM1, DM2>
[[nodiscard]]
consteval auto operator-(const quantity<DM1, T1>& lhs, const quantity<DM2, T2>& rhs) {
    constexpr double dm1_dimensionality = DM1::dimensionality;
    constexpr double dm2_dimensionality = DM2::dimensionality;

    if constexpr (dm1_dimensionality > dm2_dimensionality)
        return quantity<DM1, T1>(
            (lhs.amount * dm1_dimensionality) - (rhs.amount * dm2_dimensionality)
        );
    else
        return quantity<DM2, T2>(
            (lhs.amount * dm1_dimensionality) - (rhs.amount * dm2_dimensionality)
        );
}

/**
 * @brief Multiplies two scalar values in a binary expression for the \* operator.
 *
 * This function is used to perform multiplication operations on `quantity` objects with compatible
 * units. The result is a new `quantity` object with the product of the amounts and the same unit as
 * the operands.
 *
 * @tparam M1 The type of the first operand, which must be a magnitude.
 * @tparam M2 The type of the second operand, which must be a magnitude and have the same dimension
 * as M1.
 * @tparam T1 The type of the amount associated with the first operand.
 * @tparam T2 The type of the amount associated with the second operand.
 *
 * @return A new `quantity` object with the product of the amounts and the same unit as the
 * operands.
 */
template<Magnitude M1, Magnitude M2, ValidAmountType T1 = double, ValidAmountType T2 = T1>
    requires SameDimension<M1, M2>
[[nodiscard]]
constexpr auto operator*(const quantity<M1, T1>& lhs, const quantity<M2, T2>& rhs)
    -> quantity<std::conditional_t<(M1::ratio::value > M2::ratio::value), M1, M2>> {
    constexpr auto m1_ratio_v = M1::ratio::value;
    constexpr auto m2_ratio_v = M2::ratio::value;

    if constexpr (m1_ratio_v > m2_ratio_v)
        return quantity<M1, T1>((lhs.amount * m1_ratio_v * rhs.amount * m2_ratio_v) / m1_ratio_v);
    else
        return quantity<M2, T2>((lhs.amount * m1_ratio_v * rhs.amount * m2_ratio_v) / m2_ratio_v);
}

/**
 * @brief Same as the operator\*() overload for BaseMagnitude, but for DerivedMagnitude.
 *
 * This function is used to perform multiplication operations on `quantity` objects with compatible
 * units. The result is a new `quantity` object with the product of the amounts and the same unit as
 * the operands.
 *
 * @tparam DM1 The type of the first operand, which must be a derived magnitude.
 * @tparam DM2 The type of the second operand, which must be a derived magnitude and have the same
 * dimension as DM1.
 * @tparam T1 The type of the amount associated with the first operand.
 * @tparam T2 The type of the amount associated with the second operand.
 *
 * @return A new `quantity` object with the product of the amounts and the same unit as the
 * operands.
 */
template<
    DerivedMagnitude DM1,
    DerivedMagnitude DM2,
    ValidAmountType T1 = double,
    ValidAmountType T2 = T1>
    requires SameDimensions<DM1, DM2>
[[nodiscard]]
consteval auto operator*(const quantity<DM1, T1>& lhs, const quantity<DM2, T2>& rhs) {
    constexpr double dm1_dimensionality = DM1::dimensionality;
    constexpr double dm2_dimensionality = DM2::dimensionality;

    if constexpr (dm1_dimensionality > dm2_dimensionality)
        return quantity<DM1, T1>(
            (lhs.amount * dm1_dimensionality) * (rhs.amount * dm2_dimensionality)
        );
    else
        return quantity<DM2, T2>(
            (lhs.amount * dm1_dimensionality) * (rhs.amount * dm2_dimensionality)
        );
}

/**
 * @brief Divides two scalar values in a binary expression for the / operator.
 *
 * This function is used to perform division operations on `quantity` objects with compatible units.
 * The result is a new `quantity` object with the quotient of the amounts and the same unit as the
 * operands.
 *
 * @tparam M1 The type of the first operand, which must be a magnitude.
 * @tparam M2 The type of the second operand, which must be a magnitude and have the same dimension
 * as M1.
 * @tparam T1 The type of the amount associated with the first operand.
 * @tparam T2 The type of the amount associated with the second operand.
 *
 * @return A new `quantity` object with the quotient of the amounts and the same unit as the
 * operands.
 */
template<Magnitude M1, Magnitude M2, ValidAmountType T1 = double, ValidAmountType T2 = T1>
    requires SameDimension<M1, M2>
[[nodiscard]]
constexpr auto operator/(const quantity<M1, T1>& lhs, const quantity<M2, T2>& rhs)
    -> quantity<std::conditional_t<(M1::ratio::value > M2::ratio::value), M1, M2>> {
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
 * @brief Same as the operator/() overload for BaseMagnitude, but for DerivedMagnitude.
 *
 * This function is used to perform division operations on `quantity` objects with compatible units.
 * The result is a new `quantity` object with the quotient of the amounts and the same unit as the
 * operands.
 *
 * @tparam DM1 The type of the first operand, which must be a derived magnitude.
 * @tparam DM2 The type of the second operand, which must be a derived magnitude and have the same
 * dimension as DM1.
 * @tparam T1 The type of the amount associated with the first operand.
 * @tparam T2 The type of the amount associated with the second operand.
 *
 * @return A new `quantity` object with the quotient of the amounts and the same unit as the
 * operands.
 */
template<
    DerivedMagnitude DM1,
    DerivedMagnitude DM2,
    ValidAmountType T1 = double,
    ValidAmountType T2 = T1>
    requires SameDimensions<DM1, DM2>
[[nodiscard]]
consteval auto operator/(const quantity<DM1, T1>& lhs, const quantity<DM2, T2>& rhs) {
    constexpr double dm1_dimensionality = DM1::dimensionality;
    constexpr double dm2_dimensionality = DM2::dimensionality;

    if constexpr (dm1_dimensionality > dm2_dimensionality)
        return quantity<DM1, T1>(
            (lhs.amount * dm1_dimensionality) / (rhs.amount * dm2_dimensionality)
        );
    else
        return quantity<DM2, T2>(
            (lhs.amount * dm1_dimensionality) / (rhs.amount * dm2_dimensionality)
        );
}

/**
 * @brief Sends a formatted version of the quantity to an output stream.
 *
 * This function is used to display information about the units associated with a physical quantity.
 * The output includes the name of the quantity and its value, displayed in a human-readable format.
 *
 * @tparam M The type of the magnitude associated with the quantity.
 *
 * @param os The output stream where the formatted version will be sent.
 * @param q The `quantity` object to be formatted.
 *
 * @return A reference to the input output stream.
 */
template<typename M>
constexpr std::ostream& operator<<(std::ostream& os, const quantity<M>& q) {
    if constexpr (is_base_magnitude<M>::value)
        os << q.amount << " "
           << zero::split_str(zero::types::type_name<typename M::symbol>(), "::").back();
    else {
        std::string out;
        derived_magnitude_symbols<M>(out);
        os << q.amount << out;
    }

    return os;
}

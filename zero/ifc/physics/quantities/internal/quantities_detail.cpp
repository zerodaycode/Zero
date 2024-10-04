/**
 * @brief Partition for holding the implementation details that won't contribute to the external API
 * of the units module.
 *
 * Due to the recursive function template for formatting the derived magnitude symbols, we can't use
 * this as an internal partition, due to the linker is not able to resolve the template in order to
 * link it at call site
 */

export module physics.quantities:quantities.detail;

import std;

import type_info;
import str_manip;

/**
 * @brief Helper struct for extracting exponents of base dimensions from a tuple of derived
 * dimensions.
 *
 * This struct is used to calculate the total dimensionality of a derived unit by multiplying the
 * exponents of its base dimensions.
 */
template<typename T>
struct dimensions_exponents;

/**
 * @brief Specialization of dimensions_exponents for tuples of base dimensions.
 */
template<typename... BaseDimensions>
struct dimensions_exponents<std::tuple<BaseDimensions...>> {
    /**
     * @brief Array containing the dimension exponents of each base dimension.
     *
     * This array is used to calculate the total dimensionality by multiplying its elements.
     */
    static constexpr auto value = std::array<short, sizeof...(BaseDimensions)> {
        BaseDimensions::base_dimension::dimension::dimension_exp...
    };
};

/**
 * @brief Helper struct for extracting ratios from a tuple of base units.
 *
 * This struct is used to calculate the total ratio of a derived unit by multiplying the ratios of
 * its base units.
 */
template<typename T>
struct ratios_detail;

/**
 * @brief Specialization of ratios_detail for tuples of base units.
 */
template<typename... BaseUnits>
struct ratios_detail<std::tuple<BaseUnits...>> {
    /**
     * @brief Tuple containing the ratios of each base unit.
     *
     * This tuple is used to calculate the total ratio by multiplying its elements.
     */
    using ratios = std::tuple<typename BaseUnits::ratio...>;
};

/**
 * @brief Helper struct for calculating the product of a tuple of ratios.
 *
 * This struct is used to calculate the total ratio of a derived unit by multiplying the ratios of
 * its base units.
 */
template<typename T>
struct ratios_product_calculator;

/**
 * @brief Specialization of ratios_product_calculator for tuples of base units.
 */
template<typename... BaseUnitsRatios>
struct ratios_product_calculator<std::tuple<BaseUnitsRatios...>> {
    /**
     * @brief The product of the ratios in the tuple.
     *
     * This value is calculated by multiplying the elements of the tuple.
     */
    static constexpr auto value = (1 * ... * BaseUnitsRatios::value);
};

/**
 * @brief Recursively formats the derived magnitude symbols.
 *
 * This function template appends the symbols and exponents of each base dimension to an output
 * string.
 *
 * @param out The output string to append the derived magnitude symbols to.
 * @tparam M The type of the derived magnitude.
 * @tparam N The current index in the tuple of base dimensions (starts at 1).
 */
template<typename M, int N = 1>
void derived_magnitude_symbols(std::string& out) {
    if constexpr (N == 1)
        out += " ";

    using type = typename std::tuple_element<N - 1, typename M::units>::type;
    const auto total_elements = std::tuple_size<typename M::units>::value;
    const int dim_exp =
        std::tuple_element<N - 1, typename M::derived_dimension::dimensions>::type::dimension_exp;

    /**
     * @brief The symbol of the current base dimension.
     *
     * This is obtained by splitting the type name and taking the last part (after "::").
     */
    auto splitted = zero::split_str(zero::types::type_name<type>(), "::").back();
    auto s_symbol = splitted.substr(0, splitted.length() - 1);

    out += s_symbol;

    /**
     * @brief The exponent of the current base dimension.
     *
     * This is obtained by accessing the `dimension_exp` member of the base dimension struct.
     */
    if constexpr (dim_exp != 1)
        out += std::to_string(dim_exp);
    if constexpr (total_elements > N)
        out += "*";

    /**
     * @brief Recursively format the remaining derived magnitude symbols.
     *
     * This is done by calling `derived_magnitude_symbols` with the next index in the tuple of base
     * dimensions.
     */
    if constexpr (N - 1 < total_elements - 1)
        derived_magnitude_symbols<M, N + 1>(out);
}

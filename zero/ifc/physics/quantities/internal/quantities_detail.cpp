/**
 * @brief Partition for holding the implementation
 * details that won't contribute to the external API of the
 * units module.
 *
 * Due to the recursive function template for
 * formatting the `derived magnitude symbols`, we can't use
 * this as an internal partition, due to the linker is not able
 * to resolve the template in order to link it at call site
 */

export module physics.quantities:quantities.detail;

import std;

import type_info;
import str_manip;

export namespace quantities::__detail {
    template<typename T>
    struct dimensions_exponents;

    template<typename... BaseDimensions>
    struct dimensions_exponents<std::tuple<BaseDimensions...>> {
        static constexpr auto value = std::array<short, sizeof...(BaseDimensions)> {BaseDimensions::base_dimension::dimension::dimension_exp...};
    };

    template<typename T>
    struct ratios_detail;

    template<typename... BaseUnits>
    struct ratios_detail<std::tuple<BaseUnits...>> {
        using ratios = std::tuple<typename BaseUnits::ratio...>;
    };

    template <typename T>
    struct ratios_product_calculator;

    template<typename... BaseUnitsRatios>
    struct ratios_product_calculator<std::tuple<BaseUnitsRatios...>> {
        static constexpr auto value = (1 * ... * BaseUnitsRatios::value);
    };

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
            out += "*";

        if constexpr (N - 1 < total_elements - 1)
            derived_magnitude_symbols<M, N + 1>(out);
    }
}
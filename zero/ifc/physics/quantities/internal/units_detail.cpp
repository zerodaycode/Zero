/**
 * @brief Internal partition for holding the implementation
 * details that won't contribute to the external API of the
 * units module
 */

module physics.quantities:units.detail;

import std;

export namespace units::__detail {
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
}
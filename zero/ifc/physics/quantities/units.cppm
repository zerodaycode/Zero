/**
* @brief Predefined physical units based on the definitions
 * provided by the international system
*/

export module physics:units;

import std;

import concepts;
import :ratios;
import :dimensions;
import :units.symbols;

export namespace zero::physics {
    /* Base units */
    template<Ratio r, Symbol s>
    struct base_unit {
        using ratio = r;
        using symbol = s;
    };

    template <typename T>
    concept BaseUnit =
        Ratio<typename T::ratio> &&
        Symbol<typename T::symbol> &&
    requires {
        typename T::ratio;
        typename T::symbol;
    };

    struct Kilogram: public mass<1>, public base_unit<Kilo, kg> {};
    struct Hectogram: public mass<1>, public base_unit<Hecto, hg> {};
    struct Meter: public length<1>, public base_unit<Root, m> {};

    template<typename T>
    struct ratios_detail;

    template<BaseUnit... BaseUnits>
    struct ratios_detail<std::tuple<BaseUnits...>> {
        using ratios = std::tuple<typename BaseUnits::ratio...>;
    };

    template <typename T>
    struct ratios_product_calculator;

    template<Ratio... BaseUnitsRatios>
    struct ratios_product_calculator<std::tuple<BaseUnitsRatios...>> {
        static constexpr auto value = (1 * ... * BaseUnitsRatios::value);
    };

    /* Derived units */
    template <typename DerivedDim, BaseUnit... BaseUnits>
        requires (DerivedDimension<DerivedDim>)
    struct derived_unit {
        using units = std::tuple<BaseUnits...>;
        using ratios = typename ratios_detail<units>::ratios;
        static constexpr auto ratios_product = ratios_product_calculator<ratios>::value;

//        static constexpr double dimensionality = [] {
//            double product = 1;
//            std::size_t i = 0;
//            ((product *= std::pow(std::get<i++>(typename DerivedDim::dimensions{})::dimension_exp * BaseUnits::ratio::value, 1.0)), ...);
//            return product;
//        }();
    };

    template <typename T>
    concept DerivedUnit = requires {
        typename T::units;
        typename T::ratios;
        T::ratios_product;
    } && std::is_base_of_v<typename T::derived_dimension, T>;

    struct MetersPerSecond :
        public speed,
        public derived_unit<
            speed,
            base_unit<Kilo, m>,
            base_unit<Hecto, s>
        >
    {};

    struct KilometersPerHour :
        public speed,
        public derived_unit<
            speed,
            base_unit<Kilo, km>,
            base_unit<Root, h>
        >
    {};
}

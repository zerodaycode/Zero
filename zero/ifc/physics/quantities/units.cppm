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
import :units.detail;

using namespace units::__detail;

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

    struct kilogram: public mass<1>, public base_unit<Kilo, kg> {};
    struct hectogram: public mass<1>, public base_unit<Hecto, hg> {};
    struct meter: public length<1>, public base_unit<Root, m> {};
    struct second: public time<1>, public base_unit<Second, s> {};
    struct hour: public time<1>, public base_unit<Hour, s> {};

    /* Derived units */
    template <typename DerivedDim, BaseUnit... BaseUnits>
        requires (DerivedDimension<DerivedDim>)
    struct derived_unit {
        using units = std::tuple<BaseUnits...>;

        static constexpr double dimensionality = []<std::size_t... Is>(std::index_sequence<Is...>) {
            using dm_exp = dimensions_exponents<typename DerivedDim::dimensions>;
            return (1.0 * ... * consteval_power(BaseUnits::ratio::value, dm_exp::value[Is]));
        } (std::make_index_sequence<DerivedDim::total_dimensions>{});
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
            base_unit<Root, m>,
            base_unit<Second, s>
        >
    {};

    struct KilometersPerHour :
        public speed,
        public derived_unit<
            speed,
            base_unit<Kilo, km>,
            base_unit<Hour, h>
        >
    {};
}

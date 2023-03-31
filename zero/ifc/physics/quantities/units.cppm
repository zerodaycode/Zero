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

    struct Kilogram: public mass<1>, public base_unit<Kilo, kg> {};
    struct Hectogram: public mass<1>, public base_unit<Hecto, hg> {};
    struct Meter: public length<1>, public base_unit<Root, m> {};



    /* Derived units */
    template <typename DerivedDim, BaseUnit... BaseUnits>
        requires (DerivedDimension<DerivedDim>)
    struct derived_unit {
        using units = std::tuple<BaseUnits...>;

        static constexpr double dimensionality = [] {
            std::size_t i = 0;
            return (1 * ... * [&i] {
                auto bd = dimensions_exponents<typename DerivedDim::dimensions>::value[i++];
                return power(BaseUnits::ratio::value, bd);
            } ());
        } ();
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

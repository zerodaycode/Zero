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


    /* Derived units */
    template <BaseUnit... baseUnits>
    struct derived_unit {
        using units = std::tuple<baseUnits...>;
    };

    template <typename T>
    concept DerivedUnit = requires {
        typename T::units;
    } && std::is_base_of_v<typename T::derived_dimension, T>;

    struct MetersPerSecond :
        public speed,
        public derived_unit<
            base_unit<Kilo, m>,
            base_unit<Root, s>
        >
    {};

    struct KilometersPerHour :
        public speed,
        public derived_unit<
            base_unit<Kilo, km>,
            base_unit<Root, h>
        >
    {};
}

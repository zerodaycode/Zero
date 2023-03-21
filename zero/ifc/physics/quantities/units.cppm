/**
* @brief Predefined physical units based on the definitions
 * provided by the international system
*/

export module physics:units;

import std;

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
    concept BaseUnit = requires {
        typename T::ratio; // && T::ratio is same v
        typename T::symbol;
    };

    struct Kilogram: public mass, public base_unit<Kilo, kg> {};
    struct Hectogram: public mass, public base_unit<Hecto, hg> {};
    struct Meter: public length, public base_unit<Root, m> {};


    /* Derived units */
    template <BaseUnit... baseUnits>
    struct derived_unit {
        using units = std::tuple<baseUnits...>;
    };

    struct MetersPerSecond :
        public speed,
        public derived_unit<
            base_unit<Root, m>,
            base_unit<Root, s>
        >
    {};
}

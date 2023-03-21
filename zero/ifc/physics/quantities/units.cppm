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
    template<Ratio r, Symbol s>
    struct base_unit {
        using ratio = r;
        using symbol = s;
    };

    /* Base units */
    struct Kilogram: public mass, public base_unit<Kilo, kg> {};
    struct Hectogram: public mass, public base_unit<Hecto, hg> {};
    struct Meter: public length, public base_unit<Root, m> {};

    /* Derived units */
    struct MetersPerSecond : public speed {
        using dimensions = speed::dimensions;
    };
}

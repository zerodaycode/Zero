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
    template<Ratio prefix, Symbol S>
    struct base_unit {};

    /* Base units */  // TODO Probably we may get rid out of the tagging inheritance of base_unit?
    struct Kilogram: public mass, public base_unit<Kilo, kg> {
        using dimension = mass;
        using ratio = Kilo;
        using symbol = kg;
    };
    struct Hectogram: public mass, public base_unit<Hecto, hg> {
        using dimension = mass;
        using ratio = Hecto;
        using symbol = hg;
    };

    struct Meter: public length, public base_unit<Root, m> {
        using dimension = length;
        using ratio = Root;
        using symbol = m;
    };

    /* Derived units */
    struct MetersPerSecond : public speed {
        using dimensions = speed::dimensions;
    };
}

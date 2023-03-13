/**
* @brief Predefined physical units based on the definitions
 * provided by the international system
*/

export module physics:units;

import :ratios;
import :dimensions;
import :units.symbols;

export namespace zero::physics {
    template<Ratio prefix, Symbol S>
    struct base_unit {};

    // TODO inline namespace?
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
        using ratio = Hecto;
        using symbol = m;
    };
}
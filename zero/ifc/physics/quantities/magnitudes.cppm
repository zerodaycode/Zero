/**
* @brief Predefined physical magnitudes based on the definitions
 * provided by the international system
*/

export module physics:magnitudes;

import :ratios;
import :dimensions;
import :magnitudes.symbols;

export namespace zero::physics {
    // TODO inline namespace?
    struct Kilogram: public mass<Kilo, kg> {
        using dimension = mass;
        using ratio = Kilo;
        using symbol = kg;
    };
    struct Hectogram: public mass<Hecto, hg> {
        using dimension = mass;
        using ratio = Hecto;
        using symbol = hg;
    };

    struct Meter: public length<Root, m> {
        using dimension = length;
        using ratio = Hecto;
        using symbol = m;
    };
}
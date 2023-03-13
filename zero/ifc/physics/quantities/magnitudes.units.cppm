/**
* @brief Declarations of the predefined units for the magnitudes
 * defined in the international system
*/

export module physics:magnitudes.units;

import :ratios;
import :magnitudes.symbols;

export namespace zero::physics {
    template<Ratio prefix, Symbol S>
    struct base_unit {};
}
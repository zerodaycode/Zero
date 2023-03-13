/**
* @brief Physical dimensions
 *
 * A physical dimension is a characteristic of a physical quantity that can be expressed as a combination
 * of fundamental dimensions. Fundamental dimensions are independent dimensions that cannot be expressed
 * in terms of other dimensions.
 * Physical dimensions can be used to classify physical quantities and compare them based on their fundamental nature.
*/

export module physics:dimensions;

import :ratios;
import :magnitudes.symbols;
import :magnitudes.units;

export namespace zero::physics {
    template<typename Derived>
    class dimension {};

    template <Ratio R, Symbol S>
    class mass: public dimension<mass<R, S>>, public base_unit<R, S>{};
    template<Ratio R, Symbol S>
    class length: public dimension<length<R, S>>, public base_unit<R, S>{};
}
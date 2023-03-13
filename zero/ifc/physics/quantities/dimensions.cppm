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
import :units.symbols;

export namespace zero::physics {
    /* Base dimensions */
    class base_dimension {};

    class mass: public base_dimension {};
    class length: public base_dimension {};

    /* Compound dimensions */
    // ...
}
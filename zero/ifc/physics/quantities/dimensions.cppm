/**
 * @brief Physical dimensions
 *
 * A physical dimension is a characteristic of a physical quantity that can be expressed as a combination
 * of fundamental dimensions. Fundamental dimensions are independent dimensions that cannot be expressed
 * in terms of other dimensions.
 * Physical dimensions can be used to classify physical quantities and compare them based on their fundamental nature.
*/

export module physics:dimensions;

import std;
import :ratios;
import :units.symbols;

export namespace zero::physics {
    /* Base dimensions */
    class base_dimension {
    };

    class mass : public base_dimension {
    };

    class length : public base_dimension {
    };

    template<typename T>
    concept BaseDimension = std::is_base_of_v<base_dimension, T>;

    /* Compound dimensions */
    template<BaseDimension... Ts>
    class derived_dimension {};



    template<typename T, typename... Bs>
    concept DerivedDimension = requires {
        requires (BaseDimension<Bs>, ...);
        //requires (std::is_base_of_v<derived_dimension<Bs>, T> && ...); // expands the pack of base dimensions
    };
}

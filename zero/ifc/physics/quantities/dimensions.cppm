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
    class base_dimension {};

    class mass: public base_dimension {};
    class length: public base_dimension {};

    template <typename T>
    concept BaseDimension =
        std::is_base_of_v<base_dimension, T>;
    
    /* Compound dimensions */
    template <typename T>
    class derived_dimension {};

    class speed: public derived_dimension<mass> {};

    // template <template <typename> class T>
    template <typename T, typename B>
    concept DerivedDimension = requires {
        requires BaseDimension<B>;
        requires std::is_base_of_v<derived_dimension<B>, T>;
    };

}

static_assert(zero::physics::DerivedDimension<zero::physics::speed, zero::physics::mass>);
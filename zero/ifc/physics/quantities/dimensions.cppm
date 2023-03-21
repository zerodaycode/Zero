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

    /**
     * CRTP base "tag" for declaring a base dimension. By being a CRTP base class, we can
     * declare the `dimension` alias inside this type, so we can access it from the tags
     * of their implementors like T::base_dimension::dimension, which always will be the
     * dimension of the template parameter itself, and avoid pollute the public API with
     * using declarations when they can be automatically set up from the base tag
     */
    template <typename Dimension>
    struct base_dimension {
        using dimension = Dimension;
    };

    struct mass : public base_dimension<mass> {};
    struct length : public base_dimension<length> {};
    struct time : public base_dimension<time> {};

    template<typename T>
    concept BaseDimension = std::is_base_of_v<base_dimension<T>, T>;

    /* Compound dimensions */
    template<BaseDimension... Dimensions>
    struct derived_dimension {
        using dimensions = std::tuple<Dimensions...>;
    };

    template<typename T, typename... Bs>
    concept DerivedDimension = requires {
        requires (BaseDimension<Bs>, ...);
        requires (std::is_base_of_v<derived_dimension<Bs...>, T>);
    };

    struct speed : public derived_dimension<time, length> {};
}

static_assert(zero::physics::BaseDimension<zero::physics::mass>);
static_assert(zero::physics::BaseDimension<zero::physics::length>);
static_assert(
    zero::physics::DerivedDimension<
        zero::physics::speed,
        zero::physics::time,
        zero::physics::length
    >
);

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
    struct base_dimension {};

    struct mass : public base_dimension {};
    struct length : public base_dimension {};
    struct time : public base_dimension {};

    template<typename T>
    concept BaseDimension = std::is_base_of_v<base_dimension, T>;

    /* Compound dimensions */
    template<BaseDimension... Ts>
    struct derived_dimension {};

    template<typename T, typename... Bs>
    concept DerivedDimension = requires {
        requires (BaseDimension<Bs>, ...);
        requires (std::is_base_of_v<derived_dimension<Bs...>, T>);
    };

    struct speed : public derived_dimension<time, length> {
        using dimensions = std::tuple<time, length>;
    };
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

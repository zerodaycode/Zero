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
    template <typename Dimension, short DimensionExponent = 1>
    struct base_dimension {
        using dimension = Dimension;
        static constexpr short dimension_exp = DimensionExponent;
    };

    template <short DimensionExponent = 1>
    struct mass : public base_dimension<mass<DimensionExponent>, DimensionExponent> {};

    template <short DimensionExponent = 1>
    struct length : public base_dimension<length<DimensionExponent>, DimensionExponent> {};

    template <short DimensionExponent = 1>
    struct time : public base_dimension<time<DimensionExponent>, DimensionExponent> {};

    template<typename T>
    concept BaseDimension = std::is_base_of_v<base_dimension<T, T::dimension_exp>, T> &&
        requires { typename T::dimension; };

    /* Compound dimensions */
    template<typename Derived, typename... Dimensions>
    struct derived_dimension {
        using self = Derived;
        using dimensions = std::tuple<Dimensions...>;
    };

    template <typename T, std::size_t... Is>
    constexpr bool is_derived_dimension_impl() {
        return (std::is_base_of_v<derived_dimension<T, std::tuple_element_t<Is, typename T::dimensions>> && ...>);
    }

    template<typename T>
    concept DerivedDimension = requires {
        is_derived_dimension_impl<T>();
        typename T::self;
    };

    struct speed : public derived_dimension<speed, length<>, time< -1 >> {};
}

static_assert(zero::physics::BaseDimension<zero::physics::mass<1>>);
static_assert(zero::physics::BaseDimension<zero::physics::length<1>>);
static_assert(zero::physics::DerivedDimension<zero::physics::speed>);

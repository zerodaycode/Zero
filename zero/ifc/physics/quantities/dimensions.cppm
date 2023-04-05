/**
 * @brief Physical dimensions
 *
 * A physical dimension is a characteristic of a physical quantity that can be expressed as a combination
 * of fundamental dimensions. Fundamental dimensions are independent dimensions that cannot be expressed
 * in terms of other dimensions.
 * Physical dimensions can be used to classify physical quantities and compare them based on their fundamental nature.
*/

export module physics.quantities:dimensions;

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

    template<typename T>
    concept BaseDimension = std::is_base_of_v<base_dimension<T, T::dimension_exp>, T> &&
        requires { typename T::dimension; T::dimension_exp; };

    /* Compound dimensions */
    template<typename... Dimensions>
    struct derived_dimension {
        using dimensions = std::tuple<Dimensions...>;
        static constexpr auto total_dimensions = std::tuple_size<dimensions>::value;
    };

    template<typename T, std::size_t... Is>
    concept DerivedDimension = requires {
        typename T::dimensions;
        T::total_dimensions;
    } && (std::is_base_of_v<derived_dimension<T, std::tuple_element_t<Is, typename T::dimensions>>, T> && ...);
}

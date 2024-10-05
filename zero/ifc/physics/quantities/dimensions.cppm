/**
 * @brief Physical dimensions
 *
 * A physical dimension is a characteristic of a physical quantity that can be expressed as a
 * combination of fundamental dimensions. Fundamental dimensions are independent dimensions that
 * cannot be expressed in terms of other dimensions.
 *
 * Physical dimensions can be used to classify physical quantities and compare them based on their
 * fundamental nature.
*/

export module physics.quantities:dimensions;

import std;
import :ratios;
import :units.symbols;

export namespace zero::physics {
/**
 * @brief CRTP base "tag" for declaring a base dimension. By being a CRTP base class, we can
 * declare the `dimension` alias inside this type, so we can access it from the tags of their
 * implementors like T::base_dimension::dimension, which always will be the dimension of the
 * template parameter itself, and avoid pollute the public API with using declarations when they can
 * be automatically set up from the base tag.
 *
 * @tparam Dimension The fundamental dimension associated with this unit.
 * @tparam DimensionExponent The exponent of the dimension (default is 1).
 */
template<typename Dimension, short DimensionExponent = 1>
struct base_dimension {
    /**
     * @brief The fundamental dimension associated with this unit.
     */
    using dimension = Dimension;
    
    /**
     * @brief The exponent of the dimension.
     */
    static constexpr short dimension_exp = DimensionExponent;
};

/**
 * @brief Concept that checks if a type is a base dimension tag.
 *
 * A base dimension tag is a type that inherits from `base_dimension` and has the required
 * `dimension` alias.
 *
 * @tparam T The type to check.
 */
template<typename T>
concept BaseDimension = std::is_base_of_v<base_dimension<T, T::dimension_exp>, T> && requires {
    /**
     * @brief The fundamental dimension associated with this unit.
     */
    typename T::dimension;
    
    /**
     * @brief The exponent of the dimension.
     */
    T::dimension_exp;
};

/**
 * @brief CRTP base "tag" for declaring a derived dimension. By being a CRTP base class, we can
 * declare the `dimensions` alias inside this type, so we can access it from the tags of their
 * implementors like T::derived_dimension::dimensions, which always will be the dimensions of the
 * template parameter itself, and avoid pollute the public API with using declarations when they can
 * be automatically set up from the base tag.
 *
 * @tparam Dimensions The fundamental dimensions associated with this unit.
 */
template<typename... Dimensions>
struct derived_dimension {
    /**
     * @brief The tuple of fundamental dimensions associated with this unit.
     */
    using dimensions = std::tuple<Dimensions...>;
};

/**
 * @brief Concept that checks if a type is a derived dimension tag.
 *
 * A derived dimension tag is a type that inherits from `derived_dimension` and has the required
 * `dimensions` alias.
 *
 * @tparam T The type to check.
 */
template<typename T, std::size_t... Is>
concept DerivedDimension =
    requires {
        /**
         * @brief The tuple of fundamental dimensions associated with this unit.
         */
        typename T::dimensions;
        
        /**
         * @brief The total number of fundamental dimensions in the unit.
         */
        T::total_dimensions;
    }
    && (std::is_base_of_v<derived_dimension<T, std::tuple_element_t<Is, typename T::dimensions>>, T>
        && ...);
} // namespace zero::physics

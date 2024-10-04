/**
 * @brief Predefined physical units based on the definitions provided by the international system
 *
 * This module provides a set of predefined physical units that can be used to represent various
 * quantities. Each unit is associated with a specific dimension, such as mass (e.g., kg), length
 * (e.g., m), or time (e.g., s).
 */

export module physics.quantities:units;

import std;
import math;

import concepts;
import :ratios;
import :dimensions;
import :units.symbols;
import :quantities.detail;

using namespace quantities::__detail;
using namespace zero::math;

/**
 * @brief Base unit concept
 *
 * A base unit is a fundamental unit that cannot be expressed in terms of other units.
 * Each base unit has a unique ratio and symbol associated with it.
 */
template<Ratio r, Symbol s>
struct base_unit {
    /**
     * @brief Ratio of the base unit
     *
     * The ratio represents the power to which the base unit is raised when expressing a quantity in
     * terms of this unit.
     */
    using ratio = r;

    /**
     * @brief Symbol of the base unit
     *
     * The symbol is a unique identifier for the base unit and is used to represent it in
     * expressions.
     */
    using symbol = s;
};

/**
 * @brief Concept for checking if a type is a base unit
 *
 * A type is considered a base unit if it satisfies this concept, which means it has a ratio and
 * symbol associated with it.
 */
template<typename T>
concept BaseUnit = Ratio<typename T::ratio> && // Type must have a ratio associated with it
    Symbol<typename T::symbol>; // Type must have a symbol associated with it

/**
 * @brief Derived unit concept
 *
 * A derived unit is a unit that can be expressed in terms of base units.
 * Each derived unit has a unique set of base units and a dimensionality associated with it.
 */
template<typename DerivedDim, BaseUnit... BaseUnits>
    requires(DerivedDimension<DerivedDim>) // Type must have a derived dimension associated with it
struct derived_unit {
    /**
     * @brief Derived dimension of the derived unit
     *
     * The derived dimension represents the set of base dimensions that are used to derive this
     * unit.
     */
    using derived_dimension = DerivedDim;

    /**
     * @brief Set of base units used to derive the unit
     *
     * Each base unit in the set is associated with a specific power, which is used to calculate the
     * dimensionality of the derived unit.
     */
    using units = std::tuple<BaseUnits...>;

    /**
     * @brief Dimensionality of the derived unit
     *
     * The dimensionality represents the product of the powers of the base units used to derive this
     * unit.
     */
    static constexpr double dimensionality = []<std::size_t... Is>(std::index_sequence<Is...>) {
        using dm_exp = dimensions_exponents<typename DerivedDim::dimensions>;
        return (1.0 * ... * power_of(BaseUnits::ratio::value, dm_exp::value[Is]));
    }(std::make_index_sequence<DerivedDim::total_dimensions> {});
};

/**
 * @brief Concept for checking if a type is a derived unit
 *
 * A type is considered a derived unit if it satisfies this concept, which means it has a derived
 * dimension and a set of base units associated with it.
 */
template<typename T, std::size_t... Is>
concept DerivedUnit =
    requires {
        typename T::units; // Type must have a set of base units associated with it
        typename T::derived_dimension; // Type must have a derived dimension associated with it
        T::dimensionality; // Type must have a dimensionality associated with it
    }
    && (std::is_base_of_v<
            derived_unit<
                typename T::derived_dimension,
                std::tuple_element_t<Is, typename T::units>>,
            T>
        && ...);

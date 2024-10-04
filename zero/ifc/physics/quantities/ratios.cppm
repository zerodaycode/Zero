/**
 * @brief Definitions for representing the different order or magnitudes in a physical quantity.
 *
 * This module provides a way to represent powers that can be used as ratios in the context of units
 * of measure, where the power describes how a certain quantity is measured relative to a reference
 * unit.
 */

export module physics.quantities:ratios;

import math;
import std;
import concepts;
import :units.symbols;
import :quantities.detail;

/**
 * @brief Represents a power that can be used as a ratio.
 *
 * This struct template represents a mathematical power, where the base is an integral number,
 * and the exponent is an integer. It's designed to be used as a ratio in the context of units
 * of measure, where the power describes how a certain quantity is measured relative to a
 * reference unit.
 *
 * @tparam Base The integral base of the power.
 * @tparam Exponent The integer exponent of the power.
 * @tparam BaseDenominator The denominator of the base, which can be used to represent fractional
 * powers. By default, this is set to 1, indicating an integer base.
 */
template<typename T = double>
concept RatioV = (std::is_integral_v<T> || std::is_floating_point_v<T>) && !std::is_same_v<T, char>;

/**
 * @brief Represents a power that will serve as a ratio for comparing quantities with the same
 * dimension.
 *
 * This struct represents a power that can be used to compare quantities of the same type
 * but with different order or magnitudes. It's designed to be used in conjunction with the
 * `base_unit` and `derived_unit` classes to represent units of measurement.
 *
 * @tparam Base The base value of the power (default: 10).
 * @tparam Exponent The exponent of the power (default: 0).
 * @tparam BaseDenominator The denominator of the base (default: 1).
 */
template<int Base = 10, int Exponent = 0, int BaseDenominator = 1>
struct ratio {
    /**
     * @brief Gets the base value of the power.
     *
     * @return The base value of the power.
     */
    static constexpr double base() {
        return static_cast<double>(Base);
    }

    /**
     * @brief Gets the exponent of the power.
     *
     * @return The exponent of the power.
     */
    static constexpr double exponent() {
        return static_cast<double>(Exponent);
    }

    /**
     * @brief Gets the denominator of the base.
     *
     * @return The denominator of the base.
     */
    static constexpr double baseDenominator() {
        return static_cast<double>(BaseDenominator);
    }

    /**
     * @brief Calculates the value of the power.
     *
     * This function calculates the value of the power using the formula:
     * `base^exponent / base_denominator`. It's designed to be used in conjunction with
     * the `power_of` function from the `math` module.
     *
     * @return The calculated value of the power.
     */
    static constexpr double value() {
        return zero::math::power_of(base(), exponent()) / baseDenominator();
    }

    using Value = decltype(value());
};

/**
 * @brief Represents a unit prefix (e.g., kilo, meter).
 *
 * This struct represents a unit prefix that can be used to indicate the order or magnitude
 * of a quantity.
 */
struct unit_prefix {
    static constexpr std::string_view name() {
        return "unit_prefix";
    }
};

export namespace zero::physics {
/**
 * @brief Represents the yocto prefix (e.g., 10^-24).
 *
 * This struct represents the yocto prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^-24.
 */
using yocto = ratio<1, -24>;

/**
 * @brief Represents the zepto prefix (e.g., 10^-21).
 *
 * This struct represents the zepto prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^-21.
 */
using zepto = ratio<1, -21>;

/**
 * @brief Represents the atto prefix (e.g., 10^-18).
 *
 * This struct represents the atto prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^-18.
 */
using atto = ratio<1, -18>;

/**
 * @brief Represents the femto prefix (e.g., 10^-15).
 *
 * This struct represents the femto prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^-15.
 */
using femto = ratio<1, -15>;

/**
 * @brief Represents the pico prefix (e.g., 10^-12).
 *
 * This struct represents the pico prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^-12.
 */
using pico = ratio<1, -12>;

/**
 * @brief Represents the nano prefix (e.g., 10^-9).
 *
 * This struct represents the nano prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^-9.
 */
using nano = ratio<1, -9>;

/**
 * @brief Represents the micro prefix (e.g., 10^-6).
 *
 * This struct represents the micro prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^-6.
 */
using micro = ratio<1, -6>;

/**
 * @brief Represents the milli prefix (e.g., 10^-3).
 *
 * This struct represents the milli prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^-3.
 */
using milli = ratio<1, -3>;

/**
 * @brief Represents the centi prefix (e.g., 10^-2).
 *
 * This struct represents the centi prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^-2.
 */
using centi = ratio<1, -2>;

/**
 * @brief Represents the deci prefix (e.g., 10^-1).
 *
 * This struct represents the deci prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^-1.
 */
using deci = ratio<1, -1>;

/**
 * @brief Represents the root prefix (e.g., 10^0).
 *
 * This struct represents the root prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^0.
 */
using root = ratio<1, 0>;

/**
 * @brief Represents the deca prefix (e.g., 10^1).
 *
 * This struct represents the deca prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^1.
 */
using deca = ratio<1, 1>;

/**
 * @brief Represents the hecto prefix (e.g., 10^2).
 *
 * This struct represents the hecto prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^2.
 */
using hecto = ratio<1, 2>;

/**
 * @brief Represents the kilo prefix (e.g., 10^3).
 *
 * This struct represents the kilo prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^3.
 */
using kilo = ratio<1, 3>;

/**
 * @brief Represents the mega prefix (e.g., 10^6).
 *
 * This struct represents the mega prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^6.
 */
using mega = ratio<1, 6>;

/**
 * @brief Represents the giga prefix (e.g., 10^9).
 *
 * This struct represents the giga prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^9.
 */
using giga = ratio<1, 9>;

/**
 * @brief Represents the tera prefix (e.g., 10^12).
 *
 * This struct represents the tera prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^12.
 */
using tera = ratio<1, 12>;

/**
 * @brief Represents the peta prefix (e.g., 10^15).
 *
 * This struct represents the peta prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^15.
 */
using peta = ratio<1, 15>;

/**
 * @brief Represents the exa prefix (e.g., 10^18).
 *
 * This struct represents the exa prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^18.
 */
using exa = ratio<1, 18>;

/**
 * @brief Represents the zetta prefix (e.g., 10^21).
 *
 * This struct represents the zetta prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^21.
 */
using zetta = ratio<1, 21>;

/**
 * @brief Represents the yotta prefix (e.g., 10^24).
 *
 * This struct represents the yotta prefix, which is a unit prefix that indicates an order
 * of magnitude of 10^24.
 */
using yotta = ratio<1, 24>;

/**
 * @brief Represents the second prefix (e.g., 60).
 *
 * This struct represents the second prefix, which is a unit prefix that indicates an order
 * of magnitude related to seconds.
 */
using second = ratio<60, 0>;

/**
 * @brief Represents the minute prefix (e.g., 1/60).
 *
 * This struct represents the minute prefix, which is a unit prefix that indicates an order
 * of magnitude related to minutes.
 */
using minute = ratio<60, 1>;

/**
 * @brief Represents the hour prefix (e.g., 1/3600).
 *
 * This struct represents the hour prefix, which is a unit prefix that indicates an order
 * of magnitude related to hours.
 */
using hour = ratio<60, 2>;

/**
 * @brief Represents the day prefix (e.g., 24).
 *
 * This struct represents the day prefix, which is a unit prefix that indicates an order
 * of magnitude related to days.
 */
using day = ratio<24, 1>;
} // namespace zero::physics

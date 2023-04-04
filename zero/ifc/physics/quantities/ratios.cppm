/**
 * @brief Definitions for representing the different
 * order or magnitudes in a physical quantity
 */

export module physics.quantities:ratios;

import std;

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
template <typename T>
concept RatioV = (std::is_integral_v<T> || std::is_floating_point_v<T>)
    && !std::is_same_v<T, char>;

[[nodiscard]]
constexpr double power_of(const double base, const int exponent) {
    double result = 1;
    const int limit = ((exponent >= 0) ? exponent : exponent * -1);
    for (int i = 0; i < limit; i++)
        result *= (exponent >= 0) ? base : 1/base;
    return result;
}

[[nodiscard]]
inline consteval double consteval_power_of(const double base, const int exponent) {
    return power_of(base, exponent);
}


/**
 * Represents a power that will serve as a ratio for compare quantities
 * with the same dimension
 * @tparam Base
 * @tparam Exponent
 * @tparam BaseDenominator
 */
template <int Base = 10, int Exponent = 0, int BaseDenominator = 1>
struct ratio {
    static constexpr double base = static_cast<double>(Base);
    static constexpr double exponent = static_cast<double>(Exponent);
    static constexpr double base_denominator = static_cast<double>(BaseDenominator);
    static constexpr double value = consteval_power_of(base / base_denominator, exponent);
};

export namespace zero::physics {
    using unit_r = ratio<1, 1>;

    using yocto = ratio<10, -24>;
    using zepto = ratio<10, -21>;
    using atto = ratio<10, -18>;
    using femto = ratio<10, -15>;
    using pico = ratio<10, -12>;
    using nano = ratio<10, -9>;
    using micro = ratio<10, -6>;
    using milli = ratio<10, -3>;
    using centi = ratio<10, -2>;
    using deci = ratio<10, -1>;
    using root = ratio<10, 0>;
    using deca = ratio<10, 1>;
    using hecto = ratio<10, 2>;
    using kilo = ratio<10, 3>;
    using mega = ratio<10, 6>;
    using giga = ratio<10, 9>;
    using tera = ratio<10, 12>;
    using peta = ratio<10, 15>;
    using exa = ratio<10, 18>;
    using zetta = ratio<10, 21>;
    using yotta = ratio<10, 24>;

    using second = ratio<60, 0>;
    using minute = ratio<60, 1>;
    using hour = ratio<60, 2>;
    using day = ratio<24, 1>;

    template <typename T>
    concept Ratio = requires {
        T::base;
        T::exponent;
        T::value;
    };
}

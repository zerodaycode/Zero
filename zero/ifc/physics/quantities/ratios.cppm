/**
 * @brief Definitions for representing the different
 * order or magnitudes in a physical quantity
 */

export module physics.quantities:ratios;
import std;

/**
 * @brief Defines a Ratio in terms of the power of the numerical values
 * of the given Base and the given Exponent
 */
template <typename T>
concept RatioV = (std::is_integral_v<T> || std::is_floating_point_v<T>)
    && !std::is_same_v<T, char>;

consteval double consteval_power(double base, int exponent);
constexpr double power(double base, int exponent);

template <RatioV T = short, T Base = 10, T Exponent = 0>  // TODO template guide deduction, reorder members
struct ratio {
    static constexpr T base = Base;
    static constexpr T exponent = Exponent;
    static constexpr double value = consteval_power(base, exponent);
};

[[nodiscard]]
inline consteval double consteval_power(const double base, const int exponent) {
    return power(base, exponent);
}

[[nodiscard]]
constexpr double power(const double base, const int exponent) {
    double result = 1;
    const int limit = ((exponent >= 0) ? exponent : exponent * -1);
    for (int i = 0; i < limit; i++)
        result *= (exponent >= 0) ? base : 1/base;
    return result;
}

export namespace zero::physics {
    using yocto = ratio<short, 10, -24>;
    using zepto = ratio<short, 10, -21>;
    using atto = ratio<short, 10, -18>;
    using femto = ratio<short, 10, -15>;
    using pico = ratio<short, 10, -12>;
    using nano = ratio<short, 10, -9>;
    using micro = ratio<short, 10, -6>;
    using milli = ratio<short, 10, -3>;
    using centi = ratio<short, 10, -2>;
    using deci = ratio<short, 10, -1>;
    using root = ratio<short, 10, 0>;
    using deca = ratio<short, 10, 1>;
    using hecto = ratio<short, 10, 2>;
    using kilo = ratio<short, 10, 3>;
    using mega = ratio<short, 10, 6>;
    using giga = ratio<short, 10, 9>;
    using tera = ratio<short, 10, 12>;
    using peta = ratio<short, 10, 15>;
    using exa = ratio<short, 10, 18>;
    using zetta = ratio<short, 10, 21>;
    using yotta = ratio<short, 10, 24>;

    using second = ratio<short, 60, 0>;
    using hour = ratio<short, 60, 2>;

    template <typename T>
    concept Ratio = 
        std::is_same_v<T, yocto> ||
        std::is_same_v<T, zepto> ||
        std::is_same_v<T, atto> ||
        std::is_same_v<T, femto> ||
        std::is_same_v<T, pico> ||
        std::is_same_v<T, nano> ||
        std::is_same_v<T, micro> ||
        std::is_same_v<T, milli> ||
        std::is_same_v<T, centi> ||
        std::is_same_v<T, root> ||
        std::is_same_v<T, deci> ||
        std::is_same_v<T, deca> ||
        std::is_same_v<T, hecto> ||
        std::is_same_v<T, kilo> ||
        std::is_same_v<T, mega> ||
        std::is_same_v<T, giga> ||
        std::is_same_v<T, tera> ||
        std::is_same_v<T, peta> ||
        std::is_same_v<T, exa> ||
        std::is_same_v<T, zetta> ||
        std::is_same_v<T, second> ||
        std::is_same_v<T, hour>;
}

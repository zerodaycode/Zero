/**
 * @brief Definiton and types for representing the different
 * order or magnitudes in a physical quantity
 */

export module physics:ratios;
import std;

export namespace zero::physics {
    /**
     * @brief Defines a Ratio in terms of numerical values
     */
    template <typename T>
    concept RatioV = std::is_integral_v<T> || std::is_floating_point_v<T>;

    template <RatioV T = short, T Base = 10, T Exponent = 0>
    struct ratio {
        static constexpr T base = Base;
        static constexpr T exponent = Exponent;
        static constexpr T value = Base * Exponent;
        static constexpr double factor = std::pow(Base, Exponent);
    };

    using Yocto = ratio<short, 10, -24>;
    using Zepto = ratio<short, 10, -21>;
    using Atto = ratio<short, 10, -18>;
    using Femto = ratio<short, 10, -15>;
    using Pico = ratio<short, 10, -12>;
    using Nano = ratio<short, 10, -9>;
    using Micro = ratio<short, 10, -6>;
    using Milli = ratio<short, 10, -3>;
    using Centi = ratio<short, 10, -2>;
    using Deci = ratio<short, 10, -1>;
    using Root = ratio<short, 10, 0>;
    using Deca = ratio<short, 10, 1>;
    using Hecto = ratio<short, 10, 2>;
    using Kilo = ratio<short, 10, 3>;
    using Mega = ratio<short, 10, 6>;
    using Giga = ratio<short, 10, 9>;
    using Tera = ratio<short, 10, 12>;
    using Peta = ratio<short, 10, 15>;
    using Exa = ratio<short, 10, 18>;
    using Zetta = ratio<short, 10, 21>;
    using Yotta = ratio<short, 10, 24>;

    template <typename T>
    concept Ratio = 
        std::is_same_v<T, Yocto> ||
        std::is_same_v<T, Zepto> ||
        std::is_same_v<T, Atto> ||
        std::is_same_v<T, Femto> ||
        std::is_same_v<T, Pico> ||
        std::is_same_v<T, Nano> ||
        std::is_same_v<T, Micro> ||
        std::is_same_v<T, Milli> ||
        std::is_same_v<T, Centi> ||
        std::is_same_v<T, Root> ||
        std::is_same_v<T, Deci> ||
        std::is_same_v<T, Deca> ||
        std::is_same_v<T, Hecto> ||
        std::is_same_v<T, Kilo> ||
        std::is_same_v<T, Mega> ||
        std::is_same_v<T, Giga> ||
        std::is_same_v<T, Tera> ||
        std::is_same_v<T, Peta> ||
        std::is_same_v<T, Exa> ||
        std::is_same_v<T, Zetta> ||
        std::is_same_v<T, Yotta>;
}

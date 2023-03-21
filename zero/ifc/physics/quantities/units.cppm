/**
* @brief Predefined physical units based on the definitions
 * provided by the international system
*/

export module physics:units;

import std;

import :ratios;
import :dimensions;
import :units.symbols;

export namespace zero::physics {
    /* Base units */
    template<BaseDimension Dimension, Ratio R, Symbol S>
    struct base_unit: public Dimension {
        using dimension = Dimension;
        using ratio = R;
        using symbol = S;
    };

    template <typename T>
    concept BaseUnit =
        BaseDimension <typename T::dimension> &&
        Ratio <typename T::ratio> &&
        Symbol <typename T::symbol> &&
    requires {
        typename T::dimension;
        typename T::ratio;
        typename T::symbol;
    };

    struct Kilogram : public base_unit<mass, Kilo, kg> {};
    struct Hectogram :public base_unit<mass, Hecto, hg> {};
    struct Meter : public base_unit<length, Root, m> {};


    /* Derived units */
    template <BaseUnit... BaseUnits>
    struct derived_unit {
        using units = std::tuple<BaseUnits...>;
    };

    struct MetersPerSecond :
        public speed,
        public derived_unit<
            base_unit<length, Root, m>,
            base_unit<time, Root, s>
        >
    {};
}

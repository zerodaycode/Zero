/**
* @brief Predefined physical units based on the definitions
 * provided by the international system
*/

export module physics.quantities:units;

import std;

import concepts;
import :ratios;
import :dimensions;
import :units.symbols;
import :units.detail;

using namespace units::__detail;

export namespace zero::physics {
    /* Base units */
    template<Ratio r, Symbol s>
    struct base_unit {
        using ratio = r;
        using symbol = s;
    };

    template <typename T>
    concept BaseUnit =
        Ratio<typename T::ratio> &&
        Symbol<typename T::symbol> &&
    requires {
        typename T::ratio;
        typename T::symbol;
    };

    /* Derived units */
    template <typename DerivedDim, BaseUnit... BaseUnits>
        requires (DerivedDimension<DerivedDim>)
    struct derived_unit {
        using derived_dimension = DerivedDim;
        using units = std::tuple<BaseUnits...>;

        static constexpr double dimensionality = []<std::size_t... Is>(std::index_sequence<Is...>) {
            using dm_exp = dimensions_exponents<typename DerivedDim::dimensions>;
            return (1.0 * ... * consteval_power(BaseUnits::ratio::value, dm_exp::value[Is]));
        } (std::make_index_sequence<DerivedDim::total_dimensions>{});
    };

    template <typename T, std::size_t... Is>
    concept DerivedUnit = requires {
        typename T::units;
        typename T::derived_dimension;
        T::dimensionality;
    } && (std::is_base_of_v<derived_unit<typename T::derived_dimension, std::tuple_element_t<Is, typename T::units>>, T> && ...);
}

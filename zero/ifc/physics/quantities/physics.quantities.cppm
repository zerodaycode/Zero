/*
 * Primary module interface for the `quantities library`
 */

export module physics.quantities;

export import :quantity;
export import :dimensions;
export import :units;
export import :units.symbols;
export import :ratios;

export namespace zero::physics {
    /* -------------- Dimensions -------------- */

    template <short DimensionExponent = 1>
    struct mass : public base_dimension<mass<DimensionExponent>, DimensionExponent> {};

    template <short DimensionExponent = 1>
    struct length : public base_dimension<length<DimensionExponent>, DimensionExponent> {};

    template <short DimensionExponent = 1>
    struct time : public base_dimension<time<DimensionExponent>, DimensionExponent> {};

    struct speed : public derived_dimension<speed, length<>, time< -1 >> {};


    /* -------------- Units -------------- */

    struct Kilogram: public mass<1>, public base_unit<kilo, kg> {};
    struct Hectogram: public mass<1>, public base_unit<hecto, hg> {};
    struct Meter: public length<1>, public base_unit<root, m> {};
    struct Second: public time<1>, public base_unit<second, s> {};
    struct Hour: public time<1>, public base_unit<hour, h> {};

    struct MetersPerSecond :
        public derived_unit<
            speed,
            base_unit<root, m>,
            base_unit<second, s>
        > {};

    struct KilometersPerHour :
        public derived_unit<
            speed,
            base_unit<kilo, km>,
            base_unit<hour, h>
        > {};
}


/* Testing our base/derived dimensions */
static_assert(zero::physics::BaseDimension<zero::physics::mass<>>);
static_assert(zero::physics::BaseDimension<zero::physics::length<>>);
static_assert(zero::physics::DerivedDimension<zero::physics::speed>);

/* Testing our symbols */
static_assert(zero::physics::Symbol<zero::physics::kg>);

/* Testing our base units */
static_assert(zero::physics::BaseUnit<zero::physics::Kilogram>);
static_assert(zero::physics::BaseUnit<zero::physics::Hectogram>);
static_assert(zero::physics::BaseUnit<zero::physics::Meter>);
static_assert(zero::physics::BaseUnit<zero::physics::Second>);
static_assert(zero::physics::BaseUnit<zero::physics::Hour>);

/* Testing our derived units */
static_assert(zero::physics::DerivedUnit<zero::physics::MetersPerSecond>);
static_assert(zero::physics::DerivedUnit<zero::physics::KilometersPerHour>);
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
    /* ----------------------------------- Dimensions ----------------------------------- */

    /* ---------- Base Dimensions ---------- */
    template <short DimensionExponent = 1>
    struct mass : public base_dimension<mass<DimensionExponent>, DimensionExponent> {};

    template <short DimensionExponent = 1>
    struct length : public base_dimension<length<DimensionExponent>, DimensionExponent> {};

    template <short DimensionExponent = 1>
    struct time : public base_dimension<time<DimensionExponent>, DimensionExponent> {};

    template <short DimensionExponent = 1>
    struct temperature : public base_dimension<temperature<DimensionExponent>, DimensionExponent> {};

    template <short DimensionExponent = 1>
    struct electric_current : public base_dimension<electric_current<DimensionExponent>, DimensionExponent> {};

    template <short DimensionExponent = 1>
    struct amount_of_substance : public base_dimension<amount_of_substance<DimensionExponent>, DimensionExponent> {};

    template <short DimensionExponent = 1>
    struct luminous_intensity : public base_dimension<luminous_intensity<DimensionExponent>, DimensionExponent> {};

    template <short DimensionExponent = 1>
    struct dimensionless : public base_dimension<dimensionless<DimensionExponent>, DimensionExponent> {};

    /* ---------- Derived Dimensions ---------- */
    struct speed : public derived_dimension<length<>, time< -1 >> {};
    struct frequency : public derived_dimension<dimensionless<>, time< -1 >> {};
    struct force : public derived_dimension<mass<>, length<>, time< -2 >> {};
    struct energy : public derived_dimension<mass<>, length<2>, time< -2 >> {};
    struct power : public derived_dimension<mass<>, length<2>, time< -3 >> {};
    struct electric_charge : public derived_dimension<electric_current<>, time<>> {};
    struct voltage : public derived_dimension<mass<>, length<2>, time< -3 >, electric_current< -1 >> {};


    /* ----------------------------------- Units ----------------------------------- */

    /* ---------- Base Units ---------- */

    /* Base Units for Mass dimension */
    struct Kilogram: public mass<>, public base_unit<kilo, kg> {};
    struct Hectogram: public mass<>, public base_unit<hecto, hg> {};

    /* Base Units for Length dimension */
    struct Meter: public length<>, public base_unit<root, m> {};

    /* Base Units for Time dimension */
    struct Second: public time<>, public base_unit<second, s> {};
    struct Minute: public time<>, public base_unit<minute, m> {};
    struct Hour: public time<>, public base_unit<hour, h> {};
    struct Day: public time<>, public base_unit<day, d> {};

    /* Base Units for the Electric Current dimension */
    struct Ampere: public electric_current<>, public base_unit<root, A> {};


    /* ---------- Derived Units ---------- */

    /* Derived Units for the Speed dimension */
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

    /* Derived Units for the Frequency dimension */
    struct Hertz :
        public derived_unit<
            frequency,
            base_unit<unit_r, unit_type>,
            base_unit<second, s>
        > {};

    /* Derived Units for the Force dimension */
    struct Newton :
        public derived_unit<
            force,
            base_unit<kilo, kg>,
            base_unit<root, m>,
            base_unit<second, s>
    > {};


    /* Derived Units for the Energy dimension */
    struct Joule :
        public derived_unit<
            energy,
            base_unit<kilo, kg>,
            base_unit<root, m>,
            base_unit<second, s>
        > {};

    /* Derived Units for the Power dimension */
    struct Watt :
        public derived_unit<
            power,
            base_unit<kilo, kg>,
            base_unit<root, m>,
            base_unit<second, s>
        > {};

    /* Derived Units for the Electric Charge dimension */
    struct Coulomb :
        public derived_unit<
            electric_charge,
            base_unit<root, A>,
            base_unit<second, s>
        > {};

    /* Derived Units for the Voltage dimension */
    struct Volt :
        public derived_unit<
            voltage,
            base_unit<kilo, kg>,
            base_unit<root, m>,
            base_unit<second, s>,
            base_unit<root, A>
        > {};
}


/* Testing our base dimensions */
static_assert(zero::physics::BaseDimension<zero::physics::mass<>>);
static_assert(zero::physics::BaseDimension<zero::physics::length<>>);
static_assert(zero::physics::BaseDimension<zero::physics::time<>>);
static_assert(zero::physics::BaseDimension<zero::physics::temperature<>>);
static_assert(zero::physics::BaseDimension<zero::physics::electric_current<>>);
static_assert(zero::physics::BaseDimension<zero::physics::amount_of_substance<>>);
static_assert(zero::physics::BaseDimension<zero::physics::luminous_intensity<>>);
static_assert(zero::physics::BaseDimension<zero::physics::dimensionless<>>);

/* Testing our derived dimensions */
static_assert(zero::physics::DerivedDimension<zero::physics::speed>);
static_assert(zero::physics::DerivedDimension<zero::physics::frequency>);
static_assert(zero::physics::DerivedDimension<zero::physics::force>);
static_assert(zero::physics::DerivedDimension<zero::physics::energy>);
static_assert(zero::physics::DerivedDimension<zero::physics::power>);
static_assert(zero::physics::DerivedDimension<zero::physics::electric_charge>);
static_assert(zero::physics::DerivedDimension<zero::physics::voltage>);

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
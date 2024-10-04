/**
 * @brief Primary module interface for the `quantities library`
 *
 * This module provides a comprehensive framework for working with physical quantities,
 * including their dimensions, units, and relationships.
 */

export module physics.quantities;

export import :quantity;
export import :dimensions;
export import :units;
export import :units.symbols;
export import :ratios;

export namespace zero::physics {

/**
 * @brief Base dimensions
 *
 * These base dimensions are the fundamental building blocks for deriving compound
 * dimensions and units. They represent the basic characteristics of physical quantities,
 * such as mass, length, time, temperature, electric current, amount of substance, and luminous
 * intensity.
 */

/* ---------- Base Dimensions ---------- */
/**
 * @brief Mass dimension
 *
 * The mass dimension represents the quantity of matter in a physical system.
 * It is derived from the fundamental dimension of mass.
 *
 * @tparam DimensionExponent The exponent to which the fundamental dimension of mass is raised
 * (default: 1).
 */
template<short DimensionExponent = 1>
struct mass: public base_dimension<mass<DimensionExponent>, DimensionExponent> {};

/**
 * @brief Length dimension
 *
 * The length dimension represents the size or extent of a physical system.
 * It is derived from the fundamental dimension of length.
 *
 * @tparam DimensionExponent The exponent to which the fundamental dimension of length is raised
 * (default: 1).
 */
template<short DimensionExponent = 1>
struct length: public base_dimension<length<DimensionExponent>, DimensionExponent> {};

/**
 * @brief Time dimension
 *
 * The time dimension represents the duration or interval between events in a physical system.
 * It is derived from the fundamental dimension of time.
 *
 * @tparam DimensionExponent The exponent to which the fundamental dimension of time is raised
 * (default: 1).
 */
template<short DimensionExponent = 1>
struct time: public base_dimension<time<DimensionExponent>, DimensionExponent> {};

/**
 * @brief Temperature dimension
 *
 * The temperature dimension represents the measure of heat or thermal energy in a physical system.
 * It is derived from the fundamental dimension of temperature.
 *
 * @tparam DimensionExponent The exponent to which the fundamental dimension of temperature is
 * raised (default: 1).
 */
template<short DimensionExponent = 1>
struct temperature: public base_dimension<temperature<DimensionExponent>, DimensionExponent> {};

/**
 * @brief Electric current dimension
 *
 * The electric current dimension represents the flow of electric charge in a physical system.
 * It is derived from the fundamental dimension of electric current.
 *
 * @tparam DimensionExponent The exponent to which the fundamental dimension of electric current is
 * raised (default: 1).
 */
template<short DimensionExponent = 1>
struct electric_current:
    public base_dimension<electric_current<DimensionExponent>, DimensionExponent> {};

/**
 * @brief Amount of substance dimension
 *
 * The amount of substance dimension represents the quantity of a chemical substance in a physical
 * system. It is derived from the fundamental dimension of amount of substance.
 *
 * @tparam DimensionExponent The exponent to which the fundamental dimension of amount of substance
 * is raised (default: 1).
 */
template<short DimensionExponent = 1>
struct amount_of_substance:
    public base_dimension<amount_of_substance<DimensionExponent>, DimensionExponent> {};

/**
 * @brief Luminous intensity dimension
 *
 * The luminous intensity dimension represents the measure of light emitted by a source in a
 * physical system. It is derived from the fundamental dimension of luminous intensity.
 *
 * @tparam DimensionExponent The exponent to which the fundamental dimension of luminous intensity
 * is raised (default: 1).
 */
template<short DimensionExponent = 1>
struct luminous_intensity:
    public base_dimension<luminous_intensity<DimensionExponent>, DimensionExponent> {};

/**
 * @brief Dimensionless dimension
 *
 * The dimensionless dimension represents a quantity that is independent of any physical dimensions.
 * It is derived from the fundamental dimension of dimensionless.
 *
 * @tparam DimensionExponent The exponent to which the fundamental dimension of dimensionless is
 * raised (default: 1).
 */
template<short DimensionExponent = 1>
struct dimensionless: public base_dimension<dimensionless<DimensionExponent>, DimensionExponent> {};

/* ---------- Derived Dimensions ---------- */
/**
 * @brief Speed dimension
 *
 * The speed dimension represents the rate of change of position in a physical system.
 * It is derived from the length and time dimensions.
 */
struct speed: public derived_dimension<length<>, time<-1>> {};

/**
 * @brief Frequency dimension
 *
 * The frequency dimension represents the number of oscillations or cycles per unit time in a
 * physical system. It is derived from the dimensionless and time dimensions.
 */
struct frequency: public derived_dimension<dimensionless<>, time<-1>> {};

/**
 * @brief Force dimension
 *
 * The force dimension represents the push or pull exerted on an object by another object in a
 * physical system. It is derived from the mass, length, and time dimensions.
 */
struct force: public derived_dimension<mass<>, length<>, time<-2>> {};

/**
 * @brief Energy dimension
 *
 * The energy dimension represents the ability or capacity to do work in a physical system.
 * It is derived from the mass, length, and time dimensions.
 */
struct energy: public derived_dimension<mass<>, length<2>, time<-2>> {};

/**
 * @brief Power dimension
 *
 * The power dimension represents the rate of doing work in a physical system.
 * It is derived from the mass, length, and time dimensions.
 */
struct power: public derived_dimension<mass<>, length<2>, time<-3>> {};

/**
 * @brief Electric charge dimension
 *
 * The electric charge dimension represents the amount of electric charge in a physical system.
 * It is derived from the electric current and time dimensions.
 */
struct electric_charge: public derived_dimension<electric_current<>, time<>> {};

/**
 * @brief Voltage dimension
 *
 * The voltage dimension represents the difference in electric potential between two points in a
 * physical system. It is derived from the mass, length, and time dimensions.
 */
struct voltage: public derived_dimension<mass<>, length<2>, time<-3>, electric_current<-1>> {};

/* ----------------------------------- Units ----------------------------------- */

/* ---------- Base Units ---------- */

/**
 * @brief Kilogram unit
 *
 * The kilogram is the base unit of mass in the International System of Units (SI).
 */
struct Kilogram: public mass<>, public base_unit<kilo, kg> {};

/**
 * @brief Hectogram unit
 *
 * The hectogram is a unit of mass that is equal to one-hundredth of a kilogram.
 */
struct Hectogram: public mass<>, public base_unit<hecto, hg> {};

/* ---------- Base Units for Length Dimension ---------- */

/**
 * @brief Meter unit
 *
 * The meter is the base unit of length in the International System of Units (SI).
 */
struct Meter: public length<>, public base_unit<root, m> {};

/* ---------- Base Units for Time Dimension ---------- */

/**
 * @brief Second unit
 *
 * The second is the base unit of time in the International System of Units (SI).
 */
struct Second: public time<>, public base_unit<second, s> {};

/**
 * @brief Minute unit
 *
 * The minute is a unit of time that is equal to sixty seconds.
 */
struct Minute: public time<>, public base_unit<minute, min> {};

/**
 * @brief Hour unit
 *
 * The hour is a unit of time that is equal to sixty minutes or 3600 seconds.
 */
struct Hour: public time<>, public base_unit<hour, h> {};

/**
 * @brief Day unit
 *
 * The day is a unit of time that is equal to twenty-four hours.
 */
struct Day: public time<>, public base_unit<day, d> {};

/* ---------- Base Units for Electric Current Dimension ---------- */

/**
 * @brief Ampere unit
 *
 * The ampere is the base unit of electric current in the International System of Units (SI).
 */
struct Ampere: public electric_current<>, public base_unit<root, A> {};

/* ---------- Derived Units ---------- */

/**
 * @brief Meters per second unit
 *
 * The meters per second unit is a derived unit that represents speed.
 */
struct MetersPerSecond: public derived_unit<speed, base_unit<root, m>, base_unit<second, s>> {};

/**
 * @brief Kilometers per hour unit
 *
 * The kilometers per hour unit is a derived unit that represents speed.
 */
struct KilometersPerHour: public derived_unit<speed, base_unit<kilo, km>, base_unit<hour, h>> {};

/**
 * @brief Hertz unit
 *
 * The hertz unit is a derived unit that represents frequency.
 */
struct Hertz: public derived_unit<frequency, base_unit<unit_r, unit_type>, base_unit<second, s>> {};

/**
 * @brief Newton unit
 *
 * The newton unit is a derived unit that represents force.
 */
struct Newton:
    public derived_unit<force, base_unit<kilo, kg>, base_unit<root, m>, base_unit<second, s>> {};

/**
 * @brief Joule unit
 *
 * The joule unit is a derived unit that represents energy.
 */
struct Joule:
    public derived_unit<energy, base_unit<kilo, kg>, base_unit<root, m>, base_unit<second, s>> {};

/**
 * @brief Watt unit
 *
 * The watt unit is a derived unit that represents power.
 */
struct Watt:
    public derived_unit<power, base_unit<kilo, kg>, base_unit<root, m>, base_unit<second, s>> {};

/**
 * @brief Coulomb unit
 *
 * The coulomb unit is a derived unit that represents electric charge.
 */
struct Coulomb: public derived_unit<electric_charge, base_unit<root, A>, base_unit<second, s>> {};

/**
 * @brief Volt unit
 *
 * The volt unit is a derived unit that represents voltage.
 */
struct Volt:
    public derived_unit<
        voltage,
        base_unit<kilo, kg>,
        base_unit<root, m>,
        base_unit<second, s>,
        base_unit<root, A>> {};

} // namespace zero::physics

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

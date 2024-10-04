/**
 * @file
 * @brief Contains type definitions for symbols that represent physical quantities.
 *
 * This module provides a set of symbol types that can be used to represent various units and
 * dimensions in the context of physical quantities. These symbols are designed to be used as part
 * of the `physics.quantities` library, which aims to provide a comprehensive framework for working
 * with physical quantities.
 */

export module physics.quantities:units.symbols;

/**
 * @namespace zero::physics
 */
export namespace zero::physics {
/**
 * @struct unit_symbol
 * @brief Base symbol type that can be used as a template parameter to create concrete symbol types.
 *
 * This struct serves as a base class for all other symbol types in this module. It provides a
 * minimal implementation of a symbol, allowing users to add additional functionality and properties
 * as needed.
 *
 * @tparam T The underlying type that represents the symbol's value or meaning.
 */
template<typename T>
struct unit_symbol {
    /**
     * @typedef symbol
     * @brief Type alias for the underlying type that represents the symbol's value or meaning.
     */
    using symbol = T;
};

/**
 * @concept Symbol
 * @brief Concept that defines a set of requirements for types to be considered symbols in this
 * module.
 *
 * This concept ensures that any type that meets its requirements can be used as a symbol in the
 * context of physical quantities. The main requirement is that the type must have a nested `symbol`
 * type alias that represents its value or meaning.
 *
 * @tparam T The type to be checked against the Symbol concept.
 */
template<typename T>
concept Symbol = requires { typename T::symbol; };

/**
 * ------------------------- Symbols for Units -------------------------
 */

/* ----- Symbols for represent dimensionless units ----- */

/**
 * @struct unit_type
 * @brief Symbol type that represents a dimensionless unit.
 *
 * This symbol type is used to indicate that a quantity has no dimensions or units. It can be used
 * as a placeholder in mathematical expressions or when working with quantities that are inherently
 * dimensionless.
 */
struct unit_type: unit_symbol<unit_type> {};

/* ----- Symbols related with the dimension of Mass ----- */

/**
 * @struct kg
 * @brief Symbol type that represents kilograms (kilogram).
 *
 * This symbol type is used to indicate that a quantity has units of mass in kilograms. It can be
 * used as part of mathematical expressions or when working with quantities that have mass
 * dimensions.
 */
struct kg: unit_symbol<kg> {};

/**
 * @struct hg
 * @brief Symbol type that represents hectograms (hectogram).
 *
 * This symbol type is used to indicate that a quantity has units of mass in hectograms. It can be
 * used as part of mathematical expressions or when working with quantities that have mass
 * dimensions.
 */
struct hg: unit_symbol<hg> {};

/**
 * @struct dag
 * @brief Symbol type that represents dekagrams (dekagram).
 *
 * This symbol type is used to indicate that a quantity has units of mass in dekagrams. It can be
 * used as part of mathematical expressions or when working with quantities that have mass
 * dimensions.
 */
struct dag: unit_symbol<dag> {};

/**
 * @struct g
 * @brief Symbol type that represents grams (gram).
 *
 * This symbol type is used to indicate that a quantity has units of mass in grams. It can be used
 * as part of mathematical expressions or when working with quantities that have mass dimensions.
 */
struct g: unit_symbol<g> {};

/**
 * @struct dg
 * @brief Symbol type that represents decigrams (decigram).
 *
 * This symbol type is used to indicate that a quantity has units of mass in decigrams. It can be
 * used as part of mathematical expressions or when working with quantities that have mass
 * dimensions.
 */
struct dg: unit_symbol<dg> {};

/**
 * @struct cg
 * @brief Symbol type that represents centigrams (centigram).
 *
 * This symbol type is used to indicate that a quantity has units of mass in centigrams. It can be
 * used as part of mathematical expressions or when working with quantities that have mass
 * dimensions.
 */
struct cg: unit_symbol<cg> {};

/**
 * @struct mg
 * @brief Symbol type that represents milligrams (milligram).
 *
 * This symbol type is used to indicate that a quantity has units of mass in milligrams. It can be
 * used as part of mathematical expressions or when working with quantities that have mass
 * dimensions.
 */
struct mg: unit_symbol<mg> {};

/**
 * @struct ng
 * @brief Symbol type that represents micrograms (microgram).
 *
 * This symbol type is used to indicate that a quantity has units of mass in micrograms. It can be
 * used as part of mathematical expressions or when working with quantities that have mass
 * dimensions.
 */
struct ng: unit_symbol<ng> {};

/**
 * @struct pg
 * @brief Symbol type that represents picograms (picogram).
 *
 * This symbol type is used to indicate that a quantity has units of mass in picograms. It can be
 * used as part of mathematical expressions or when working with quantities that have mass
 * dimensions.
 */
struct pg: unit_symbol<pg> {};

/* ----- Symbols related with the dimension of Length ----- */

/**
 * @struct km
 * @brief Symbol type that represents kilometers (kilometer).
 *
 * This symbol type is used to indicate that a quantity has units of length in kilometers. It can be
 * used as part of mathematical expressions or when working with quantities that have length
 * dimensions.
 */
struct km: unit_symbol<km> {};

/**
 * @struct hm
 * @brief Symbol type that represents hectometers (hectometer).
 *
 * This symbol type is used to indicate that a quantity has units of length in hectometers. It can
 * be used as part of mathematical expressions or when working with quantities that have length
 * dimensions.
 */
struct hm: unit_symbol<hm> {};

/**
 * @struct dam
 * @brief Symbol type that represents dekameters (dekameter).
 *
 * This symbol type is used to indicate that a quantity has units of length in dekameters. It can be
 * used as part of mathematical expressions or when working with quantities that have length
 * dimensions.
 */
struct dam: unit_symbol<dam> {};

/**
 * @struct m
 * @brief Symbol type that represents meters (meter).
 *
 * This symbol type is used to indicate that a quantity has units of length in meters. It can be
 * used as part of mathematical expressions or when working with quantities that have length
 * dimensions.
 */
struct m: unit_symbol<m> {};

/**
 * @struct dm
 * @brief Symbol type that represents decameters (decameter).
 *
 * This symbol type is used to indicate that a quantity has units of length in decameters. It can be
 * used as part of mathematical expressions or when working with quantities that have length
 * dimensions.
 */
struct dm: unit_symbol<dm> {};

/**
 * @struct cm
 * @brief Symbol type that represents centimeters (centimeter).
 *
 * This symbol type is used to indicate that a quantity has units of length in centimeters. It can
 * be used as part of mathematical expressions or when working with quantities that have length
 * dimensions.
 */
struct cm: unit_symbol<cm> {};

/**
 * @struct mm
 * @brief Symbol type that represents millimeters (millimeter).
 *
 * This symbol type is used to indicate that a quantity has units of length in millimeters. It can
 * be used as part of mathematical expressions or when working with quantities that have length
 * dimensions.
 */
struct mm: unit_symbol<mm> {};

/* ----- Symbols related with the dimension of Length ----- */

/**
 * @struct d
 * @brief Symbol type that represents days (day).
 *
 * This symbol type is used to indicate that a quantity has units of time in days. It can be used as
 * part of mathematical expressions or when working with quantities that have time dimensions.
 */
struct d: unit_symbol<d> {};

/**
 * @struct h
 * @brief Symbol type that represents hours (hour).
 *
 * This symbol type is used to indicate that a quantity has units of time in hours. It can be used
 * as part of mathematical expressions or when working with quantities that have time dimensions.
 */
struct h: unit_symbol<h> {};

/**
 * @struct min
 * @brief Symbol type that represents minutes (minute).
 *
 * This symbol type is used to indicate that a quantity has units of time in minutes. It can be used
 * as part of mathematical expressions or when working with quantities that have time dimensions.
 */
struct min: unit_symbol<min> {};

/**
 * @struct s
 * @brief Symbol type that represents seconds (second).
 *
 * This symbol type is used to indicate that a quantity has units of time in seconds. It can be used
 * as part of mathematical expressions or when working with quantities that have time dimensions.
 */
struct s: unit_symbol<s> {};

/**
 * @struct ms
 * @brief Symbol type that represents milliseconds (millisecond).
 *
 * This symbol type is used to indicate that a quantity has units of time in milliseconds. It can be
 * used as part of mathematical expressions or when working with quantities that have time
 * dimensions.
 */
struct ms: unit_symbol<ms> {};

/* ----- Symbols related with the dimension of Length ----- */

/**
 * @struct A
 * @brief Symbol type that represents amperes (ampere).
 *
 * This symbol type is used to indicate that a quantity has units of electric current in amperes. It
 * can be used as part of mathematical expressions or when working with quantities that have
 * electric current dimensions.
 */
struct A: unit_symbol<A> {};

} // namespace zero::physics

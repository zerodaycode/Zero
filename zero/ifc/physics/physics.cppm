/**
 * @brief Primary module interface for the `physics` library.
 *
 * This module contains mostly reexports for the internal libraries that compound the whole picture
 * of the physics library.
 */

export module physics;

/**
 * @brief Reexports for physical quantities and units from the physics.quantities module.
 */
export import physics::quantities;

/**
 * @brief Type information utilities for working with physical types.
 */
export import type_info;

/**
 * @brief String manipulation utilities for formatting physical quantity output.
 */
export import str_manip;

/**
 * @brief Defines C++20 concepts to design constraints to be used
 * across the libraries
 * 
 * @file concepts.cppm
 * @author Alex Vergara (pyzyryab@tutanota.com)
 * @version 0.1.0
 * @date 2022-12-11
 */

export module concepts;

import typedefs;

export namespace zero::concepts {

    /**
     * @brief Defines a constrait for container operations,
     * where the requested index to read or retrieve should be
     * inside a range between [0, N]
     * 
     * @tparam idx the index to access in a container
     * @tparam N the number of elements (size) stored in the container
     */
    template <zero::size_t idx, zero::size_t N>
    concept inside_bounds = requires () {
        requires idx <= N;
    };
}
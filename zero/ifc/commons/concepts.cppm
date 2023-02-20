/**
 * @brief General purpose concepts
 */

export module concepts;

import std;
import typedefs;

export namespace zero::concepts {

    /**
     * @brief checks if the type is a type with a push_back
     * member method implemented
     * 
     * @tparam C the container type 
     * @tparam T the type of value
     */
    template <typename C, typename T>
    concept has_push_back = requires(C& c, T&& t) {
        c.push_back(std::forward<T>(t));
    };

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
        requires idx < N;
    };
}
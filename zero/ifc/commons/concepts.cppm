//#pragma clang diagnostic ignored "-Wc++17-extensions"

/**
 * @brief General purpose concepts
 */

export module concepts;

import std;
import typedefs;
import type_traits;

export namespace zero::concepts {

    /// \brief Constrain for types that has an operator<< overload
    template <typename T>
    concept Ostreamable = requires(const T& t, std::ostream& os) {
        { os << t } -> std::same_as<std::ostream&>;
    };

    /// \brief Constrain for types that has an std::to_string implementation
    template <typename T>
    concept StringConvertible = requires(const T& t) {
        { std::to_string(t) } -> std::same_as<std::string>;
    };

    /// \brief Constrain for types with either operator<< or std::to_string
    template <typename T>
    concept Printable = Ostreamable<T> || StringConvertible<T>;

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
     * @brief Defines a constraint for container operations,
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

    /**
     * @brief Constrains the implementors to receive types that
     * shares the same template, without taking in consideration
     * the possible template arguments
     * @tparam T
     * @tparam U
     */
    template<class T, class U>
    concept SameTemplate = zero::same_template_v<T, U>;
}
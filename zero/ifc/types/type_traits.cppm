/**
 * @brief Contains custom type traits, not present in the standard library
 *
 * @def A type trait is a template struct that contains a member constant,
 * which in turn holds the answer to the question the type trait asks or
 * the transformation it performs.
 */
export module type_traits;

import std;

export namespace zero {
    /**
     * @brief Determines whenever a type T is the same type than other
     * type U, without taking in consideration the template parameters.
     */
    template<class T, class U>
    struct same_template {
        static auto test(...) -> std::false_type;

        template<template<class...> class C, class... R1s, class... R2s>
        static auto test(C<R1s...>, C<R2s...>) -> std::true_type;

        static constexpr bool value = decltype(test(std::declval<T>(), std::declval<U>()))::value;
    };

    /**
     * Nice to have, an alias request directly the value static member,
     * which holds the result of the comparison between the two templates
     */
    template<class T, class U>
    constexpr bool same_template_v = same_template<T, U>::value;
}
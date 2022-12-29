/**
 * @brief Iterators hierarchies and concepts
 * 
 * @file iterator.cppm
 * @author Alex Vergara (pyzyryab@tutanota.com)
 * @version 0.1.0
 * @date 2022-12-29
 */

export module iterator;

import std;

export namespace zero::iterator::concepts {
    /**
     * @brief Enforces the requeriments over the `Category` template argument
     * of the `zero::iterator::iterator` iterator type of pass only a iterator tag 
     * defined in the standard library. This allows the code of zero to be
     * perfectly compatible with any element that expects tag dispaching
     */
    template <typename T>
    concept iterator_category = requires () {
        std::is_same<T, std::input_iterator_tag>() ||
        std::is_same<T, std::output_iterator_tag>() ||
        std::is_same<T, std::forward_iterator_tag>() ||
        std::is_same<T, std::bidirectional_iterator_tag>() ||
        std::is_same<T, std::random_access_iterator_tag>() ||
        std::is_same<T, std::contiguous_iterator_tag>();
    };
}

export namespace zero::iterator {
    /**
    @brief The classical ISO standard definition of an iterator,
    as a templated base class for the iterators hierarchy. \n 
     * !Warn: Deprecated from the standard since C++17

     *  
     * @tparam Category the category of the iterator must be one of the `iterator
     * category tags` defined in the standard. Enforced by the `iterator_category`
     * concept defined in the `zero::iterator::concepts` namespace 
     * @tparam T usually know as the value_type
     * @tparam Distance the type that will determine the value obtained of
     * substracting two pointers
     * @tparam Pointer the pointer type. Usually T*, being T equals to value_type
     * @tparam Reference the reference type. Usually T&, being T equals to value_type
     */
    template<
        zero::iterator::concepts::iterator_category C,
        class T,
        class Distance = std::ptrdiff_t,
        class Pointer = T*,
        class Reference = T&
    > struct iterator;
}

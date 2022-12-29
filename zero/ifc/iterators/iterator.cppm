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
import typedefs;

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
     * @brief Implementation of the ISO standard defined family of iterators
     * being this `iterator_interface` the base class for the hierarchy.
     * 
     * The implementation design decision behind this family of iterators is using
     * the CRTP idiom, achieving much better expresiveness and performance,
     * thanks to the static polimorphism provided by this technique.
     * 
     * @tparam Derived the template argument for downcast to the correct child type
     * @tparam T usually know as the value_type
     * @tparam Category the category of the iterator must be one of the `iterator
     * @tparam Pointer the pointer type. Usually T*, being T equals to value_type
     * @tparam Reference the reference type. Usually T&, being T equals to value_type
     * category tags` defined in the standard. Enforced by the `iterator_category`
     * concept defined in the `zero::iterator::concepts` namespace 
     */
    template<
        typename Derived,
        typename T,
        typename pointer_type = T*,
        typename reference_type = T&, 
        zero::iterator::concepts::iterator_category C
    > struct iterator {
        using value_type        = T;
        using iterator_category = C;
        using pointer           = pointer_type;
        using reference         = reference_type;
        using difference_type   = zero::ptrdiff;
    };
}

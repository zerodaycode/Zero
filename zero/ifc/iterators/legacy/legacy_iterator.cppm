/**
 * @brief The classical iterator approach defined in the standard
 */

export module iterator:legacy_iterator;

import :detail;
import :concepts;

import std;
import typedefs;

export namespace zero::iterator::legacy {

    namespace iter_concepts = zero::iterator::concepts;

    /**
     * @brief Implementation of the classical family of iterators
     * defined by the standard until C++17, where the `iterator` type
     * got deprecated.
     * 
     * @tparam T usually know as the value_type
     * @tparam Category the category of the iterator must be one of the `iterator
     * category tags` defined in the standard. Enforced by the `iterator_category`
     * concept defined in the `zero::iterator::concepts` namespace 
     * @tparam Pointer the pointer type. Usually T*, being T equals to value_type
     * @tparam Reference the reference type. Usually T&, being T equals to value_type
     */
    template<
        iter_concepts::std_iterator_category Category,
        typename T,
        typename pointer_type = T*,
        typename reference_type = T&
    > struct iterator {
        using value_type        = T;
        using iterator_category = Category;
        using pointer           = pointer_type;
        using reference         = reference_type;
        using difference_type   = zero::ptrdiff;
    };
}
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
     * @tparam Category the category of the iterator must be one of the `iterator
     * category tags` defined in the standard. Enforced by the `iterator_category`
     * concept defined in the `zero::iterator::concepts` namespace 
     * @tparam T, which is usually known as the value_type
     * @tparam The pointer type. Usually T*, being the value_type T
     * @tparam The reference type. Usually T&, being the value_type T
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
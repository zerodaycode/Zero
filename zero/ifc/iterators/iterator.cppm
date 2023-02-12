/**
 * @brief Primary module interface for the iterators hierarchies,
 * implementations and concepts
 */

export module iterator;

export import :concepts;
export import :iterator_facade;
export import :legacy_iterator;

import :detail;

import std;
import typedefs;


/// ----------------- compile time tests ----------------------///
static_assert(
    zero::iterator::concepts::input_iterator<
        zero::iterator::old_input_iter<int>
    >, 
    "Failed to create the input iterator"
);
static_assert(
    std::input_iterator<
        zero::iterator::old_input_iter<int>
    >, 
    "zero::iterator::input_iter<T> isn't an std::input_iterator"
);

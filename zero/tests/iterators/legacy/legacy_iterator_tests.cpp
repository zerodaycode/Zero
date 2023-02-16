/**
 * @brief Test for the Array type of the collections module of Zero
 */

import std;
import collections;
import container;
import iterator;

#include "../../deps/catch.hpp"

using namespace zero;

collections::Array arr = collections::Array<int, 5>{1, 2, 3, 4, 5};

/// Tests for the legacy_input_iterator
auto it_begin = arr.begin();
auto it_end = arr.end();
auto it_begin_copy {it_begin};

/// Helper for reduce boilerplate WHEN-THEN scenario
/// cases.
template<int x, int to>
struct static_for {
    void operator()() {
        if constexpr (x + 1 > 1)
            ++it_begin;
        REQUIRE(*it_begin == arr.get<x>());
        static_for<x + 1, to>()();
    }
};
/// Specialization for determine when the recursive
/// template instanciations must stop
template<int to>
struct static_for<to, to> {
    void operator()() {}
};

SCENARIO("Test for the legacy input iterator", "[iterator::legacy_input_iterator]") {
    WHEN("a call to the operator++() over the begin iterator is made") {
        THEN("we are able to get the same result than with the .get<I>() method") {
            static_for<0, 5>()();
        }
    }
    WHEN("We make a copy of our iterator") {
        THEN("we are able to check that both are equals") {
            REQUIRE(it_begin_copy == it_begin_copy);
        }
    }
}

/**
 * @brief Test for the Array type of the collections module of Zero
 */

import std;
import collections;
import container;

#include "../../deps/catch.hpp"

using namespace zero;

constexpr collections::Array arr = collections::Array<int, 5>{1, 2, 3, 4, 5};

/// Tests for the legacy_input_iterator
auto it_begin = arr.begin();
auto it_end = arr.end();

/// Temporal concrete helper for execute loops that want to
/// pass variables to template arguments
template<int x, int to>
struct static_for {
    void operator()() {
        ++it_begin;
        REQUIRE(*it_begin == arr.get<x>());
        static_for<x + 1, to>()();
    }
};

template<int to>
struct static_for<to, to> {
    void operator()() 
    {}
};



SCENARIO("Test for the legacy input iterator", "[iterator::legacy_iterator]") {

    WHEN("a call to the operator++() over the begin iterator is made") {
        // for (int i = 0; i < arr.size(); i++) {
            // ++it_begin;
            THEN("we are able to get the same result than with the .get<I>() method") {
                REQUIRE(*it_begin == arr.get<0>());
                // static_for<0, 5>();
            }
        // }
    }

    WHEN("a call to the operator++() over the begin iterator is made") {
        ++it_begin;
        THEN("we are able to get the same result than with the .get<I>() method") {
            REQUIRE(*it_begin == arr.get<1>());
        }
    }

    WHEN("a call to the operator++() over the begin iterator is made") {
        it_begin++;
        THEN("we are able to get the same result than with the .get<I>() method") {
            REQUIRE(*it_begin == arr.get<2>());
        }
    }

    WHEN("a call to the operator++() over the begin iterator is made") {
        ++it_begin;
        THEN("we are able to get the same result than with the .get<I>() method") {
            REQUIRE(*it_begin == arr.get<3>());
        }
    }

    WHEN("a call to the operator++() over the begin iterator is made") {
        it_begin++;
        THEN("we are able to get the same result than with the .get<I>() method") {
            REQUIRE(*it_begin == arr.get<4>());
        }
    }
}

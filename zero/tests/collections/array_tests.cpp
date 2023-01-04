/**
 * @brief Test for the Array type of the collections module of Zero
 */

import std;
import collections;
import container;

#include "../deps/catch.hpp"

using namespace zero;

constexpr collections::Array a = collections::Array<long, 5>{1L, 2L, 3L};
auto b = new decltype(collections::Array<int, 5>{1, 2, 3, 4, 5})[0];
collections::Array c = collections::Array<long, 5>{1L, 2L, 3L};

TEST_CASE("Basic tests for the Array type", "[collections::Array]") {

    SECTION("length of the array") {
        REQUIRE( a.size() == 5 );
        REQUIRE( collections::Array<int, 1>{1}.size() == 1 );
    }

    SECTION(".get<I>()") {
        REQUIRE( a.get<0>() == 1 );
        REQUIRE( a.get<1>() == 2 );
        REQUIRE( a.get<2>() == 3 );
        REQUIRE( a.get<3>() == 0 );
        REQUIRE( a.get<4>() == 0 );
    }
    
    SECTION("get_or_nullptr(const int idx)") {
        REQUIRE( a.get_or_nullopt(12).value_or(-1) == -1 ); // Trying to get a value out-of-bounds
        REQUIRE( a.get_or_nullopt(2).value() == 3 ); // Safely unwrapping the value
    }
}

SCENARIO("Scenario: when trying to mutate a value at index I", "[Array: mut-ref-at]") {
            
    WHEN("by calling mut_ref_at<I>() and assign it a new value") {
        b->mut_ref_at<2>() = 10;
        
        THEN("the value should be successfully updated") {
            REQUIRE(b->get<2>() == 10);
        }
    }
}

SCENARIO("Scenario: when working with get_or_nullopt", "[Array]") {
            
    WHEN("a requested index is out-of-bounds and the value is unwrapped") {
        auto opt_wrapper = a.get_or_nullopt(12);
        
        THEN("an optional bad_access exception should ocurrs") {
            REQUIRE_THROWS_AS( opt_wrapper.value(), std::bad_optional_access );
        }
    }
}

SCENARIO("Scenario: The iterator library is modeled in Zero", "[Array]") {
            
    WHEN("we made our Array<T, N> iterable") {
        THEN("users can use for-range loop") {
            for (auto value : c)
                REQUIRE( value >= 0 );
        }
    }

    WHEN("we made our Array<T, N> iterable and const compatible") {
        THEN("so users can use for-range loop over const collections") {
            for (auto value : a)
                REQUIRE( value >= 0 );
        }
    }
}

/**
 * @brief Test for the `type_info` free function
 */

import std;
import type_info;

#include "../deps/catch.hpp"

using namespace zero;

TEST_CASE("Testing the returned values of zero::type_info", "[type_info]") {

    int a;

    SECTION(".get<I>()") {
        REQUIRE( type_name<a>() == "int" );
    }

}

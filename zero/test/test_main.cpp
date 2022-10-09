import zero;

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

using namespace zero;

// Test for the Array collections module
constexpr collections::Array a = collections::Array<int, 10>(1, 2, 3);
auto b = new decltype(collections::Array<int, 5>{1, 2, 3, 4, 5})[0];

TEST_CASE( "Testing the collections::Array", "[collections::Array]" ) {
    REQUIRE( a.get<0>() == 1 );
}
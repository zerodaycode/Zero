/**
 * @brief Test for the Array type of the collections module of Zero
 */

import std;
import physics;

#include "../../deps/catch.hpp"

using namespace zero::physics;

auto q1 = quantity<Kilogram, double>{3000.};
auto q2 = quantity<Hectogram, int>{72};
auto m1 = quantity<Meter>{5};
auto m2 = quantity<Meter>{10};

SCENARIO("Scenario: when we define some physical quantities in terms of magnitudes", "[quantity<Magnitude, T>...]") {

        WHEN("we perform an addition arithmetic operation in the form of the binary expression of x + y") {
            auto addition = q1 + q2;
        THEN("We are able to add magnitudes with the same dimension") {
            REQUIRE(addition.amount == 3007.2);
        }
    }
}

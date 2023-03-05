/**
 * @brief Test for the physical quantities defined in the physics module of Zero
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
    WHEN("we perform a subtraction arithmetic operation in the form of the binary expression of x - y") {
        auto subtraction = q1 - q2;
        THEN("We are able to add magnitudes with the same dimension") {
            REQUIRE(subtraction.amount == 2992.8);
        }
    }
    WHEN("we perform a multiplication in the form of the binary expression of x * y") {
        auto multiplication = q1 * q2;
        THEN("We are able to multiply magnitudes with the same dimension") {
            REQUIRE(multiplication.amount == 21600000.0);
        }
    }
    WHEN("we perform a division in the form of the binary expression of x / y") {
        auto division = q1 / q2;
        THEN("We are able to divide magnitudes with the same dimension") {
            REQUIRE_THAT(division.amount, Catch::WithinAbs(0.42, 0.01));
        }
    }
}

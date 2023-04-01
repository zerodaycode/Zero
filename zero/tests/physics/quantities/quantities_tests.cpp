/**
 * @brief Test for the physical quantities defined in the physics module of Zero
 */

import std;
import physics;

#include "../../deps/catch.hpp"

using namespace zero::physics;

auto q1 = quantity<Kilogram, double>{3000.};
auto q2 = quantity<Hectogram, int>{72};

constexpr auto velocity = quantity<MetersPerSecond> {300'000.};
constexpr auto velocity2 = quantity<KilometersPerHour> {200.};

SCENARIO("Scenario: when we define some physical quantities in terms of magnitudes", "[quantity<Magnitude, T>...]") {

    WHEN("we perform an addition arithmetic operation in the form of the binary expression of x + y") {
        auto bases_addition = q1 + q2;
        auto derived_addition = velocity + velocity2;
        THEN("We are able to add quantities with the same dimension") {
            REQUIRE(bases_addition.amount == 3007.2);
            REQUIRE_THAT(derived_addition.amount, Catch::WithinAbs(300055.555555556, 0.01));
        }
    }

    WHEN("we perform a subtraction arithmetic operation in the form of the binary expression of x - y") {
        auto bases_subtraction = q1 - q2;
        auto derived_subtraction = velocity - velocity2;
        THEN("We are able to subtract quantities with the same dimension") {
            REQUIRE(bases_subtraction.amount == 2992.8);
            REQUIRE_THAT(derived_subtraction.amount, Catch::WithinAbs(299944.444444444, 0.01));
        }
    }

    WHEN("we perform a multiplication in the form of the binary expression of x * y") {
        auto bases_multiplication = q1 * q2;
        auto derived_multiplication = velocity * velocity2;
        THEN("We are able to multiply quantities with the same dimension") {
            REQUIRE(bases_multiplication.amount == 21600000.0);
            REQUIRE_THAT(derived_multiplication.amount, Catch::WithinAbs(16666666.6666667, 0.01));
        }
    }

    WHEN("we perform a division in the form of the binary expression of x / y") {
        auto bases_division = q1 / q2;
        auto derived_division = velocity / velocity2;
        THEN("We are able to divide quantities with the same dimension") {
            REQUIRE_THAT(bases_division.amount, Catch::WithinAbs(0.42, 0.01));
            REQUIRE(derived_division.amount == 5400);
        }
    }
}

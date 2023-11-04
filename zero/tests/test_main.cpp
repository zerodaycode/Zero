import tsuite;
import std;

//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
//#include "deps/catch.hpp"

//using namespace zero;


#include "./math/matrix_tests.h"
//TEST_CASE( "Base tests entry point for The Zero Project", "[Zero Project]" ) {}

int main() {
    matrix_tests();
    RUN_TESTS();
    return 0;
}
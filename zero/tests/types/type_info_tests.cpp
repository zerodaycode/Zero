/**
 * @brief Test for the `type_info` free function
 */

import std;
import type_info;

#include "../deps/catch.hpp"

using namespace zero::types;

TEST_CASE("Testing the returned values of zero::types::type_info", "[type_info]") {

    int a {0};
    const int b {0};
    const long c {0L};
    long long d {0L};
    long long& e {d};

    int* f;             // Pointer to int
    const int* g;       // Pointer to const int
    int* const h {&a};       // Const pointer to int
    const long* const i {&c}; // Const pointer to const long
    const int* const j {nullptr}; // Const pointer to const int initialized as nullptr

    struct A;
    class B;

    SECTION(".type_name<I>()") {
        CHECK( type_name<decltype(a)>() == "int" );
        CHECK( type_name<decltype(b)>() == "const int" );
        CHECK( type_name<decltype(c)>() == "const long" );
        CHECK( type_name<decltype(d)>() == "long long" );
        CHECK( type_name<decltype(e)>() == "long long &" );

        CHECK( type_name<decltype(f)>() == "int *" );
        CHECK( type_name<decltype(g)>() == "const int *" );
        CHECK( type_name<decltype(h)>() == "int *const" );
        CHECK( type_name<decltype(i)>() == "const long *const" );
        CHECK( type_name<decltype(j)>() == "const int *const" );

        CHECK( type_name<void>() == "void" );
        CHECK( type_name<void*>() == "void *" );
        CHECK( type_name<A>() == "A" );
        CHECK( type_name<B>() == "B" );
    }

}

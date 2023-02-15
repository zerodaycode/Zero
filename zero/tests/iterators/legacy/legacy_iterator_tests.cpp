/**
 * @brief Test for the Array type of the collections module of Zero
 */

import std;
import collections;
import container;

#include "../deps/catch.hpp"

using namespace zero;

constexpr collections::Array a = collections::Array<int, 5>{1, 2, 3, 4, 5};
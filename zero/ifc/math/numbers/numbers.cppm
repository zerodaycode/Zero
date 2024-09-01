/// This module provides strong types over the most common sets of numbers in mathematics

export module math:numbers;

import std;
import math.symbols;

export import :numbers.naturals;
export import :numbers.integers;
export import :numbers.rationals;

export namespace zero::math {
    // TODO: Create individual concepts per Number type that allows to check more complex behaviour,
    // like overflows (is this possible with a concept??!), that they can be constructible from certain types
    // which allows us to reduce to only one template constructor per type instead of having lots of them

//    class Real {
//        double number; // TODO handle rationals and irrationals with std::variant?
//    };
//
//    class Complex {
//        Real real;
//        Real imaginary;
//    };

}


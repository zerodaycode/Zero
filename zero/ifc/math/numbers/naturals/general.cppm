/// module partition for hold mostly forward declaration of the 'numerical types'
export module math.numbers:general;

import std;
import math.ops;
import math.symbols;

export namespace zero::math {
    // Forward declarations
    class Natural;
    class Integer;
    class Rational;
    class Irrational;
    class Real;
    class Complex;
}

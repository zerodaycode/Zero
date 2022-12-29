/**
 * @brief Provides a custom way of reexport common types and symbols typically
 * found on some system headers in a convenient and encapsulated way.
 * 
 * The main motivation of this module interface unit is to wrap all the system
 * headers that has standard C++ typedefs, avoding the user to have to include
 * on every file that is required those definitions, that also must be defined
 * on multiple another system headers, like `std::size_t`, which can be found
 * on :
 *  ```
 *  Defined in header <cstddef>
 *  Defined in header <cstdio>
 *  Defined in header <cstdlib>
 *  Defined in header <cstring>
 *  Defined in header <ctime>
 *  Defined in header <cuchar>
 *  
 *  Defined in header <cwchar> (since C++17) 
 *  ```
 * 
 * @file typedefs.cppm
 * @author Alex Vergara (pyzyryab@tutanota.com)
 * @version 0.1.0
 * @date 2022-10-01
 */

export module typedefs;

import std;

export namespace zero {
    /**
     * @brief `zero::size_t` is a typedef for wrapping the `std::size_t`, which is the unsigned integer type of the result 
     * of the sizeof operator as well as the sizeof... operator and the alignof operator.

     * The bit width of std::size_t is not less than 16.

     * zero::size_t can store the maximum size of a theoretically possible object of any type (including array).

     * A type whose size cannot be represented by zero::size_t is ill-formed. On many platforms 
     * (an exception is systems with segmented addressing) zero::size_t can safely store the value of any non-member pointer,
     * in which case it is synonymous with std::uintptr_t. 
     */
    typedef std::size_t size_t;

    /**
     * @brief zero::ptrdiff_t is a type alias for the std::ptrdiff_t, 
     * being the signed integer type of the result of subtracting two pointers.
     * 
     * is used for pointer arithmetic and array indexing, if negative values are 
     * possible. 
     * Programs that use other types, such as int, may fail on, e.g. 64-bit systems
     * when the index exceeds INT_MAX or if it relies on 32-bit modular arithmetic
     * 
     * Most common place of use if usually working with iterators, specially to fullfil
     * the `difference_type` template argument
     */
    typedef std::ptrdiff_t ptrdiff;
}
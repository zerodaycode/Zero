/**
 * @brief A templated version of a raw array 
 * 
 * @file array.cppm
 * @author Alex Vergara (pyzyryab@tutanota.com)
 * @version 0.1.0
 * @date 2022-09-25
 * @copyright Copyright (c) 2022
 */

export module array;

import typedefs;

export namespace zero::collections {
    template <typename T, zero::size_t N>
    class Array {
        private:
            T array[];
    };
}
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
import <iostream>;

export namespace zero::collections {
    template <typename T, zero::size_t N>
    class Array {
        private:
            T array[N];
        public:
            template <typename... InitValues>
            Array(const InitValues&&... init_values) 
                : array{ init_values... }
            {
                for (size_t i = 0; i < N; i++)
                    std::cout << "Value[" << i << "]: " << array[i] << std::endl;
            }
    };
}
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
import <stdexcept>;
import <sstream>;

export namespace zero::collections {
    /**
     * @brief Interface for dealing with the different types of arrays provided by Zero
     * 
     * @tparam T the type of the elements which will be stored in the container
     */
    template<typename T>
    class Array {
        public:
            virtual T get(const zero::size_t idx) const = 0;
    };

    /**
     * @brief Wrapper over a legacy c-style raw array, encapsulating the low level
     * details to offer a high-level interface to work with a fixed-size array
     * stored on the stack
     * 
     * @tparam T the type of the elements which will be stored in the container
     * @tparam N the capacity of the StackArray with which will be initialized
     * 
     * `StackArray` has a constructor with a variadic template arguments that initializes
     * the array with the provided elements, up to the number constrained by N or less.
     * 
     * If the initializer takes n elements where n < N, non provided values
     * will be zero initialized.
     */
    template <typename T, zero::size_t N>
    class StackArray: Array<T> {
        private:
            T array[N];
        public:
            template <typename... InitValues>
            StackArray(const InitValues&&... init_values) 
                : array{ init_values... }
            {
                for (size_t i = 0; i < N; i++)
                    std::cout << "Value[" << i << "]: " << array[i] << std::endl;
            }

            T get(const zero::size_t idx) const override {
                if (idx >= sizeof(array) / sizeof(T)) {
                    std::ostringstream msg;
                    msg << "Index {" << idx << "} is out-of-bounds";
                    throw std::out_of_range(msg.str());
                }
                return array[idx];
            }
    };
}
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
import <optional>;
import <stdexcept>;
import <sstream>;

using namespace zero;
using namespace std;

export namespace zero::collections {
    /**
     * @brief Interface for dealing with the different types of containers provided by Zero
     * 
     * @tparam T the type of the elements which will be stored in the container
     */
    template<typename T>
    class Container {
        public:
            /**
             * @brief Returns a mut reference to the element at specified location `idx`,
             * with bounds checking.
             * 
             * @param idx a `size_t` value for specifiying the position of 
             * the element to retrieve.
             * @return T& to the element at idx position
             */
            virtual T& mut_ref_at(const size_t idx) const = 0;

            /**
             * @brief Returns a copy of the value of the element at the 
             * specified location `idx`, with bounds checking.
             * 
             * @param idx a `size_t` value for specifiying the position of 
             * the element to retrieve
             * @return optional<T> wrapping copy of the underlying value 
             * if is within the range of the container, `std::nullopt` is 
             * the index is out-of-bounds
             */
            virtual constexpr optional<T> get(const size_t idx) const = 0;
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
    class StackArray: public Container<T> {
        private:
            T array[N];
        public:
            template <typename... InitValues>
            StackArray(InitValues... init_values) 
                : array{ init_values... }
            {
                for (size_t i = 0; i < N; i++)
                    std::cout << "Value[" << i << "]: " << array[i] << std::endl;
            }

            /**
             * @brief delete the `new` operator, since the intended usage of
             * the type is to be a wrapper over a C-style array.
             * 
             * @return void* 
             */
            void* operator new(std::size_t) = delete;
            // void* operator new[](std::size_t) = delete;

            auto mut_ref_at(const size_t idx) const -> T(&) {
                if (idx >= sizeof(array) / sizeof(T))
                    throw std::out_of_range("Provided index is out-of-bounds");
                return (T&) array[idx];
            }

            constexpr optional<T> get(const size_t idx) const {
                if (idx >= sizeof(array) / sizeof(T))
                    return std::nullopt;
                return make_optional<T>(array[idx]);
            }
    };
}
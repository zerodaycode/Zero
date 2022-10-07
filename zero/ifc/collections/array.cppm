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
import <concepts>;

using namespace zero;
using namespace std;

template <size_t idx, size_t N>
concept IsInBounds = requires () {
    requires idx <= N;
};

export namespace zero::collections {
    /**
     * @brief Interface for dealing with the different types of containers provided by Zero
     * 
     * @tparam T the type of the elements which will be stored in the container
     */
    template<typename T, size_t N>
    class Container {
        public:
            template <size_t I>
            constexpr T& mut_ref_at() requires IsInBounds<I, N>;
            
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

    template<typename T, size_t N>
    class FixedSizeContainer : public Container<T, N> {
        protected:
            T arr[N];

            template <typename... InitValues>
            FixedSizeContainer(InitValues... init_values) 
                : arr{ init_values... } {}
        public:
            /**
             * @brief Returns a mut reference to the element at specified location `idx`,
             * with bounds checking.
             * 
             * @param idx a `size_t` value for specifiying the position of 
             * the element to retrieve.
             * @return T& to the element at idx position
             */
            template <size_t I>
            constexpr T& mut_ref_at() requires IsInBounds<I, N>
            {
                return arr[I];
            }

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
            constexpr optional<T> get(const size_t idx) const override
            {
                if (idx >= sizeof(this->arr) / sizeof(T))
                    return std::nullopt;
                return make_optional<T>(this->arr[idx]);
            }
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
    class StackArray : public FixedSizeContainer<T, N>
    {
        public:
            template <typename... InitValues>
            StackArray(InitValues... init_values) 
                : FixedSizeContainer<T, N>( init_values... ) {}

            /**
             * @brief delete the `new` operator, since the intended usage of
             * the type is to be a wrapper over a C-style array.
             * 
             * @return void* 
             */
            void* operator new(std::size_t) = delete;
    };
}
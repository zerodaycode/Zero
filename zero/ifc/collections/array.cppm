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

import std;
import typedefs;

using namespace zero;
using namespace std;

template <size_t idx, size_t N>
concept AccessInBounds = requires () {
    requires idx <= N;
};

export namespace zero::collections {
    /**
     * @brief Wrapper over a legacy c-style raw array, encapsulating the low level
     * details to offer a high-level interface to work with a fixed-size array
     * stored on the stack
     * 
     * @tparam T the type of the elements which will be stored in the container
     * @tparam N the capacity of the Array with which will be initialized
     * 
     * `Array` has a constructor with a variadic template arguments that initializes
     * the array with the provided elements, up to the number constrained by N or less.
     * 
     * If the initializer takes n elements where n < N, non provided values
     * will be zero initialized.
     */
    template<typename T, size_t N>
    class Array {
        private:
            T array[N];

            /**
             * @brief delete the `new` operator, since the intended usage of
             * the type is to be a wrapper over a C-style array.
             * 
             * @return void* 
             */
            void* operator new(std::size_t) = delete;

        public:

            /**
             * @brief returns the number of elements stored in the underlying
             * array
             * 
             * @return constexpr int 
             */
            [[nodiscard]]
            constexpr int len() const noexcept { return sizeof(array) / sizeof(T); }

            /**
             * @brief public constructor for the Array<T, N> type
             * 
             * @tparam InitValues variadic template argument for provide
             * at most, so much elements in initialization as the value
             * holded by the template parameter N, being the capacitiy
             * of the Array<T, N>
             */
            template <typename... InitValues>
            constexpr Array(InitValues... init_values) 
                : array{ init_values... } {}

            /**
             * @brief Returns a copy of the value of the element at the 
             * specified location `idx`, with bounds checking.
             * 
             * @param I a `size_t` templated value for specifiying the position of 
             * the element to retrieve
             * 
             * @return a copy value of the ith element T at index I
             */
            template <size_t I>
            constexpr T get() const {
                return array[I];
            }

            /**
             * @brief Returns a copy of the value of the element at the 
             * specified location `idx`, with bounds checking.
             * 
             * @param idx a `size_t` value for specifiying the position of 
             * the element to retrieve
             * 
             * @return optional<T> wrapping copy of the underlying value 
             * if is within the range of the container, `std::nullopt` is 
             * the index is out-of-bounds
             */
            constexpr optional<T> get_or_nullopt(const size_t idx) const {
                if (idx >= sizeof(array) / sizeof(T))
                    return std::nullopt;
                return make_optional<T>(array[idx]);
            }

            /**
             * @brief Returns a const reference to the element at specified location `idx`,
             * with bounds checking.
             * 
             * @tparam I a `size_t` value for specifiying the position of 
             * the element to retrieve.
             * 
             * @return read-only const T& to the element at idx position
             */
            template <size_t I>
            requires AccessInBounds<I, N>
            constexpr T const& const_ref_at() const noexcept {
                return array[I];
            }

            /**
             * @brief Returns a mut reference to the element at specified location `idx`,
             * with bounds checking.
             * 
             * This method is designed to change the value of some element at index `I`
             * of the underlying fixed size container.
             * 
             * @tparam idx a `size_t` value for specifiying the position of 
             * the element to retrieve.
             * 
             * @return T& to the element at idx position
             */
            template <size_t I>
            requires AccessInBounds<I, N> 
            constexpr T& mut_ref_at() noexcept {
                return array[I];
            }
    };
}
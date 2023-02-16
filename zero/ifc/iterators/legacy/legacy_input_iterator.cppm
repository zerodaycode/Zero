export module iterator:legacy_input_iterator;

import :legacy_iterator;
import std;

export namespace zero::iterator::legacy {
    /**
     * @brief Specific type alias for avoiding writing operations
     * with operator*() and operator->() 
    */
    template <typename T>
    using base_it = iterator<std::input_iterator_tag, const T>;

    /**
     * @brief A generic implementation of an input_iterator, that serves
     * as a coding example for of an input iterator for containers or ranges
     * that have its elements placed in contiguous memory addresses (from [0, N)).
     * 
     * This iterator can be directly used in containers like `std::Array` and `std::vector`,
     * or replicas, like `zero::collections::Array` or `zero::collections::vector`, but no
     * in other ones that does not follows the memory layout described above, like
     * it will be directly UB work with them. 
     */
    template <typename T>
    struct input_iter: base_it<T> {
        private:
            typename base_it<T>::pointer _ptr;

        public:
            constexpr input_iter<T>() = default;
            constexpr explicit input_iter<T>(typename base_it<T>::pointer ptr = nullptr)
                : _ptr { ptr } {}
            constexpr ~input_iter<T>() = default;
            constexpr input_iter<T>(const input_iter<T>& other) = default;
            constexpr input_iter<T>(input_iter<T>&& other) noexcept = default;

            [[nodiscard]]
            constexpr auto operator=(typename base_it<T>::pointer ptr) -> input_iter<T>& { 
                _ptr = ptr; return *this; 
            }
            constexpr auto operator=(const input_iter<T>&) -> input_iter<T>& = default;
            constexpr auto operator=(input_iter<T>&&) noexcept -> input_iter<T>& = default;

            [[nodiscard]]
            constexpr auto operator*() const noexcept -> const typename base_it<T>::reference {
                return *_ptr;
            }

            [[nodiscard]]
            constexpr auto operator->() const noexcept -> const typename base_it<T>::pointer {
                return _ptr;
            }

            constexpr auto operator++() noexcept -> input_iter& {
                ++this-> _ptr;
                return *this;
            }

            constexpr void operator++(int) noexcept {
                ++(*this);
            }

            [[nodiscard]]
            constexpr friend auto operator==(const input_iter& lhs, const input_iter& rhs) noexcept -> bool {
                return lhs._ptr == rhs._ptr;
            }

            [[nodiscard]]
            constexpr friend auto operator!=(const input_iter& lhs, const input_iter& rhs) noexcept -> bool {
                return not (lhs == rhs);
            }
    };
}
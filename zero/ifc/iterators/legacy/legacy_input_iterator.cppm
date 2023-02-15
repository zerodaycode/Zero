export module iterator:legacy_input_iterator;

import :legacy_iterator;
import std;

export namespace zero::iterator::legacy {
    /**
     * @brief A generic implementation of an input_iterator
     */
    template <typename T>
    struct input_iter: iterator<std::input_iterator_tag, T> {
        using base_it = iterator<std::input_iterator_tag, T>;

        private:
            typename base_it::pointer _ptr;

        public:
            input_iter<T>() = delete;
            explicit input_iter<T>(typename base_it::pointer ptr = nullptr)
                : _ptr { ptr } {}
            ~input_iter<T>() = default;
            input_iter<T>(const input_iter<T>& other) = default;
            input_iter<T>(input_iter<T>&& other) noexcept = default;

            auto operator=(typename base_it::pointer ptr) -> input_iter<T>& { _ptr = ptr; return *this; }
            auto operator=(const input_iter<T>&) -> input_iter<T>& = default;
            auto operator=(input_iter<T>&&) noexcept -> input_iter<T>& = default;

            [[nodiscard]]
            auto operator->() const noexcept -> typename base_it::pointer {
                return _ptr;
            }

            [[nodiscard]]
            auto operator*() const noexcept -> typename base_it::reference {
                return *_ptr;
            }

            auto operator++() noexcept -> input_iter& {
                ++this-> _ptr;
                return *this;
            }

            void operator++(int) noexcept {
                ++(*this);
            }

            [[nodiscard]]
            friend auto operator==(input_iter& self, input_iter& rhs) noexcept -> bool {
                return self._ptr == rhs._ptr;
            }

            [[nodiscard]]
            friend auto operator!=(input_iter& self, input_iter& rhs) noexcept -> bool {
                return self._ptr != rhs._ptr;
            }
    };
}
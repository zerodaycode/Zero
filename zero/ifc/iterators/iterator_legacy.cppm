/**
 * @brief The classical iterator approach defined in the standard
 */

export module iterator:legacy_iterator;

import :detail;
import :concepts;

import std;
import typedefs;

export namespace zero::iterator {

    namespace iter_concepts = zero::iterator::concepts;

    /**
     * @brief Implementation of the classical family of iterators
     * defined by the standard until C++17, where the `iterator` type
     * got deprecated.
     * 
     * @tparam T usually know as the value_type
     * @tparam Category the category of the iterator must be one of the `iterator
     * category tags` defined in the standard. Enforced by the `iterator_category`
     * concept defined in the `zero::iterator::concepts` namespace 
     * @tparam Pointer the pointer type. Usually T*, being T equals to value_type
     * @tparam Reference the reference type. Usually T&, being T equals to value_type

     */
    template<
        iter_concepts::std_iterator_category Category,
        typename T,
        typename pointer_type = T*,
        typename reference_type = T&
    > struct base_iterator {
        using value_type        = T;
        using iterator_category = Category;
        using pointer           = pointer_type;
        using reference         = reference_type;
        using difference_type   = zero::ptrdiff;
    };

    /**
     * @brief A generic implementation of an input_iterator
     */
    template <typename T>
    struct old_input_iter: base_iterator<std::input_iterator_tag, T> {
        using base_it = base_iterator<std::input_iterator_tag, T>;

        private:
            typename base_it::pointer _ptr;

        public:
            old_input_iter<T>() = delete;
            explicit old_input_iter<T>(typename base_it::pointer ptr = nullptr)
                : _ptr { ptr } {}
            ~old_input_iter<T>() = default;
            old_input_iter<T>(const old_input_iter<T>& other) = default;
            old_input_iter<T>(old_input_iter<T>&& other) noexcept = default;

            auto operator=(typename base_it::pointer ptr) -> old_input_iter<T>& { _ptr = ptr; return *this; }
            auto operator=(const old_input_iter<T>&) -> old_input_iter<T>& = default;
            auto operator=(old_input_iter<T>&&) noexcept -> old_input_iter<T>& = default;

            [[nodiscard]]
            auto operator->() const -> typename base_it::pointer {
                return _ptr;
            }

            [[nodiscard]]
            auto operator*() const -> typename base_it::reference {
                return *_ptr;
            }

            auto operator++() -> old_input_iter& {
                ++this-> _ptr;
                return *this;
            }

            void operator++(int) {
                ++(*this);
            }

            [[nodiscard]]
            friend auto operator==(old_input_iter& self, old_input_iter& rhs) -> bool {
                return self._ptr == rhs._ptr;
            }

            [[nodiscard]]
            friend auto operator!=(old_input_iter& self, old_input_iter& rhs) -> bool {
                return self._ptr != rhs._ptr;
            }
    };
}
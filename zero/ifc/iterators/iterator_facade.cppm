/**
 * @brief A facade to dealing with iterators in a modern approach
 */

export module iterator:iterator_facade;
import :detail;

import std;

export namespace zero::iterator {
    /**
 * @brief CRTP base class for provide an iterator facade that quickly
 * allows the user to build any kind of iterator
 */
template <typename Derived>
    class iterator_facade {
        private:
            friend Derived;
            iterator_facade() {}
            
            auto _self() -> Derived& {
                return static_cast<Derived&>(*this);
            }
            auto _self() const -> const Derived& {
                return static_cast<const Derived&>(*this);
            }
        
        public:
            decltype(auto) operator*() const {
                return _self().dereference();
            }

            auto operator->() const {
                decltype(auto) ref = **this;
                if constexpr (std::is_reference_v<decltype(ref)>) {
                    // `ref` is a true reference, and we're safe to take its address
                    return std::addressof(ref);
                } else {
                    // `ref` is *not* a reference. Returning its address would be the
                    // address of a local. Return that thing wrapped in an proxy_reference.
                    return ::iterator::__detail::proxy_reference(std::move(ref));
                }
            }

            // Prefix increment operator overload
            [[nodiscard]]
            Derived& operator++() {
                _self().increment();
                return _self();
            }

            // Postfix increment operator overload
            [[nodiscard]]
            Derived operator++(int) {
                auto copy = _self();
                ++*this;
                return copy;
            }

            // Prefix decrement operator overload
            [[nodiscard]]  // TODO Requieres here for ex, bidirectional iters?
            auto operator--() -> Derived&
            requires ::iterator::__detail::impls_decrement<Derived> {
                _self().decrement();
                return _self();
            }

            // Postfix increment operator overload
            [[nodiscard]]
            auto operator--(int) -> Derived
            requires ::iterator::__detail::impls_decrement<Derived> {
                auto copy = *this;
                --*this;
                return copy;
            }

            [[nodiscard]]
            friend auto operator==(const Derived& self, const Derived& rhs) -> bool {
                return self.equals_to(rhs);
            }

            [[nodiscard]]
            friend auto operator!=(const Derived& self, const Derived& rhs) -> bool {
                return self._ptr != rhs._ptr;
            }
    };

    template <typename T>
    class input_iter: public iterator_facade<input_iter<T>> {
        private:
            T* _ptr;
        
        /// Three minimum-required APIs

        const input_iter& dereference() const {
            return _ptr;
        }

        void increment() {
            _ptr = input_iter(++_ptr);
        }

        bool equals_to(input_iter o) const {
            return _ptr == o._ptr;
        }
    };
}

/// Partial template specialization for out iterator facade
template <typename Iter>
    requires (std::is_base_of<zero::iterator::iterator_facade<Iter>, Iter>())
struct std::iterator_traits<Iter> {
    static const Iter& _it;

    using reference       = decltype(*_it);
    using pointer         = decltype(_it.operator->());
    using value_type      = ::iterator::__detail::infer_value_type_t<Iter>;
    using difference_type = ::iterator::__detail::infer_difference_type_t<Iter>;

    using iterator_category =
        std::conditional_t<
        ::iterator::__detail::meets_random_access<Iter>,
        // We meet the requirements of random-access:
        std::random_access_iterator_tag,
        // We don't:
        std::conditional_t<
            ::iterator::__detail::meets_bidirectional<Iter>,
            // We meet requirements for bidirectional usage:
            std::bidirectional_iterator_tag,
            // We don't:
            std::conditional_t<
                ::iterator::__detail::is_single_pass<Iter>,
                // A single-pass iterator is an input-iterator:
                std::input_iterator_tag,
                // Otherwise we are a forward iterator:
                std::forward_iterator_tag
            >
        >
    >;

    // Just set this to the iterator_category, for now
    using iterator_concept = iterator_category;
};

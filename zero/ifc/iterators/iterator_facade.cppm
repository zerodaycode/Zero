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

            /// Reference operator overload
            auto operator->() const {
                decltype(auto) ref = **this;
                if constexpr (std::is_reference_v<decltype(ref)>) {
                    // `ref` is a true reference, and we're safe to take its address
                    return std::addressof(ref);
                } else {
                    // `ref` is *not* a reference. Returning its address would be the
                    // address of a local. Return that thing wrapped in an proxy_reference.
                    return ::iterator::__detail::arrow_proxy(ref);
                }
            }

            [[nodiscard]]
            Derived& operator++() {
                _self().increment();
                return _self();
            }

            [[nodiscard]]
            Derived operator++(int) {
                auto copy = _self();
                ++*this;
                return copy;
            }

            [[nodiscard]]
            auto operator--() -> Derived&
            requires ::iterator::__detail::impls_decrement<Derived> {
                _self().decrement();
                return _self();
            }

            [[nodiscard]]
            auto operator--(int) -> Derived
            requires ::iterator::__detail::impls_decrement<Derived> {
                auto copy = *this;
                --*this;
                return copy;
            }

            [[nodiscard]] friend Derived& operator+=(
                Derived& self,
                ::iterator::__detail::difference_type_arg<Derived> auto offset
            ) requires ::iterator::__detail::impls_advance<Derived> {
                self.advance(offset);
                return self;
            }

            [[nodiscard]] friend Derived& operator-=(
                Derived& self,
                ::iterator::__detail::difference_type_arg<Derived> auto offset
            ) requires ::iterator::__detail::impls_advance<Derived> {
                return self = self - offset;
            }

            [[nodiscard]] friend Derived& operator+(
                Derived& lhs,
                ::iterator::__detail::difference_type_arg<Derived> auto offset
            ) requires ::iterator::__detail::impls_advance<Derived> {
                return lhs += offset;
            }

            [[nodiscard]] friend Derived& operator+(
                ::iterator::__detail::difference_type_arg<Derived> auto offset,
                Derived& rhs
            ) requires ::iterator::__detail::impls_advance<Derived> {
                return rhs += offset;
            }

            [[nodiscard]] friend Derived& operator-(
                Derived& self,
                ::iterator::__detail::difference_type_arg<Derived> auto offset
            ) requires ::iterator::__detail::impls_advance<Derived> {
                return self + -offset;
            }

            [[nodiscard]] 
            friend auto operator-(const Derived& lhs, const Derived& rhs) -> Derived&
            requires ::iterator::__detail::impls_distance_to<Derived> {
                return rhs.distance_to(lhs);
            }

            [[nodiscard]] decltype(auto) operator[](
                ::iterator::__detail::difference_type_arg<Derived> auto position
            ) requires ::iterator::__detail::impls_advance<Derived> {
                return *(_self() + position);
            }

            [[nodiscard]]
            friend auto operator==(const Derived& lhs, const Derived& rhs) -> bool {
                return lhs.equals_to(rhs);
            }

            [[nodiscard]]
            friend auto operator!=(const Derived& lhs, const Derived& rhs) -> bool {
                return lhs._ptr != rhs._ptr;
            }

            [[nodiscard]]
            friend auto operator<=>(const Derived& lhs, const Derived& rhs) -> bool 
            requires ::iterator::__detail::impls_distance_to<Derived> {
                return (lhs - rhs) <=> 0;
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

/**
 * @brief Partial template specialization for out iterator facade
 * 
 * @tparam Iter the type that is derived from our `iterator_facade`
 * specialized on itself
 * 
 * @details For make out `iterator_facade` happy compatible with all
 * the things on the standard that expects some properties from an iterator,
 * we must specialize `std::iterator_traits` for our facade.
 * 
 * Why? For example, when some algorythm will request for 
 * `iterator_implementation::value_type`, the implementor will get errors,
 * because there's no `value_type` type member.
 * 
 * `std::iterator_traits` is unable to see through our facade, because we can't
 * just define an `type_value` type member, because in the definition of our facade,
 * the `self_type` is still an incomplete type, and only it knows the real type of
 * `self_type::value_type`, and we can't know it until after the full definition
 * of `self_type`.
 * 
 * This is a classical know issue with the `CRTP` idiom, the derived types are uncomplete
 * types until is full definition. Luckily, the standard allows to specialize 
 * `std::iterator_traits` for user defined types, so the specialization below is a
 * partial specialization for any class that is derived from our facade and specialized
 * on itself
 */ 
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

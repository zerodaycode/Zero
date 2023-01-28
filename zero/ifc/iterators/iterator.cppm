/**
 * @brief Iterators hierarchies and concepts
 * 
 * @file iterator.cppm
 * @author Alex Vergara (pyzyryab@tutanota.com)
 * @version 0.1.0
 * @date 2022-12-29
 */

export module iterator;

import std;
import typedefs;

export namespace zero::iterator::concepts {
    /**
     * @brief Enforces the requeriments over the `Category` template argument
     * of the `zero::iterator::iterator` iterator type of pass only a iterator tag 
     * defined in the standard library. This allows the code of zero to be
     * perfectly compatible with any element that expects tag dispaching
     */
    template <typename T>
    concept std_iterator_category = 
        std::is_same<T, std::input_iterator_tag>() ||
        std::is_same<T, std::output_iterator_tag>() ||
        std::is_same<T, std::forward_iterator_tag>() ||
        std::is_same<T, std::bidirectional_iterator_tag>() ||
        std::is_same<T, std::random_access_iterator_tag>() ||
        std::is_same<T, std::contiguous_iterator_tag>();

    /**
     * @brief Alias for define that a template parameter T is a reference `T = T&`
     */
    template<typename T>
    using template_arg_as_ref = T&;

    /**
     * @brief satisfied if and only if the type is referenceable (in particular, not void)
     */
    template<typename T>
    concept can_reference = requires() { typename template_arg_as_ref<T>; };

    /**
     * @brief satisfied if and only if the type is dereferenceable (in particular, not void)
     */
    template<typename T>
    concept dereferenceable = requires(T& t) {
	    { *t } -> can_reference;
	};

    /**
     * @brief Computes the value type of T. 
     * If `std::iterator_traits<std::remove_cvref_t<T>>` is not specialized, 
     * then `std::iter_value_t<T>` is 
     * `std::indirectly_readable_traits<std::remove_cvref_t<T>>::value_type`. 
     * 
     * Otherwise, it is `std::iterator_traits<std::remove_cvref_t<T>>::value_type` 
     */
    template<dereferenceable T>
    using iter_reference_t = decltype(*std::declval<T&>());

    template<typename T>
    concept is_signed_integer_like = 
        std::signed_integral<T>;
        // || is_signed_int128<T> || // Not yet
        // std::same_as<T, std::__max_diff_type>;  // Neither ready

    template<typename Iter>
    concept weakly_incrementable = std::movable<Iter> && requires(Iter i) {
        typename std::iter_difference_t<Iter>;
        requires is_signed_integer_like<std::iter_difference_t<Iter>>;
        { ++i } -> std::same_as<Iter&>;   // not required to be equality-preserving
        i++;                              // not required to be equality-preserving
    };

    /**
     * @brief The `input_or_output_iterator` concept forms the basis of the iterator concept taxonomy;
     * every iterator type satisfies the `input_or_output_iterator` requirements.
     */
    template <typename Iter>
    concept input_or_output_iterator = weakly_incrementable<Iter> &&
        requires(Iter i) { { *i } -> can_reference; };

    /**
    * @brief The input_iterator concept is a refinement of input_or_output_iterator, adding the requirement that the r
    * deferenced values can be read (via indirectly_readable) and the requirement 
    * that the iterator concept tag be present.
    */
    template <typename Iter>
    concept input_iterator =
        input_or_output_iterator<Iter> &&  // from the std
        std::indirectly_readable<Iter> &&  // from the std
        requires (Iter i, Iter rhs) {
            { i.operator*() } -> std::same_as<typename Iter::reference>;
            { i.operator->() } -> std::same_as<typename Iter::pointer>;
            { i.operator++() } -> std::same_as<decltype(std::declval<Iter&>())>;
            { i++ } -> std::same_as<void>;
            { operator==(i, rhs) } -> std::same_as<bool>;
            { operator!=(i, rhs) } -> std::same_as<bool>;
        };
}

namespace iterator::__detail {
    /**
     * @brief helper struct to safetly play with temporaries
     */
    template<class Reference>
    struct proxy_reference {
        Reference r;
        Reference* operator->() {
            return &r;
        }
    };

    /**
     * @brief The iterator declares itself a single pass iterator.
     * input or output iterator must meet this requirement
     */
    template <typename T>
    concept is_single_pass = bool(T::single_pass_iterator);

    /**
     * @brief Requires to the implementors to define the
     * `decrement()` member function.
     * 
     * Bidirectional iterators or higher should be constrained
     * by this concept.
     */
    template <typename T>
    concept impls_decrement = requires(T it) { it.decrement(); };

    /**
     * @brief Yields true if-and-only-if it has a member `.distance_to` that can be
     * invoked with another instance of const T. 
     * 
     * We check const because distance_to must be a non-modifying operation.
     */
    template <typename T>
    concept impls_distance_to = requires (const T it) { it.distance_to(it); };
    
    // Partial template speciallizations to help us to deduce the
    // iterator mandatory `difference_type`
    template <typename>
    struct infer_difference_type { using type = std::ptrdiff_t; };

    // Case when `T` provides a `.distance_to()` member method
    template <impls_distance_to T>
    struct infer_difference_type<T> {
        static const T& it;
        using type = decltype(it.distance_to(it));
    };

    template <typename T>
    using infer_difference_type_t = typename infer_difference_type<T>::type;

    // Partial template speciallizations to help us to deduce the
    // iterator mandatory `value:type`
    template <typename T>
    requires requires { typename T::value_type; }
    struct infer_value_type {
        using type = typename T::value_type;
    };

    template <typename T>
    using infer_value_type_t = typename infer_value_type<T>::type;


    /**
     * @brief 
     * 
     */
    template <typename T>
    concept impls_advance = requires 
        (T it, const infer_difference_type_t<T> offset)
    {
        it.advance(offset);
    };

    // We can meet "random access" if it provides
    // both .advance() and .distance_to()
    template <typename T>
    concept meets_random_access =
        impls_advance<T> && impls_distance_to<T>;

    // We meet `bidirectional` if we are random_access, OR we have .decrement()
    template <typename T>
    concept meets_bidirectional =
        meets_random_access<T> || impls_decrement<T>;

}


export namespace zero::iterator {

    namespace iter_concepts = zero::iterator::concepts;

    /**
     * @brief Implementation of the classical family of iterators
     * being this `base_interface` the base class for the hierarchy.
     * 
     * The implementation design decision behind this family of iterators is using
     * the CRTP idiom, achieving much better expresiveness and performance,
     * thanks to the static polimorphism provided by this technique.
     * 
     * NOTE: Sure? Offering an already implemented (an customizable?) family 
     * of iterators? Could we do something as boost::iterator_facade? But sightly
     * different?
     * 
     * @tparam Derived the template argument for downcast to the correct child type
     * @tparam T usually know as the value_type
     * @tparam Category the category of the iterator must be one of the `iterator
     * category tags` defined in the standard. Enforced by the `iterator_category`
     * concept defined in the `zero::iterator::concepts` namespace 
     * @tparam Pointer the pointer type. Usually T*, being T equals to value_type
     * @tparam Reference the reference type. Usually T&, being T equals to value_type

     */
    template<
        // typename Derived, // Not yet!
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
        
        // Three minimum-required APIs
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

/// ----------------- compile time tests ----------------------///
static_assert(
    zero::iterator::concepts::input_iterator<
        zero::iterator::old_input_iter<int>
    >, 
    "Failed to create the input iterator"
);
static_assert(
    std::input_iterator<
        zero::iterator::old_input_iter<int>
    >, 
    "zero::iterator::input_iter<T> isn't an std::input_iterator"
);

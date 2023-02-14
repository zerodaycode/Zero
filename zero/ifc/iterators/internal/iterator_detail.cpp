/**
 * @brief Internal partition for holding the implementation
 * details that won't contribute to the external API of the
 * iterator primary module interface
 */
module iterator:detail;

import std;


namespace iterator::__detail {
    /**
     * @brief implementation of the `arrow_proxy` idiom, to safetly play with temporaries.
     * Basically, this proxy class is needed to implement the `operator->` for 
     * iterators which can't return pointers
     */
    template<class Reference>
    struct arrow_proxy {
        Reference r;

        arrow_proxy(Reference&& value) : r(std::move(value)) {}
        Reference* operator->() const { return &r; }
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
    
    // Partial template speciallizations to allow us to deduce the
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

    /// Partial template speciallizations to allow us to deduce the
    /// iterator mandatory `value:type`
    template <typename T>
    requires requires { typename T::value_type; }
    struct infer_value_type {
        using type = typename T::value_type;
    };

    template <typename T>
    using infer_value_type_t = typename infer_value_type<T>::type;


    /// checks if the implementor contains a member .advance method
    template <typename T>
    concept impls_advance = requires 
        (T it, const infer_difference_type_t<T> offset)
    {
        it.advance(offset);
    };

    /// checks if the implementor contains a member .equals method
    template <typename T>
    concept impls_equals_to = requires (const T it) {
        { it.equal_to(it) -> boolean };
    };

    /// We can determine if it is a "random access" iterator if it
    /// provides both .advance() and .distance_to()
    template <typename T>
    concept meets_random_access =
        impls_advance<T> && impls_distance_to<T>;

    /// We can determine if an iterator is a `bidirectional` if is at least
    /// random_access or if has .decrement() member method
    template <typename T>
    concept meets_bidirectional =
        meets_random_access<T> || impls_decrement<T>;

    /// Helper concept to declare a later-deduced parameter type,
    /// but that type is still constrained to be a type that we
    /// don’t yet know
    template <typename Arg, typename Iter>
    concept difference_type_arg =
        std::convertible_to<Arg, infer_difference_type_t<Iter>>;

}

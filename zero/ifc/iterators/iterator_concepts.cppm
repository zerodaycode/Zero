/**
 * @brief Contains definition of concepts defined by the standard
 * or newer ones, defined by `Zero`
 */

export module iterator:concepts;

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
            { i++ } -> std::same_as<Iter>;
            { operator==(i, rhs) } -> std::same_as<bool>;
            { operator!=(i, rhs) } -> std::same_as<bool>;
        };
}

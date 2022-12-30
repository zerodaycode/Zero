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

/**
 * @brief Namespace for define the interface requeriments of the iterator concepts
 */
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
     * @brief ALias for define that a template parameter T is a reference `T = T&`
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
        i++;                           // not required to be equality-preserving
    };

    /**
     * @brief The `input_or_output_iterator` concept forms the basis of the iterator concept taxonomy;
     * every iterator type satisfies the `input_or_output_iterator` requirements.
     */
    template <typename Iter>
    concept input_or_output_iterator = weakly_incrementable<Iter> && 
    requires(Iter i) {
        { *i } -> can_reference;
    };
}

export namespace zero::iterator {

    namespace iter_cpts = zero::iterator::concepts;

    /**
     * @brief Implementation of the ISO standard defined family of iterators
     * being this `iterator_interface` the base class for the hierarchy.
     * 
     * The implementation design decision behind this family of iterators is using
     * the CRTP idiom, achieving much better expresiveness and performance,
     * thanks to the static polimorphism provided by this technique.
     * 
     * @tparam Derived the template argument for downcast to the correct child type
     * @tparam T usually know as the value_type
     * @tparam Category the category of the iterator must be one of the `iterator
     * @tparam Pointer the pointer type. Usually T*, being T equals to value_type
     * @tparam Reference the reference type. Usually T&, being T equals to value_type
     * category tags` defined in the standard. Enforced by the `iterator_category`
     * concept defined in the `zero::iterator::concepts` namespace 
     */
    template<
        typename Derived,
        iter_cpts::std_iterator_category Category,
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
}

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
 * @brief 
 */
namespace zero::iterator_traits {
    /**
     * @brief SFINAE friendly iterator_traits
     */
    template<typename Iter, typename = void>
    struct iterator_traits {};

    /**
     * @brief An iterator such that iterator_traits<Iter> 
     * names a specialization generated from the primary template.
     */
    template<typename Iter>
    concept __primary_traits_iter = 
        std::is_base_of_v<iterator_traits<Iter, void>, iterator_traits<Iter>>;

    template<typename Iter, typename T>
    struct __iter_traits_impl
    { using type = iterator_traits<Iter>; };

    template<typename Iter, typename T>
    requires __primary_traits_iter<Iter>
    struct __iter_traits_impl<Iter, T> {};

    // ITER_TRAITS
    template<typename Iter, typename T = Iter>
    using __iter_traits = typename __iter_traits_impl<Iter, T>::type;

    template<typename Iter>
    struct __iter_concept_impl;

    // ITER_CONCEPT(I) is ITER_TRAITS(I)::iterator_concept if that is valid.
    template<typename Iter>
    requires requires { typename __iter_traits<Iter>::iterator_concept; }
    struct __iter_concept_impl<Iter>
    { using type = typename __iter_traits<Iter>::iterator_concept; };

    // Otherwise, ITER_TRAITS(I)::iterator_category if that is valid.
    template<typename Iter>
    requires (!requires { typename __iter_traits<Iter>::iterator_concept; }
        && requires { typename __iter_traits<Iter>::iterator_category; })
    struct __iter_concept_impl<Iter>
    { using type = typename __iter_traits<Iter>::iterator_category; };

    // Otherwise, random_access_tag if iterator_traits<I> is not specialized.
    template<typename Iter>
    requires (!requires { typename __iter_traits<Iter>::iterator_concept; }
	  && !requires { typename __iter_traits<Iter>::iterator_category; }
	  && __primary_traits_iter<Iter>)
    struct __iter_concept_impl<Iter>
    { using type = std::random_access_iterator_tag; };

    // Otherwise, there is no ITER_CONCEPT(I) type.
    template<typename Iter>
    struct __iter_concept_impl{};

    /**
    //  * @brief the std library internal implementation's way to get a tag for a given type
    //  */
    template<typename Iter>
    using iter_concept = typename __iter_concept_impl<Iter>::type;
}

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
     * @brief Computes the value type of T. If `std::iterator_traits<std::remove_cvref_t<T>>`
     * is not specialized, then `std::iter_value_t<T>` is 
     * `std::indirectly_readable_traits<std::remove_cvref_t<T>>::value_type`. 
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
    requires(Iter i) {
        { *i } -> can_reference;
    };

    // /**
    //  * @brief The input_iterator concept is a refinement of input_or_output_iterator, adding the requirement that the r
    //  * eferenced values can be read (via indirectly_readable) and the requirement 
    //  * that the iterator concept tag be present.
    //  */
    // template <typename Iter>
    // concept input_iterator =
    //     input_or_output_iterator<I> &&
    //     std::indirectly_readable<I> &&
    //     requires { typename iter_reference_t<I>; } &&
    //     std::derived_from</*ITER_CONCEPT*/<I>, 
    //     std::input_iterator_tag>;  // Could we get rid out of this in our custom impl?
    // }
}

export namespace zero::iterator {

    namespace iter_cpts = zero::iterator::concepts;

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
     * @tparam Pointer the pointer type. Usually T*, being T equals to value_type
     * @tparam Reference the reference type. Usually T&, being T equals to value_type
     * category tags` defined in the standard. Enforced by the `iterator_category`
     * concept defined in the `zero::iterator::concepts` namespace 
     */
    template<
        typename Derived, // Sure? 
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

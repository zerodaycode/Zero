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
    * eferenced values can be read (via indirectly_readable) and the requirement 
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
        // typename Derived, // Sure? 
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

    /**
     * @brief A generic implementation of an input_iterator
     */
    template <typename T>
    struct input_iter: base_iterator<std::input_iterator_tag, T> {
        // Convenient way of access the inherited type members
        using base_it = base_iterator<std::input_iterator_tag, T>;

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
            auto operator->() -> typename base_it::pointer {
                return _ptr;
            }

            [[nodiscard]]
            auto operator->() const -> const typename base_it::pointer {
                return _ptr;
            }

            [[nodiscard]]
            auto operator*() -> typename base_it::reference {
                return *_ptr;
            }

            [[nodiscard]]
            auto operator*() const -> const typename base_it::reference {
                return *_ptr;
            }

            auto operator++() -> input_iter& {
                ++this-> _ptr;
                return *this;
            }

            void operator++(int) {
                ++(*this);
            }

            [[nodiscard]]  //! NOTE: Should this be equality with `Sentinel`?
            friend auto operator==(input_iter& self, input_iter& rhs) -> bool {
                return self._ptr == rhs._ptr;
            }

            [[nodiscard]]
            friend auto operator!=(input_iter& self, input_iter& rhs) -> bool {
                return self._ptr != rhs._ptr;
            }
    };
}

/// ----------------- compile time tests ----------------------///
static_assert(
    zero::iterator::concepts::input_iterator<
        zero::iterator::input_iter<int>
    >, 
    "Failed to create the input iterator"
);

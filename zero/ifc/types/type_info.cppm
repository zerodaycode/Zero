/**
 * @brief Provides facilities to retrieve information about types at compile time
 * 
 * Current implementation returns an string version of a template
 * parameter type T when it's passed as template argument in the `type_name<T>()`
 * freestanding function, available under the `zero::types` namespace
 */

export module type_info;

import std;

export namespace zero::types {
    /**
     * @tparam T - the template argument that will be stringifyed
     * @return an std::string_view with the string representation of the template argument
     */
    template <typename T>
    [[nodiscard]] consteval std::string_view type_name();

    /**
     * @brief Template specialization for void types, that chooses any arbitrary type
     * (void in this case) as a mock for the flux that retrieves the T type name, or directly returns void for
     * T = void
     */
    template <>
    [[nodiscard]] consteval std::string_view type_name<void>() { return "void"; }
}

using mock_type = void;

template <typename T>
inline consteval std::string_view wrapped_type_name() {
#ifdef __clang__
    return __PRETTY_FUNCTION__;
#elif defined(__GNUC__)
    return __PRETTY_FUNCTION__;
#elif defined(_MSC_VER)
    return __FUNCSIG__;
#else
#error "Unsupported compiler"
#endif
}

inline consteval std::size_t wrapped_type_name_prefix_length() { 
    return wrapped_type_name<mock_type>()
        .find(zero::types::type_name<mock_type>()); 
}

inline consteval std::size_t wrapped_type_name_suffix_length() { 
    return wrapped_type_name<mock_type>().length() 
        - wrapped_type_name_prefix_length() 
        - zero::types::type_name<mock_type>().length();
}

export namespace zero::types {
    // Implementation of `type_name`
    template <typename T>
    [[nodiscard]] consteval std::string_view type_name() {
        constexpr auto wrapped_name = wrapped_type_name<T>();
        constexpr auto prefix_length = wrapped_type_name_prefix_length();
        constexpr auto suffix_length = wrapped_type_name_suffix_length();
        constexpr auto type_name_length = wrapped_name.length() - prefix_length - suffix_length;
        return wrapped_name.substr(prefix_length, type_name_length);
    }
}
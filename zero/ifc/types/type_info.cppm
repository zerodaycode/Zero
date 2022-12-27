/**
 * @brief Exports free standing helper functions to obtain info about `types`
 * 
 * @file type_info.cppm
 * @author Alex Vergara (pyzyryab@tutanota.com)
 * @version 0.1.0
 * @date 2022-12-27
 */

export module type_info;

import std;

/**
 * @tparam T the template argument that will be stringyfied
 * @return constexpr std::string_view with the string representation of the template argument
 */
template <typename T> constexpr std::string_view type_name();

/**
 * @brief Primary template specialization for void types
 */
template <>
constexpr std::string_view type_name<void>() { return "void"; }

using type_name_prober = void;

template <typename T>
constexpr std::string_view wrapped_type_name() 
{
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

constexpr std::size_t wrapped_type_name_prefix_length()
{ 
    return wrapped_type_name<type_name_prober>().find(type_name<type_name_prober>()); 
}

constexpr std::size_t wrapped_type_name_suffix_length()
{ 
    return wrapped_type_name<type_name_prober>().length() 
        - wrapped_type_name_prefix_length() 
        - type_name<type_name_prober>().length();
}

export namespace zero {
    /**
     * @brief Implementation of `type_name`
     */
    template <typename T>
    constexpr std::string_view type_name() 
    {
        constexpr auto wrapped_name = wrapped_type_name<T>();
        constexpr auto prefix_length = wrapped_type_name_prefix_length();
        constexpr auto suffix_length = wrapped_type_name_suffix_length();
        constexpr auto type_name_length = wrapped_name.length() - prefix_length - suffix_length;
        return wrapped_name.substr(prefix_length, type_name_length);
    }
}
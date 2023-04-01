/**
* Actions and operations over character or text types
*/

export module str_manip;

import std;

template <typename T>
concept SplittableString =
    std::is_same_v<const char*, std::remove_reference_t<T>> ||
    std::is_same_v<std::string, std::remove_reference_t<T>> ||
    std::is_same_v<std::string_view, std::remove_reference_t<T>>;

export namespace zero {
    template <SplittableString T>
    auto split_str(T&& str, const char* delimiter) -> std::vector<std::string> {
        std::vector<std::string> tokens;

        std::istringstream iss;
        if constexpr (std::is_same_v<std::remove_reference_t<T>, std::string_view)
            iss = std::istringstream(std::string {str});
        else
            iss = std::istringstream(std::forward<T>(str));

        std::string token;
        while (std::getline(iss, token, *delimiter))
            tokens.push_back(token);

        return tokens;
    }
}

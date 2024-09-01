export module tsuite:assertions;

import std;
import concepts;

using namespace zero::concepts;

template <Printable T, Printable U>
constexpr inline void throw_on_failed_test(const T& expected, const U& actual);

export {
    /// @brief Compares two values. Generates a test failed if values are non-equal.
    /// @param actual the given or computed value
    /// @param expected the given expectation for the computed value
    template<typename T, typename U>
        requires (!std::is_pointer_v<T> && !std::is_pointer_v<U>)
    constexpr void assertEquals(const T& expected, const U& actual) {
        ::throw_on_failed_test(expected, actual);
    }

    ///  @brief Compares two values being T pointer types.
    /// Generates a test failed if the values after dereference the pointers are non-equal.
    template<typename T>
    constexpr void assertEquals(const T* expected_ptr, const T* actual_ptr) {
        const auto expected   = *expected_ptr;
        const auto actual     = *actual_ptr;

        ::throw_on_failed_test(expected, actual);
    }


    /// @brief Compares two values. Generates a test failed if the values are equals.
    template<typename T>
        requires (!std::is_pointer_v<T>)
    constexpr void assertNotEquals(const T& expected, const T& actual) {
        ::throw_on_failed_test(expected, actual);
    }


    /// @brief Compares two values being T pointer types.
    /// Generates a test failed if the values after dereference
    /// the pointers are non-equal.
    template<typename T>
    constexpr void assertNotEquals(const T* expected_ptr, const T* actual_ptr) {
        const auto expected   = *expected_ptr;
        const auto actual     = *actual_ptr;

        ::throw_on_failed_test(expected, actual);
    }
}

// Detail -- TODO move to an impl module partition

/// \brief custom internal exception for the assertions failure
class assertion_failed : public std::exception {
private:
    std::string message_;

public:
    explicit assertion_failed(const std::string& message)
        : message_(message) {}

    [[nodiscard]] const char* what() const noexcept override {
        return message_.c_str();
    }
};

/// \brief helper to reduce cognitive complexity,
/// \enabled when the concept {\link @StringConvertible} is satisfied
template<typename T, typename U>
constexpr inline void throw_on_failed_test_str_impl(const T& expected, const U& actual) {
    if (expected != actual) {
        const auto expected_str   = std::to_string(expected);
        const auto actual_str     = std::to_string(actual);

        std::string msg {};
        msg.reserve(29 + expected_str.size() + actual_str.size() + 11);

        msg += "Assertion failed: expected = "; // 29
        msg += expected_str;
        msg += ", actual = "; // 11
        msg += actual_str;

        throw assertion_failed(msg);
    }
}

/// \brief helper to reduce cognitive complexity,
/// \enabled when the concept {\link @Ostreamable} is satisfied
template<typename T, typename U>
constexpr inline void throw_on_failed_test_oss_impl(const T& expected, const U& actual) {
    if (expected != actual) {
        std::ostringstream oss;
        oss << "Assertion failed: expected = ";
        oss << expected;
        oss << ", actual = ";
        oss << actual;

        throw assertion_failed(oss.str()); // TODO use a better one
    }
}

template <Printable T, Printable U>
constexpr inline void throw_on_failed_test(const T& expected, const U& actual) {
    if constexpr (StringConvertible<T> && StringConvertible<U>)
        throw_on_failed_test_str_impl(expected, actual);
    else
        throw_on_failed_test_oss_impl(expected, actual);
}

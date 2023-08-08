export module tsuite:assertions;

import std;

export {
    /**
    * Compares two values. Generates a test failed if values are non-equal.
    */
    template<typename T>
        requires (!std::is_pointer_v<T>)
    void assertEquals(const T& expected, const T& actual) {
        if (expected != actual)
            throw std::runtime_error("Assertion failed: expected = " + std::to_string(expected) +
                                     ", actual = " + std::to_string(actual));
    }

    /**
    * Compares two values being T pointer types.
    * Generates a test failed if the values after dereference
    * the pointers are non-equal.
    */
    template<typename T>
    void assertEquals(const T* expected_ptr, const T* actual_ptr) {
        auto expected   = *expected_ptr;
        auto actual     = *actual_ptr;

        if (expected != actual)
            throw std::runtime_error("Assertion failed: expected = " + std::to_string(expected) +
                                     ", actual = " + std::to_string(actual));
    }

    /**
    * Compares two values. Generates a test failed if the values are equals.
    */
    template<typename T>
        requires (!std::is_pointer_v<T>)
    void assertNotEquals(const T& expected, const T& actual) {
        if (expected == actual)
            throw std::runtime_error("Assertion failed: expected = " + std::to_string(expected) +
                                     ", actual = " + std::to_string(actual));
    }

    /**
    * Compares two values being T pointer types.
    * Generates a test failed if the values after dereference
    * the pointers are non-equal.
    */
    template<typename T>
    void assertNotEquals(const T* expected_ptr, const T* actual_ptr) {
        auto expected   = *expected_ptr;
        auto actual     = *actual_ptr;

        if (expected == actual)
            throw std::runtime_error("Assertion failed: expected = " + std::to_string(expected) +
                                     ", actual = " + std::to_string(actual));
    }
}
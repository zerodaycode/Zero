export module math.ops:arithmetic;

import std;

export namespace zero::math {
    template <typename T>
    [[nodiscard]] constexpr auto value_retriever(T& val) {
        if constexpr (std::is_pointer_v<T>)
            return *val;
        else
            return val;
    }

    template <typename T>
    [[nodiscard]] constexpr auto add(const T& lhs, const T& rhs) -> std::remove_pointer_t<T> {
        return value_retriever(lhs) + value_retriever(rhs);
    }

    template <typename T>
    [[nodiscard]] constexpr auto minus(const T& lhs, const T& rhs) -> std::remove_pointer_t<T> {
        return value_retriever(lhs) - value_retriever(rhs);
    }

    template <typename T>
    [[nodiscard]] constexpr auto multiply(const T& lhs, const T& rhs) -> std::remove_pointer_t<T> {
        return value_retriever(lhs) * value_retriever(rhs);
    }

    template <typename T>
    [[nodiscard]] constexpr auto divide(const T& lhs, const T& rhs) -> std::remove_pointer_t<T> {
        return value_retriever(lhs) / value_retriever(rhs);
    }

    [[nodiscard]] constexpr double power_of(const double base, const int exponent) {
        double result = 1;
        const int limit = ((exponent >= 0) ? exponent : exponent * -1);
        for (int i = 0; i < limit; i++)
            result *= (exponent >= 0) ? base : 1 / base;
        return result;
    }
}

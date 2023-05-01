export module math.ops:arithmetic;


export namespace zero::math {
    [[nodiscard]]
    constexpr double power_of(const double base, const int exponent) {
        double result = 1;
        const int limit = ((exponent >= 0) ? exponent : exponent * -1);
        for (int i = 0; i < limit; i++)
            result *= (exponent >= 0) ? base : 1/base;
        return result;
    }

    [[nodiscard]]
    inline consteval double consteval_power_of(const double base, const int exponent) {
        return power_of(base, exponent);
    }
}

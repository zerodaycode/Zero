export module math.ops:algebraic;

export namespace zero::math {
    namespace gcd_ops {
        [[nodiscard]]
        constexpr int gcd(int a, int b) {
            while (b != 0) {
                auto t = b;
                b = a % b;
                a = t;
            }
            return a;
        }

        template <typename... Args>
        [[nodiscard]] constexpr int gcd(int a, int b, Args... args) {
            auto intermediate = gcd(a, b);
            return gcd(intermediate, args...);
        }
    }

    // Using-declaration to bring names into zero::math namespace
    using gcd_ops::gcd;
}

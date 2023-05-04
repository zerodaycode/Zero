export module math.ops:algebraic;

export namespace zero::math {
    namespace gcd_ops {
         /// Computes the greatest common divisor (GCD) of two integers a and b
        [[nodiscard]]
        constexpr int gcd(int a, int b) {
            while (b != 0) {
                auto t = b;
                b = a % b;
                a = t;
            }
            return a;
        }

        /// Computes the greatest common divisor (GCD) of N integer given numbers
        template <typename... Args>
        [[nodiscard]] constexpr int gcd(int a, int b, Args... args) {
            return gcd(gcd(a, b), args...);
        }
    }

    namespace lcm_ops {
        /// Computes the least common multiple (LCM) of two integers a and b
        int lcm(int a, int b) {
          return a * b / gcd_ops::gcd(a, b);
        }

        /// Computes the least common multiple (LCM) of n integers
        template <typename... Args>
        int lcm(int a, int b, Args... args) {
            return lcm(lcm(a, b), args...);
        }
    }

    // Using-declaration to bring names into zero::math namespace
    using gcd_ops::gcd;
    using lcm_ops::lcm;
}

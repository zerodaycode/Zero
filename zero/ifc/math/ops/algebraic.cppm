export module math.ops:algebraic;


export namespace zero::math {
    [[nodiscard]]
    constexpr int gcd(int a, int b) {
        while (b != 0) {
            int t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    [[nodiscard]]
    inline consteval int consteval_gcd(int a, int b) {
        return gcd(a, b);
    }
}

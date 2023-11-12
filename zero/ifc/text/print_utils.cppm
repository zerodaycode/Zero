export module print_utils;
import formatter;
import std;


export namespace zero::fmt {

    template<typename... Args>
    constexpr void print(const std::string& format, Args... args) {
        std::cout << formatter(format, args...);
    }

    template<typename... Args>
    constexpr void println(const std::string& format, Args... args) {
        print(format + "\n", args...);
    }

    void newln() {
        std::cout << "\n";
    }
}

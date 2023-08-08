export module print_utils;
import std;
import formatter;


export namespace zero::fmt {

    template<typename... Args>
    void print(const std::string& format, Args... args) {
        std::cout << formatter(format, args...);
    }

    template<typename... Args>
    void println(const std::string& format, Args... args) {
        print(format + "\n", args...);
    }

}

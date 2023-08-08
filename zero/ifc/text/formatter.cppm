/**
* Provides functions and enums for string formatting
*/

export module formatter;

import std;

template<typename T>
std::string stringify(const T& t) {
    std::ostringstream oss;
    oss << t;
    return oss.str();
}

export namespace zero::fmt {

    template<typename... Args>
    std::string formatter(const std::string& format, Args... args) {
        std::deque<std::string> argStrings{ stringify(args)... };
        std::string result;
        bool escape_next = false;

        for (size_t i = 0; i < format.size(); ++i) {
            if (format[i] == '\\' && !escape_next) {
                escape_next = true;
            } else if (format[i] == '{' && i + 1 < format.size() && format[i + 1] == '}' && !escape_next) {
                if (argStrings.empty())
                    throw std::runtime_error("Not enough arguments provided");

                result += argStrings.front();
                argStrings.pop_front();
                ++i;  // Skip the next character ('}')
            } else if (format[i] == '{' && escape_next) {
                result += '{';
                escape_next = false;
            } else {
                result += format[i];
                escape_next = false;
            }
        }

        if (!argStrings.empty())
            throw std::runtime_error("Too many arguments provided");

        return result;
    }
}

/**
* Provides functions and enums for string formatting and styling
*/

export module format;

import std;

template<typename T>
std::string stringify(const T& t) {
    std::ostringstream oss;
    oss << t;
    return oss.str();
}

export namespace zero::fmt {

    enum class Color {
        DEFAULT,  // Default console color
        RED = 196,
        ORANGE = 202,
        YELLOW = 226,
        GREEN = 46,
        BLUE = 21,
        PURPLE = 93,
        CYAN = 51,
        WHITE = 15,
        GREY = 244,
        BLACK = 16
    };

    enum class Modifier {
        BOLD = 1,
        FAINT = 2,
        ITALIC = 3,
        UNDERLINE = 4,
        BLINK = 5,
        REVERSE = 7,
        HIDDEN = 8
    };

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

    std::string stylize(const std::string& text, Color color, const std::vector<Modifier>& modifiers) {
        std::string colorCode = color == Color::DEFAULT ? "" : "\033[38;5;" + std::to_string(static_cast<int>(color)) + "m";
        std::string modifierCodes = "";

        for (const auto& modifier : modifiers) {
            modifierCodes += "\033[" + std::to_string(static_cast<int>(modifier)) + "m";
        }

        std::string resetCodes = "";
        for (size_t i = 0; i < modifiers.size(); ++i) {
            resetCodes += "\033[0m";
        }

        return modifierCodes + colorCode + text + resetCodes + "\033[0m";
    }
}

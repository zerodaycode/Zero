/**
* Provides functions and enums for string styling
*/

export module stylizer;

import std;

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

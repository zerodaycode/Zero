/**
* Provides functions and enums for string styling
*/

export module stylizer;

import std;

export namespace zero::fmt {

    enum class Color {
        DEFAULT, // Default console color

        // Standard ANSI foreground colors
        BLACK = 30,
        RED = 31,
        GREEN = 32,
        YELLOW = 33,
        BLUE = 34,
        MAGENTA = 35,
        CYAN = 36,
        WHITE = 37,

        // Bright ANSI foreground colors
        BRIGHT_BLACK = 90,
        BRIGHT_RED = 91,
        BRIGHT_GREEN = 92,
        BRIGHT_YELLOW = 93,
        BRIGHT_BLUE = 94,
        BRIGHT_MAGENTA = 95,
        BRIGHT_CYAN = 96,
        BRIGHT_WHITE = 97,

        // Standard ANSI background colors
        BG_BLACK = 40,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_YELLOW = 43,
        BG_BLUE = 44,
        BG_MAGENTA = 45,
        BG_CYAN = 46,
        BG_WHITE = 47,

        // Bright ANSI background colors
        BG_BRIGHT_BLACK = 100,
        BG_BRIGHT_RED = 101,
        BG_BRIGHT_GREEN = 102,
        BG_BRIGHT_YELLOW = 103,
        BG_BRIGHT_BLUE = 104,
        BG_BRIGHT_MAGENTA = 105,
        BG_BRIGHT_CYAN = 106,
        BG_BRIGHT_WHITE = 107,

        // Extended 256-color palette
        // Reds
        EXT_RED = 196,
        EXT_LIGHT_RED = 203,
        EXT_DARK_RED = 124,
        EXT_CRIMSON_RED = 160,
        EXT_FIREBRICK_RED = 88,
        EXT_CORAL_RED = 210,
        EXT_INDIAN_RED = 167,
        EXT_SALMON_RED = 209,

        // Oranges
        EXT_ORANGE = 202,
        EXT_LIGHT_ORANGE = 214,
        EXT_DARK_ORANGE = 208,
        EXT_SOFT_ORANGE = 216,
        EXT_DEEP_ORANGE = 166,

        // Yellows
        EXT_YELLOW = 226,
        EXT_LIGHT_YELLOW = 228,
        EXT_DARK_YELLOW = 220,
        EXT_GOLDEN_YELLOW = 184,
        EXT_SUN_YELLOW = 190,
        EXT_MUSTARD_YELLOW = 172,

        // Greens
        EXT_GREEN = 46,
        EXT_LIGHT_GREEN = 82,
        EXT_DARK_GREEN = 28,
        EXT_LIME_GREEN = 118,
        EXT_SEA_GREEN = 85,
        EXT_OLIVE_GREEN = 58,
        EXT_EMERALD_GREEN = 34,

        // Blues
        EXT_BLUE = 21,
        EXT_LIGHT_BLUE = 39,
        EXT_DARK_BLUE = 19,
        EXT_SKY_BLUE = 117,
        EXT_NAVY_BLUE = 17,
        EXT_AQUA_BLUE = 45,
        EXT_TEAL_BLUE = 30,
        EXT_STEEL_BLUE = 67,

        // Purples
        EXT_PURPLE = 93,

        // Other colors
        EXT_CYAN = 51,
        EXT_WHITE = 15,
        EXT_GREY = 244,
        EXT_BLACK = 16,
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
        // The color code will depend on whether we are using a standard ANSI color
        // or an extended color from the 256-color palette.
        std::string colorCode = "";
        if (static_cast<int>(color) >= 30 && static_cast<int>(color) <= 37) {
            // Standard ANSI colors are within the range of 30-37.
            // These are directly used following the escape sequence "\033[".
            colorCode = "\033[" + std::to_string(static_cast<int>(color)) + "m";
        } else {
            // Colors outside the range of standard ANSI colors are treated as part of
            // the extended 256-color palette. They require a prefix "38;5;" which
            // signals the terminal to interpret the following number as a 256-palette index.
            colorCode = "\033[38;5;" + std::to_string(static_cast<int>(color)) + "m";
        }

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

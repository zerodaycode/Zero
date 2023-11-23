/// @file stylizer.hpp
/// Provides functions and enums for string styling.

export module stylizer;

import std;

/// @namespace zero::fmt
/// Namespace containing functions and enums for text styling.
export namespace zero::fmt {

    // ANSI escape codes for text styling
    constexpr char foreground_color_begin[] = "\033[38;5;";     ///< Start of foreground color
    constexpr char modifier_begin[] = "\033[";                  ///< Start of modifier
    constexpr char reset_code[] = "\033[0m";                    ///< Reset text styling

    /// @enum Color
    /// Enumerates ANSI color codes for text styling.
    enum class Color {
        DEFAULT,  ///< Default console color
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

    /// @enum Modifier
    /// Enumerates ANSI modifier codes for text styling.
    enum class Modifier {
        BOLD = 1,
        FAINT = 2,
        ITALIC = 3,
        UNDERLINE = 4,
        BLINK = 5,
        REVERSE = 7,
        HIDDEN = 8
    };

    /// @brief Apply text styling to a given string.
    /// @tparam Modifiers Variadic template representing text styling modifiers.
    /// @param text The input string to be stylized.
    /// @param color The foreground color.
    /// @param modifiers Variadic parameters representing text styling modifiers.
    /// @return The stylized string.
    template <typename... Modifiers>
    constexpr std::string stylize(const std::string& text,
                                  const Color color = Color::DEFAULT,
                                  const Modifiers... modifiers)
    {
        std::ostringstream result;

        // Add foreground color
        result << foreground_color_begin << static_cast<int>(color) << "m";

        // Apply modifiers
        ((result << modifier_begin << static_cast<int>(modifiers) << "m"), ...);

        // Append the text
        result << text;

        // Reset text styling
        result << reset_code;

        return result.str();
    }

}

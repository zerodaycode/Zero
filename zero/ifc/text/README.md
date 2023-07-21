# The Text library

The Text library provides common operations not present in the standard language and custom text types. It includes the following components:

## str_manip module
This module offers a function named `split_str` to split a string into multiple parts based on a specified delimiter.

## format module
This module facilitates string formatting and styling with various utilities.

- `Color` and `Modifier` enumerations: Define constants for stylizing text with different colors and styles, like bold, faint, italic, underline, etc.

- `formatter`: Formats a string by replacing placeholders with the provided arguments. This is useful in constructing dynamic strings.

- `stylize`: Applies color and style modifications to a string. For instance, you can use this to colorize your log messages for better readability.

### Examples of use:

```cpp
// Example of formatter
std::string format_str = "x = {}, y = 20, z = {}";
std::cout << zero::fmt::formatter(format_str, 10, 30) << std::endl;

// Example of stylize
std::string boldText = zero::fmt::stylize("[WARNING] This is bold text", zero::fmt::Color::YELLOW, {zero::fmt::Modifier::BOLD});
std::cout << boldText << "\n";

// Example of combining formatter and stylize
std::string format_str1 = "[WARNING] {} is deprecated. Please use {} instead.";
std::string warning_msg = zero::fmt::formatter(format_str1, "methodA", "methodB");
std::string stylized_warning_msg = zero::fmt::stylize(warning_msg, zero::fmt::Color::YELLOW, {zero::fmt::Modifier::BOLD});
std::cout << stylized_warning_msg << std::endl;
```
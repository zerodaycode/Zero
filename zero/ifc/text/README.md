# The Text library

The Text library provides common operations not present in the standard language and custom text types. It includes the following components:

## str_manip module
This module offers a function named `split_str` to split a string into multiple parts based on a specified delimiter.


## formatter module

This module provides functions for string formatting. Given a format string, it replaces placeholders with actual values.

### Example of use:

```cpp
zero::fmt::formatter("Hello, {}", "world");  // Outputs: "Hello, world"
```

## stylizer module

This module provides functions and enums for string styling. It allows for adding color and other text modifiers to strings.

### Example of use:

```cpp
zero::fmt::stylize("This is a warning", zero::fmt::Color::YELLOW, {zero::fmt::Modifier::BOLD});
```

## print_utils module

This module provides utilities to directly print formatted text to the console, abstracting away direct usage of `std::cout`.

- `print`: Formats and prints a string without a newline.
- `println`: Formats and prints a string followed by a newline.

### Examples of use:

```cpp
// Example of print
zero::fmt::print("This is a number: {}", 42);

// Example of println
zero::fmt::println("Hello, {}!", "world");
```
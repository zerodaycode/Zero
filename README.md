# The ZERO project

Zero project it's a set of powerful libraries written in modern C++ and for
modern C++ projects (C++ standard >= 20)

## Build system

We are relying on [`Zork++`](https://github.com/zerodaycode/Zork) to build our project around the
latest features of the language, including the full usage of modules on all the source files
of the codes instead of the legacy headers, due to it's fenomenal integration with this feature
under `Clang` environments.

## Testing tools

We are using [`catch2`](https://github.com/catchorg/Catch2) as the testing suite for `Zero`, in its *header-only* version.
Tests compilation under Windows is taking nearly 20 seconds.

We made a try to replace it with `boost::ut`, that spots that is compatible with modules, but
we are getting all kind of errors in the compilation process with `Clang`, so we will stay
with `catch2` for now.

Also, we are looking for generate a precompiled header of the Catch's suite in order to decrement
the tests compilation time.

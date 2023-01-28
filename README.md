# The ZERO project

Zero project it's a set of powerful libraries written in modern C++ and for
modern C++ projects

## Motivation

Zero's main ideas and motivations can be summarized in the search for a deeper understanding of the roots of C++ than usual. For this, we are approaching this project as an implementation of the standard C++ library, as established in the standards by the ISO Committee, but perhaps with some deviation or functionality not included in the standard that would be interesting. An example of this, for example, could be a Result<T, E> type like the one in Rust, to represent the result of fallible computations at runtime, but other implementations that deviate from the standard would also be welcome, as long as they have a certain consensus base and place within the ecosystem.

Another basis of the project is the use of modules. Many talks and conferences have exposed the goodness and benefits of migrating to the new model, but let's be realistic, it is unfeasible to rewrite more than 40 years of projects. What is feasible, however, is to use the modules in projects that start from scratch, like this one.

Zero was born from the idea of improving as library developers, to be able to design better public APIs and to offer content focused on maintainability, sustainability, scalability and performance, and, above all, it is a personal and professional learning project about different software engineering tools, and in search of a deeper knowledge of one of our favorite tools, C++.

## Disclaimer

This project is not a "production ready" project, far from it. Even if the written implementations are correct, solid and efficient, we just want to mix fun and knowledge, create a good development environment, and have productive talks about what exists in C++, what could have existed, its interpretations... This project is just an experiment, and as Herb Sutter would say, the default of an experiment is to fail. Maybe tomorrow we can refine our language concepts, improve the implementations (that's the root idea) adn the knowledge about the intrinsics, or adhere completely to the Standard and start being an alternative for certain projects. But that is not the initial or main goal. The goal is to create, learn and share, and for that, the more people we contribute, the better!

## Build system

We are relying on [`Zork++`](https://github.com/zerodaycode/Zork) to build our project around the
latest features of the language, including the full usage of modules on all the source files
of the codes instead of the legacy headers, due to it's fenomenal integration with this feature
under `Clang` environments.

## Testing tools

We are using [`catch2`](https://github.com/catchorg/Catch2) as the testing suite for `Zero`, in its *header-only* version.

We made a try to replace it with `boost::ut`, that spots that is compatible with modules, but we are getting all kind of errors in the process of convert the provided header to a precompiled module, so we will stay
with `catch2` for now.

Also, we are looking for generate a precompiled header of the Catch's suite in order to decrement
the tests compilation time.

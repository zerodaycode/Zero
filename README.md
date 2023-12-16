# The ZERO project

Zero project it's a set of powerful libraries written in modern C++ and for
modern C++ projects

## Libraries

Quick description, and links to the documentation of all the libraries of the project

- [Physics](./zero/ifc/physics/README.md) - A general purpose library for dealing with field related aspects and problems of physics
  - [Quantities](./zero/ifc/physics/quantities) - Compile time library for work with physical quantities acording the `SI`
- [Collections](./zero/ifc/collections/README.md) - Custom containers, operations and interfaces
- [Iterators](./zero/ifc/iterators/README.md) - Custom iterator interfaces, and some legacy implementation (just as examples) of the legacy ones
- [Text](./zero/ifc/text/README.md) - Offers utilities for text manipulation, string splitting, formatting, styling, and print to console functionalities.
- [Types](./zero/ifc/types/README.md) - Information about types and traits for types
- [Math](./zero/ifc/math/README.md) - Mathematical operations and functions
- [Test Suite](./zero/ifc/test-suite/README.md)  - A flexible and simple test-suite.

## Sponsorship

<img src="https://resources.jetbrains.com/storage/products/company/brand/logos/jb_beam.svg" width="100" />
This project has been supported directly by JetBrains, giving us free access to all of their amazing products.
You guys rocks, thanks! 

## Motivation

Zero's main ideas and motivations can be summarized in the search for a deeper understanding of the roots of C++ than usual. For that,
we are aim to implement library functionalities that we are missing in the language, or that we would like to know how they must be build
from scratch.
One way of understand this felling, is thanks to Jason Turner, and it's incredible [C++ Weekly](https://www.youtube.com/playlist?list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1) YouTube
channel. In particular, you can checkout [this particular episode](https://youtu.be/287_oG4CNMc?list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1&t=378) and immediately
you understand our feeling!

Also, we like to create and share new libraries that are part of our way to see the world. For example, the physics
library born as an idea of "what if we could code the Physics degree?" From the roots, by starting with units and system
of measurements, until complex equation systems, matrix and problems solver...! As well as a new math library.
We are well aware that already exists maths libraries. But this idea is, learn the degree by... coding it!

Another basis of the project is the use of modules. Many talks and conferences have exposed the goodness and benefits of migrating
to the new model, but let's be realistic, it is unfeasible to rewrite more than 40 years of projects.
What is feasible, however, is to use the modules in projects that start from scratch, like this one.

Zero was born from the idea of improving as library developers, to be able to design better public APIs and to offer content focused on maintainability, sustainability, scalability and performance, and, above all, it is a personal and professional learning project about different software engineering tools, and in search of a deeper knowledge of one of our favorite tools, C++.

## Build system

The last but not least, is using `Zero` as a platform for showing our [`Zork++`](https://github.com/zerodaycode/Zork) build
system in a real world environment, so people can profit by taking examples of how we set-up things with `Zork++`
in a big scale project. Also, we introduce the changes of the latest releases available here, so it serves as well as
a kind of latest up-to-date guide.

## General guidelines and API design

This entry is a collection of both the things that we're looking for, or focusing on
in the design of our code, or how we with that design, decide to implement the user's
API.

### Design APIs to make it able to be processed at compile-time

We all know the marvelous `constexpr` C++ keyword. This is, compute the things that you can at
compile-time if you are able to do so. `C++20` brings us other alternatives, like `consteval`, which
means work only if you're able to do your computations at compile-time, or `Concepts`, that are template
constraints for types.

Process your data at compile-time has a lot of incredible benefits. It provides faster runtime
applications, since the job is already done. But, our favourite thing by far, is that working with this
kind of code make us able to spot any kind of users code errors when the code is being compiled, instead
of having to produce a failure when their program is running.

Let's take, for example, the `std::get<>()` template. This function takes a template parameter that
must be an index or a type, to retrieve an element from a generic collection. Let's say that you have
and `std::array<int, 3>`, and you want to get the fifth element. As you may be spotted, there's no such
fifth element, since the array only contains 4 elements! If you tried to retrieve the element with the
*index subscript operator*, for example `my_array[5]`, you will go directly towards *undefined behaviour*.
You will be accessing a memory address outside the arrays range, bring if you thrash data if you're lucky
enough, because all kind of bad things could have happen.

So, most of the time, you will face our APIs, that will be asking you for certain template parameters
that maybe you weren't expecting. But this has a powerful reason, we are able to provide you an API
that is non-throwable, or doesn't lead you to write code that creates *undefined behaviour*.
And sometimes, you'll find mixed behaviour. Take in consideration our `Matrix` type, from the
linear-algebra library.

```c++
Matrix m {
    std::array{3, 5, 8},
    std::array{4, 7, 9},
    std::array{9, 1, 15}
};
assertEquals(m[0][0] == 3);
```

The `Matrix` type has a constructor based on an `std::initializer_list`. This means that you're able
to don't have to write the outter array, and just declare the arrays that holds the real matrix data.
But that's not the point. The point is the template argument deduction. You instantiated a new matrix,
which is a template class. The template class has two non template parameters, the two first, to specify
the number of rows and columns that your matrix has, and the third, which is a template parameter for
indicate the type of the data that will be holding. This means that the parameters deduced will
be, for the example above, `3, 3, int`. This means that, when you want to make a matrix multiplication
operation with a 3 by 5 matrix, we may check and ensure that the multiplication operation is defined,
because the first matrix matches the same number of columns that the second matrix number of rows, so
we can multiply them (otherwise, the multiplication operation isn't defined between the first and the second.)

But the neat thing is that we can check this at compile time! If you try to multiply two 2 by 3 matrices,
you'll see a compile time error, and you can fix it in your codebase, non when the program is running.
This is a huge advantage that compile-time programming provides, and we'll try to focus on it make it present
in all of our APIs whenever is possible.

We can take also the example of how we provide an API to get an element from the matrix.
```c++
Matrix<3, 3, int> m {
    std::array{3, 5, 8},
    std::array{4, 7, 9},
    std::array{9, 1, 15}
};

// Using the fluent builder API to access elements
int element = m.row<0>().column<0>(); // Retrieves the element at row 0, column 0 (value: 3)
```

The row and column methods are templated, allowing you to specify the row or column index at compile time.
If the provided index is out of range, you will get a compile-time error, ensuring that users are accessing valid
elements of the matrix.

This fluent builder API improves the safety and usability of the matrix class, providing compile-time checks and
eliminating the possibility of runtime failures when accessing elements.

But, in this particular case, we are also providing for this API the typical subscript operator `[]`.
Even we already discussed the benefits of using non failable runtime APIs, not always must be convenient
to use those one (specially, when prototyping). We prefer to maintain a neutral position most of the time,
where as library designers we just offer both approaches, and its ultimately the developer which decides
what option fits the best in their codebase.

### Prefer to work with value APIs vs reference/pointers APIs

// TODO

### Avoid returning raw pointers from functions

// TODO

### Make the public APIs exception-free

We largely hate the APIs that throws exceptions to the client code. Throw exceptions
is typically used in the industry as a way to propagate all kind of errors, and that's
shouldn't be the way of how exceptions must be used. The word exception already has a strong
meaning, that, for us, is *something exceptionally bad happened in the runtime of your program*,
and you must take care of it.
Exceptions has a high runtime cost, user's must be aware that a certain API is throwable, and then handle properly.
At the time of writing, already exists modern alternatives for deal with errors that mustn't be considered
as any kind of exception, like `std::optional` and *C++23* `std::expected`, so they will be present
in our codebase as the major guideline to follow when we are working and providing a fallible API.

### Avoid non initialized code

Let's be clear. Non initialized code is ugly, dark and error prone. Also, it has the major drawback that
if code isn't managed properly, developers can fall into the classical error of work with non initialized
data, that will lead them towards *undefined behaviour*.

Modern languages are going towards code workflows that avoids non initialized data, or probably are forbidden already
in the language. Sure that there's situations where you may need to wait for user input, maybe working with streams,
or another kind of "justified" situation, but in general non initialized code must be avoided whenever is possible.

To help with this situation, you'll see that most of our types has deleted its default constructor, thing
that must force the users to better design their code workflows, but in the end, creating a more robust
and less error prone codebases.

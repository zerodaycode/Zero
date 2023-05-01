# The ZERO project

Zero project it's a set of powerful libraries written in modern C++ and for
modern C++ projects

## Libraries

Quick description, and links to the documentation of all the libraries of the project

- [Physics](./zero/ifc/physics/README.md) - A general purpose library for dealing with field related aspects and problems of physics
  - [Quantities](./zero/ifc/physics/quantities) - Compile time library for work with physical quantities acording the `SI`
- [Collections](./zero/ifc/collections/README.md) - Custom containers, operations and interfaces
- [Iterators](./zero/ifc/iterators/README.md) - Custom iterator interfaces, and some legacy implementation (just as examples) of the legacy ones
- [Text](./zero/ifc/text/README.md) - Character types and manipulation operations on them
- [Types](./zero/ifc/types/README.md) - Information about types and traits for types
- [Math](./zero/ifc/math/README.md) - Mathematical operations and functions
## Sponsorship

<img src="https://resources.jetbrains.com/storage/products/company/brand/logos/jb_beam.svg" width="100" />
This project has been supported directly by JetBrains, giving us free access to all of their amazing products.
You guys rocks, thanks! 

## Motivation

Zero's main ideas and motivations can be summarized in the search for a deeper understanding of the roots of C++ than usual. For that,
we are aim to implement library functionalities that we are missing in the language, or that we would like to know how they must be build
from scratch.
One way of understand this felling, is thanks to Jason Turner, and it's incredible [C++Weekly](https://www.youtube.com/playlist?list=PLs3KjaCtOwSZ2tbuV1hx8Xz-rFZTan2J1) YouTube
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

## Testing tools

We are using [`catch2`](https://github.com/catchorg/Catch2) as the testing suite for `Zero`, in its *header-only* version.

We made a try to replace it with `boost::ut`, that spots that is compatible with modules, but we are getting all kind of errors in the process of convert the provided header to a precompiled module, so we will stay
with `catch2` for now.

Also, we are looking for generate a precompiled header of the Catch's suite in order to decrement
the tests compilation time.

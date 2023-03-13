#pragma clang diagnostic ignored "-Wc++17-extensions"

/**
* Contains the type definitions for the physical quantities
* defined in the `Physics` library
*/

export module physics:magnitudes.symbols;

export namespace zero::physics {
    template<typename T>
    struct unit_symbol {
        using symbol = T;
    };

    template<typename T>
    concept Symbol = requires {
        typename T::symbol;
    };

    // TODO a submodule for every symbol?

    /** Definitions of symbols */
    struct kg: unit_symbol<kg> {};
    struct hg: unit_symbol<hg> {};
    struct m: unit_symbol<m> {};
}
/**
* Contains the type definitions for the symbols that represents a physical quantity
*/

export module physics.quantities:units.symbols;

export namespace zero::physics {
    template<typename T>
    struct unit_symbol {
        using symbol = T;
    };

    template<typename T>
    concept Symbol = requires {
        typename T::symbol;
    };

    /** Definitions of symbols */
    struct kg: unit_symbol<kg> {};
    struct hg: unit_symbol<hg> {};
    struct km: unit_symbol<km> {};
    struct m: unit_symbol<m> {};
    struct h: unit_symbol<h> {};
    struct s: unit_symbol<s> {};
}

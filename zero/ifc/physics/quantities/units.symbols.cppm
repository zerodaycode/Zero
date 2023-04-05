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

    /* ------------------------- Symbols for Units ------------------------- */

    /* ----- Symbols for represent dimensionless units ----- */
    struct unit_type: unit_symbol<unit_type> {};

    /* ----- Symbols related with the dimension of Mass ----- */
    struct kg: unit_symbol<kg> {};
    struct hg: unit_symbol<hg> {};
    struct dag: unit_symbol<dag> {};
    struct g: unit_symbol<g> {};
    struct dg: unit_symbol<dg> {};
    struct cg: unit_symbol<cg> {};
    struct mg: unit_symbol<mg> {};
    struct ng: unit_symbol<ng> {};
    struct pg: unit_symbol<pg> {};

    /* ----- Symbols related with the dimension of Length ----- */
    struct km: unit_symbol<km> {};
    struct hm: unit_symbol<hm> {};
    struct dam: unit_symbol<dam> {};
    struct m: unit_symbol<m> {};
    struct dm: unit_symbol<dm> {};
    struct cm: unit_symbol<cm> {};
    struct mm: unit_symbol<mm> {};

    /* ----- Symbols related with the dimension of Length ----- */
    struct d: unit_symbol<d> {};
    struct h: unit_symbol<h> {};
    struct min: unit_symbol<min> {};
    struct s: unit_symbol<s> {};
    struct ms: unit_symbol<ms> {};

    /* ----- Symbols related with the dimension of Length ----- */
    struct A: unit_symbol<A> {};
}

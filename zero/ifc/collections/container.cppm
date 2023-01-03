/**
 * @brief An interface for exposing the public API of the collections of the library
 * as templated CRTP hierarchy, including concepts as constraints of part of the
 * public API as well
 */

export module container;

export namespace zero {
    /**
     * @brief Base interface for the hierarchy of collections
     */
    template <
        typename Child, // TODO Interface the types to repr valid containers
        // So we can get rid of the declaration (neither impl) of the methods
        // in the base class
        typename Iter
        // typename ConstIter 
    >
    class Container {
        public:
            Iter begin() { return static_cast<Child*>(this)->begin(); }
            Iter end() { return static_cast<Child*>(this)->end(); }
            Iter begin() const { return static_cast<const Child*>(this)->begin(); }
            Iter end() const { return static_cast<const Child*>(this)->end(); }
    };
}
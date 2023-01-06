/**
 * @brief An interface for exposing the public API of the collections of the library
 * as templated CRTP hierarchy, including concepts as constraints of part of the
 * public API as well
 */

export module container;
import std;
import type_info;

export namespace zero {
    /**
     * @brief Base interface for the hierarchy of collections
     */
    template <class Child>
    class Container {
        private:
            /**
             * @brief When N classes happen to derive from the same CRTP base class,
             * we likely get to undefined behaviour when the CRTP will try to use the
             * wrong class. That's why we are declaring the friend Child from the template
             * parameter and a defaul-constructor. Since the constructor in the base class
             * is private, no one can access it except the friend classes.
             * And the only friend class is the template class
             */
            friend Child;
            constexpr Container() {};
        public:
            decltype(auto) begin() { return static_cast<Child&>(*this).abegin(); }
            decltype(auto) end() { return static_cast<Child&>(*this).aend(); }
            decltype(auto) begin() const { return static_cast<const Child&>(*this).abegin(); }
            decltype(auto) end() const { return static_cast<const Child&>(*this).aend(); }
    };
}
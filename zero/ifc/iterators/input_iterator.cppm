export module iterator:input_iterator;

import :iterator_facade;

export namespace zero::iterator {
    /**
     * @brief A generic implementation of an input iterator based on
     * compile time polimorphism thanks to the {@link iterator_facade}
     * using CRTP 
     * 
     * @details An input iterator implements the three minimum required
     * APIs for a type to be an iterator
     */
    template <typename T>
    class input_iter: public iterator_facade<input_iter<T>> {
        private:
            T* _ptr;

        const input_iter& dereference() const {
            return _ptr;
        }

        void increment() {
            _ptr = input_iter(++_ptr);
        }

        bool equals_to(input_iter o) const {
            return _ptr == o._ptr;
        }
    };
}
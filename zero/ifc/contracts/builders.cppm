export module builders;

export namespace zero::contracts::builders {
    
    /**
     * @brief provides an interface class for construct
     * any concrete builder
     * 
     * Any concrete builder in Zero will implement this interface,
     * so they all must provide an implementation for gthe build()
     * method, which is the ultimate responsable for generate
     * the implementor instance.
     */
    template <class T>
    class Builder {
        protected:
            // Virtual destructor
            virtual ~Builder(){}
            // Builds a concrete instance of the implementor
            virtual T build() const = 0;
    };
}
export module testing.core;

export namespace zero::testing::core {

    class TestSuite {
        public:
            static constexpr const char* var [] = { "Hi, constexpr!" };
    };

    void say_hello();
}
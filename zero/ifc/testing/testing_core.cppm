export module testing.core;

export import builders;

import <vector>;
import <string>;
import <functional>;
    
export namespace zero::testing::core {

    template <class T>
    class TestBuilder : zero::contracts::builders::Builder<T> {
        private:
            // A collection of tests as function pointers or functors
            // (TODO: make it for only a T type)
            std::vector<std::function<void()>> tests {};
            // Disallow the copy constructor
            TestBuilder(TestBuilder& test_builder) = delete;

        public:
            // Base constructor
            TestBuilder(T instance);
            // Virtual destructor
            virtual ~TestBuilder() {};
            // Add a new test to the collection of tests for the T instance
            // of the test_class_instance
            template<typename Function>
            void add(Function&& fn) {  
                tests.push_back(std::forward<Function>(fn)); 
            }
            // override the build() base method from Builder<T>
            virtual const std::vector<std::function<void ()>> build() const override {
                return this->tests;
            }
    };

    // template<class T>
    class TestSuite {
        private:
            // A collection of tests as function pointers or functors
            // (TODO: make it for only a T type)
            std::vector<std::function<void()>> tests;
            // Disallow the copy constructor
            TestSuite(TestSuite& test_suite) = delete;

        public:
            // Base constructor
            TestSuite() : tests {} {};
            // Destructor
            ~TestSuite() = default;

            template<typename Function>
            void add_test(Function&& fn) {  
                tests.push_back(std::forward<Function>(fn)); 
            }
            
            void run_tests() {
                for (auto test : this->tests)
                    test();
            }
    };
}
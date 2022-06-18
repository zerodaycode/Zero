// import testing;
// import zero;
import testing.core;
import <iostream>;
import <string>;

using namespace zero;

// Mock class for test the process of making a Zero::Test
class MockedClass : Test {
    public:
        void operator()() {
            std::cout << "Functor called" << std::endl;
        }
};

int main() {
    using namespace zero::testing::core;

    TestSuite testSuite;
    testSuite.add_test(MockedClass());
    testSuite.run_tests();
    
    return 0;
}
    
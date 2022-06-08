// import testing;
// import zero;
import testing.core;
import <iostream>;
import <string>;

using namespace zero;

// Mock class for test the process of making a Zero::Test
class MockedClass {
    public:
        std::string return_hi() const {
            return std::string {"Hi!"};
        }

        int return_num() const {
            return 10;
        }
};

int main() {

    // Prints the return values of the declared methods of the MockedClass
    MockedClass mc;
    std::cout << mc.return_hi() << std::endl;
    std::cout << mc.return_num() << std::endl;

    // Generate a new TestBuilder
    // testing::core::TestBuilder itce = 
    //     testing::core::TestBuilder<MockedClass> {mc};
    using namespace zero::testing::core;
    TestSuite testSuite = TestSuite {};
    return 0;
}
    
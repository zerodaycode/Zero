// import testing;
// import zero;
import testing.core;
import <iostream>;

using namespace zero;

int main() {
    testing::core::say_hello();

    // Prints const char* first element memory address
    std::cout << testing::core::TestSuite::var << std::endl;
    // Prints the deferenced value of the const char* constexpr
    std::cout << *testing::core::TestSuite::var << std::endl;

    return 0;
}
    
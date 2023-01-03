import std;
import zero;
import collections;
// import container;

using namespace zero;

int main() {
    // TODO Now that the Testing Suite is integrated into the project,
    // this file should dissapear. Only stays here until a way to #include
    // headers // BUG (Only on WIN32) in a main file when importing modules that already uses
    // imports are found
    // constexpr collections::Array a = collections::Array<long, 5>{1L, 2L, 3L};
    // auto b = new decltype(collections::Array<int, 5>{1, 2, 3, 4, 5})[0];
    collections::Array c = collections::Array<long, 5>{1L, 2L, 3L, 4L, 5L};

    std::cout << "Before" << std::endl;
    std::cout << "[0]: " << c.get<0>() << std::endl;
    std::cout << "[&0]: " << &c.array[0] << std::endl;
    std::cout << "[5]: " << c.get<4>() << std::endl;
    std::cout << "[&5]: " << &c.array[6] << std::endl;
    std::cout << "[begin()]: " << *(c.begin()) << std::endl;
    std::cout << "[end()]: " << *(c.end()) << std::endl;
    auto it = c.begin(); 
    for (auto i = 0; i < 4; i++) {
        std::cout << "idx: " << i << " - Value: " << *it << std::endl;
        ++it;
    }

    for (long value : c)
        std::cout << "RANGE Value: " << value  << std::endl;

    return 0;
}

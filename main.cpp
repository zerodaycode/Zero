import std;
import zero;
import collections;
import iterator;
// import container;

using namespace zero;

int main() {
    collections::Array a = collections::Array<long, 5>{1L, 2L, 3L, 4L, 5L};
    constexpr collections::Array b = collections::Array<long, 5>{1L, 2L, 3L, 4L, 5L};

    std::cout << "Iterating over the values of a zero::collection!" << std::endl;
    for (long value : a)
        std::cout << " - [constexpr] Value: " << value << std::endl;

    std::cout << "Iterating over the values of a constexpr zero::collection!" << std::endl;
    for (long value : b)
        std::cout << " - [constexpr] Value: " << value << std::endl;

    return 0;
}

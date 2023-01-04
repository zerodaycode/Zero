import std;
import zero;
import collections;
import iterator;
// import container;

using namespace zero;

int main() {
    collections::Array c = collections::Array<long, 5>{1L, 2L, 3L, 4L, 5L};

    std::cout << "Iterating over the values of a zero::collection!" << std::endl;
    for (long value : c)
        std::cout << " - Value: " << value << std::endl;

    return 0;
}

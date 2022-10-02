import zero;

import <iostream>;

using namespace zero;

int main() {
    // Testing the collections
    std::cout << collections_miu_greet() << std::endl;
    
    decltype(auto) a = collections::StackArray<int, 5>{1, 2, 3, 4, 5};

    // .get(6) will throw out-of-bounds, and should be caught
    std::cout << "Getting an element: " << a.get(6) << std::endl;
    std::cout << "Getting an element 2: " << a.get(2) << std::endl; // Ok

    return 0;
}
    
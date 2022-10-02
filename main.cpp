import zero;

import <iostream>;

using namespace zero;

int main() {
    // Testing the collections
    std::cout << collections_miu_greet() << std::endl;
    
    auto a = collections::Array<int, 5>{1, 2, 3, 4, 5};

    return 0;
}
    
import zero;

import <iostream>;
import <optional>;


using namespace zero;

int main() {
    // Testing the collections
    std::cout << collections_miu_greet() << std::endl;
    
    decltype(auto) a = collections::StackArray<int, 5>(1, 2, 3);
    auto b = new decltype(collections::StackArray<int, 5>{1, 2, 3, 4, 5})[0];

    // .get(6) terminating with uncaught exception oftype std::bad_optional_access: bad_optional_access
    std::cout << "Getting an element: " << a.get(6).value_or(-1) << std::endl;
    std::cout << "Getting an element 2: " << a.get(2).value() << std::endl;

    // mutating the content of index 3
    a.mut_ref_at(3) = 10;
    // static_assert(a.get(3) == 10);
    std::cout << a.get(3).value() << std::endl;

    return 0;
}
    
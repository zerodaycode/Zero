import zero;

#ifdef _WIN32
    #include <iostream>
    #include <optional>
#else
    import <iostream>;
    import <optional>;
#endif

using namespace zero;

int main() {
    // Testing the collections
    std::cout << collections_miu_greet() << std::endl;
    
    constexpr collections::Array a = collections::Array<int, 10>(1, 2, 3);
    // auto b = new decltype(collections::StackArray<int, 5>{1, 2, 3, 4, 5})[0];

    // .get(6) terminating with uncaught exception oftype std::bad_optional_access: bad_optional_access
    std::cout << "Getting an element: " << a.get_or_nullopt(6).value_or(-1) << std::endl;
    std::cout << "Getting an element 2: " << a.get_or_nullopt(2).value() << std::endl;

    // mutating the content of index 3
    // a.mut_ref_at<3>() = 10;
    std::cout << a.get<3>() << std::endl;

    // cout a const ref to an element
    std::cout << a.const_ref_at<2>() << std::endl;
    // a.const_ref_at<5>() = 15;
    std::cout << a.get_or_nullopt(5).value() << std::endl;
    return 0;
}
    
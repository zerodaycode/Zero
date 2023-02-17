import std;
import zero;
import collections;
import iterator;
import container;
import type_info;

// using namespace zero;

int main() {
    // constexpr auto a = collections::Array<long, 5>{1L, 2L, 3L, 4L, 5L};
    // const Container<collections::Array<long, 5>>& b = collections::Array<long, 5>{1L, 2L, 3L, 4L, 5L};
    // Container<collections::Array<long, 5>>* c = new collections::Array<long, 5>{1L, 2L, 3L, 4L, 5L};

    // std::cout << "Iterating over the values of a constexpr zero::collection!" << std::endl;
    // std::cout << "decltype a: " << zero::types::type_name<decltype(a)>() << std::endl;
    // for (long value : a)
    //     std::cout << " - [constexpr] Value: " << value << std::endl;

    // std::cout << "Iterating over the values of a zero::container!" << std::endl;
    // std::cout << "decltype b: " << zero::types::type_name<decltype(b)>() << std::endl;
    // for (long value : b)
    //     std::cout << " - [const Container<T>&] Value: " << value << std::endl;

    // std::cout << "Iterating over the values of a zero::container dynamically allocated!" << std::endl;
    // std::cout << "decltype c: " << zero::types::type_name<decltype(c)>() << std::endl;
    // for (long value : *c)
    //     std::cout << " - [const Container<T>*] Value: " << value << std::endl;

    std::ostream_iterator<int> os_iter(std::cout, "from ostream: ");
    // my_os_iter = 10;
    // ++my_os_iter;
    // my_os_iter = 20;
    // ++my_os_iter;
    // my_os_iter = 30;
    // ++my_os_iter;
    std::vector<int> v { 1, 2, 3, 4, 5 };
    zero::iterator::legacy::output_iter<int> my_os_iter(std::cout);

    std::copy(v.begin(), v.end(), my_os_iter);
    // std::cout << "Reading from the output iterator: " << *my_os_iter << std::endl;

    // std::vector<int> my_vec;
    // zero::iterator::legacy::output_iter<std::vector<int>> my_vec_iter(&my_vec);
    // my_vec_iter = 10;
    // my_vec_iter = 20;
    // my_vec_iter = 30;

    // for (auto elem : my_vec) {
    //     std::cout << elem << " ";
    // }
    // std::cout << std::endl;

    return 0;
}

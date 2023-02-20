import std;
// import zero;
// import collections;
// import iterator;
// import container;
// import type_info;
import physics;

using namespace zero::physics;

// Forward decls
// void run_containers_examples();
// void run_output_iterator_examples();

int main() {
    // run_containers_examples();
    // run_output_iterator_examples();

    // Physics
    // unit_simbol us;
    // kg k;

    // static_assert(1_kg == 1_kg);

    // base_unit kilogram { "Kilogram", 0, k };


    // Creating quantities using different units within the gram family
    // kilogram<double> kg{1.0};
    // gram<double> g{1000.0};
    // decagram<double> dag{0.1};
    // hectogram<double> hg{0.01};
    
    // // Adding quantities with different units
    // auto total = kg + g + dag + hg;
    
    // // Multiplying a quantity by a scalar
    // auto double_total = total * 2.0;
    
    // // Outputting the total amount
    // std::cout << double_total.amount << std::endl;

    mass<double> m1{1.0};
    mass<double> m2{2.0};
    // auto m3 = m1 + m2;
    // length<double> l1{1.0};
    // length<double> l2{2.0};
    // auto l3 = l1 + l2;
    // zero::physics::time<double> t1{1.0};
    // zero::physics::time<double> t2{2.0};
    // auto t3 = t1 + t2;
    // return 0;
    return 0;
}

/*
void run_containers_examples() {
    constexpr auto a = collections::Array<long, 5>{1L, 2L, 3L, 4L, 5L};
    const Container<collections::Array<long, 5>>& b = collections::Array<long, 5>{1L, 2L, 3L, 4L, 5L};
    Container<collections::Array<long, 5>>* c = new collections::Array<long, 5>{1L, 2L, 3L, 4L, 5L};

    std::cout << "Iterating over the values of a constexpr zero::collection!" << std::endl;
    std::cout << "decltype a: " << zero::types::type_name<decltype(a)>() << std::endl;
    for (long value : a)
        std::cout << " - [constexpr] Value: " << value << std::endl;

    std::cout << "Iterating over the values of a zero::container!" << std::endl;
    std::cout << "decltype b: " << zero::types::type_name<decltype(b)>() << std::endl;
    for (long value : b)
        std::cout << " - [const Container<T>&] Value: " << value << std::endl;

    std::cout << "Iterating over the values of a zero::container dynamically allocated!" << std::endl;
    std::cout << "decltype c: " << zero::types::type_name<decltype(c)>() << std::endl;
    for (long value : *c)
        std::cout << " - [const Container<T>*] Value: " << value << std::endl;
}

void run_output_iterator_examples() {
    std::cout << "Using output iterator with ostream: ";
    zero::iterator::legacy::output_iter<std::ostream> out1(std::cout);
    out1 = 1;
    out1 = " hello";
    out1 = 3.14;
    std::cout << std::endl;

    std::cout << "Using output iterator with vector: ";
    std::vector<int> vec;
    zero::iterator::legacy::output_iter<decltype(vec)> out2(vec);
    out2 = 1;
    out2 = 2;
    out2 = 3;
    for (auto i : vec) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::vector<int> v{ 7, 8, 9, 10, 11 };
    std::vector<int> result;
    zero::iterator::legacy::output_iter<decltype(v)> my_vec_iter(result);
    std::copy(v.begin(), v.end(), my_vec_iter);
    for (const auto& value : result) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    zero::iterator::legacy::output_iter<std::ostream> output_iter(std::cout);
    output_iter = 42;
    output_iter = "hello";
    output_iter = 3.14;

    std::ostringstream oss;
    zero::iterator::legacy::output_iter<decltype(oss)> oss_output_iter(oss);
    oss_output_iter = 46;
    oss_output_iter = "hellofghjfghjfgh";
    oss_output_iter = 3.1425465463456;
    std::cout << "What do we have here: " << oss.str() << std::endl;

    std::ofstream ofs("output.txt");
    zero::iterator::legacy::output_iter<decltype(ofs)> ofs_output_iter(ofs);
    ofs_output_iter = 42;
    ofs_output_iter = "hello";
    ofs_output_iter = 3.14;

    std::list<int> my_list = {1, 2, 3, 4, 5};
    zero::iterator::legacy::output_iter<std::list<int>> out_it(my_list);
    for (int i = 0; i < 5; ++i)
        *out_it = 7;

    for (const auto& x : my_list)
        std::cout << x << ' ';

    std::cout << '\n';
}
*/
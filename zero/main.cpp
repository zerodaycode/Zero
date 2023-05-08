import std;
import zero;
import collections;
import iterator;
import container;
import type_info;
import physics;
import math;


// Forward decls
void run_containers_examples();
void run_output_iterator_examples();
void run_quantities_examples();

int main() {
    // run_containers_examples();
    // run_output_iterator_examples();
    run_quantities_examples();

    std::cout.precision(15);

    // Math
    const int a = 16;
    const int b = 20;
    const int c = 30;

    std::cout << "\nGCD of " << a << " and " << b << " is: " << zero::math::gcd(a, b) << "\n";
    std::cout << "GCD of " << a << ", " << b << " and " << c << " is: " << zero::math::gcd(a, b, c) << "\n";

    std::cout << "\nLCM of 2, 3, 4 and 5 is: " << zero::math::lcm(2, 3, 4, 5) << "\n";
    std::cout << "LCM of 10, 15 and 25 is: " << zero::math::lcm(10, 15, 25) << "\n";
    std::cout << "LCM of 8 and 6 is: " << zero::math::lcm(8, 6) << "\n";

    std::cout << "\nAddition of two integers: " << zero::math::add(7, 3) << "\n";
//    std::cout << "Addition of two integer l-value references: " << zero::math::add(&a, &b) << "\n";
    std::cout << "Subtraction of two integers: " << zero::math::minus(7, 3) << "\n";
    std::cout << "Subtraction of two integer l-value references: " << zero::math::minus(&a, &b) << "\n\n";

    return 0;
}


void run_containers_examples() {
    using namespace zero;

    constexpr auto a = collections::Array<long, 5>{1L, 2L, 3L, 4L, 5L};
    const Container<collections::Array<long, 5>>& b = collections::Array<long, 5>{1L, 2L, 3L, 4L, 5L};
    Container<collections::Array<long, 5>>* c = new collections::Array<long, 5>{1L, 2L, 3L, 4L, 5L};

    std::cout << "Iterating over the values of a constexpr zero::collection!" << std::endl;
    std::cout << "decltype a: " << types::type_name<decltype(a)>() << std::endl;
    for (long value : a)
        std::cout << " - [constexpr] Value: " << value << std::endl;

    std::cout << "Iterating over the values of a zero::container!" << std::endl;
    std::cout << "decltype b: " << types::type_name<decltype(b)>() << std::endl;
    for (long value : b)
        std::cout << " - [const Container<T>&] Value: " << value << std::endl;

    std::cout << "Iterating over the values of a zero::container dynamically allocated!" << std::endl;
    std::cout << "decltype c: " << types::type_name<decltype(c)>() << std::endl;
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

void run_quantities_examples() {
    using namespace zero::physics;
    // Physics
    constexpr auto q1 = quantity<Kilogram, double>{9};
    constexpr auto q2 = quantity<Hectogram>{7.2};
    std::cout << "\nMasses addition [m/s + m/s]: " << q1 + q2 << "\n";

    constexpr auto kgms = quantity<Kilogram>{1.};
    constexpr auto hgs = quantity<Hectogram>{10.};
    std::cout << "  - Converting kilograms to hectograms: " << kgms.to<Hectogram>() << "\n";
    std::cout << "  - Converting hectograms to Kilograms: " << hgs.to<Kilogram>() << "\n";

    constexpr auto velocity = quantity<MetersPerSecond> {300'000.};
    constexpr auto velocity2 = quantity<KilometersPerHour> {200.};

    std::cout << "  - Velocities addition  [m/s + km/h]: " << velocity +  velocity2 << "\n";
    std::cout << "  - Velocities subtraction  [km/h - m/s]: " << velocity2 - velocity << "\n";
    std::cout << "  - Velocities multiplication  [m/s * km/h]: " << velocity * velocity2 << "\n";
    std::cout << "  - Velocities division  [m/s / km/h]: " << velocity / velocity2 << "\n";

    constexpr quantity<KilometersPerHour> kmph = velocity.to<KilometersPerHour>();
    constexpr quantity<MetersPerSecond> mps = kmph.to<MetersPerSecond>();
    std::cout << "  - Converting meters per second to kilometers per hour: " << kmph << "\n";
    std::cout << "  - Converting kilometers per hour to meters per second: " << mps << "\n";

    std::cout << "\nShowing some predefined derived magnitudes:\n";
    std::cout << "  - Frequency in Hertz: " << quantity<Hertz>{3} << "\n";
    std::cout << "  - Force in Newtons: " << quantity<Newton>{10} << "\n";
    std::cout << "  - Energy in Joules: " << quantity<Joule>{100} << "\n";
    std::cout << "  - Power in Watts: " << quantity<Watt>{5000} << "\n";
    std::cout << "  - Electric Charge in Coulombs: " << quantity<Coulomb>{5000} << "\n";
    std::cout << "  - Voltage in Volts: " << quantity<Volt>{240} << "\n\n";

    std::cout << "Messing with time:\n";

    constexpr auto secs_per_day = quantity<Second>{86400};
    constexpr auto mins_per_day = quantity<Minute>{1440};
    constexpr auto hours_24 = quantity<Hour>{24};
    constexpr auto one_day = quantity<Day>{1};

    std::cout << "  - Converting 86400 seconds to days: " << secs_per_day.to<Day>() << "\n";
    std::cout << "  - Converting 1440 min to days: " << mins_per_day.to<Day>() << "\n";
    std::cout << "  - Converting 24 hours to days: " << hours_24.to<Day>() << "\n";
    std::cout << "  - Converting one day to hours: " << one_day.to<Hour>() << "\n";
    std::cout << "  - Converting one day to seconds: " << one_day.to<Second>() << "\n";
    std::cout << "  - Converting one day to minutes: " << one_day.to<Minute>() << "\n";
}
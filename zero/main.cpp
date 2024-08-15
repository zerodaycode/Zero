import std;
import zero;
import collections;
import iterator;
import container;
import type_info;
import physics;
import math;
import stylizer;
import formatter;
import print_utils;
import tsuite;

// Forward decls
void run_containers_examples();
void run_output_iterator_examples();
void run_quantities_examples();
void run_formatter_and_stylize_examples();
void run_print_examples();

// Let's define some example test functions using the assertion function
void testAddition() {
    int result = 2 + 2;
    assertEquals(4, result);
    assertEquals(4, result);
    assertEquals(4, result);
}

// Let's define some more example test functions using the assertion function
void testSubtraction() {
    int result = 3 - 2;
    assertEquals(1, result);
    assertEquals(23, result);
    assertEquals(1, result);
}


// Let's define even more example test functions using the assertion function
void testMultiplication() {
    int result = 2 * 2;
    assertEquals(4, result);
    assertEquals(4, result);
    assertEquals(4, result);
}


// Passing two pointers to compare if the values that they point to are equals
void testPtrsAddition() {
    int result = 2 + 2;
    int expected = 4;
    int wrongExpected = 16;
    assertEquals(&expected, &result);
    assertEquals(&wrongExpected, &result);
}

// Driver code
int main() {
    // run_containers_examples();
    // run_output_iterator_examples();
    // run_quantities_examples();
    // run_formatter_and_stylize_examples();
    // run_print_examples();

    TEST_CASE("Multiplication Test", []() {
        int result = 5 * 3;
        assertEquals(15, result);
        assertEquals(15, result);
    });


    // Register a new test case using a function pointer.
    // Comment this line if you don't want failed tests in the freetests
    // TEST_CASE("Addition Test With Pointers", testPtrsAddition);

    // Users can register a new test case using lambdas, avoiding writing standalone functions
    TEST_CASE("Subtraction Test", []() {
        int result = 5 - 3;
        assertEquals(2, result);
        assertEquals(2, result);
    });

    // Registering test cases into test suites, to group and relate tests that makes sense to exists
    // as a part of a whole

    // Instantiate a new test suite, giving it a unique identifier.
    TestSuite suite {"My Suite"};
    // Register test cases using function pointers into a test suite
    TEST_CASE(suite, "Addition Test", testAddition);
    // Forces a warning that alerts the user that the test will be discarded, since already
    // exists one with the same identifier in the given suite
    TEST_CASE(suite, "Addition Test", testAddition);
    // Register a test case designed to fail, useful for testing the behavior 
    // of RUN_TESTS with different failure modes.
    TEST_CASE(suite, "Subtraction Test", testSubtraction);

    // Register additional test cases to verify the functionality of RUN_TESTS
    // under different conditions.
    TEST_CASE(suite, "Multiplication Test", testMultiplication);

    // Create another test suite to further validate the behavior of RUN_TESTS
    // with multiple suites, especially under different failure modes.
    TestSuite anotherSuite {"Another Suite"};
    TEST_CASE(anotherSuite, "Addition Test", testAddition);
    TEST_CASE(anotherSuite, "Subtraction Test", testSubtraction);
    TEST_CASE(anotherSuite, "Multiplication Test", testMultiplication);

    // Don't forget to call this free function, to run all the tests written!
    // Options are: CONTINUE_ON_ERROR, HALT_SUITE_ON_FAIL, ABORT_ALL_ON_FAIL
    RUN_TESTS();

    return 0;
}


void run_containers_examples() {
    using namespace zero;

    constexpr auto a = collections::Array<long, 5> {1L, 2L, 3L, 4L, 5L};
    const Container<collections::Array<long, 5>>& b = collections::Array<long, 5> {1L, 2L, 3L, 4L, 5L};
    Container<collections::Array<long, 5>>* c = new collections::Array<long, 5> {1L, 2L, 3L, 4L, 5L};

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

void run_formatter_and_stylize_examples() {
    using namespace zero::fmt;

    std::cout << "#######Check formatter########\n\n";

    std::string format_str = "x = {10, y = 20, z = {}}";
    std::cout << formatter(format_str, 10) << std::endl;


    std::cout << "\n\n#######Check stylize########\n\n";


    std::string boldText = stylize("[WARNING] This is bold text", Color::YELLOW, {Modifier::BOLD});
    std::string faintText = stylize("[INFO] This is faint text", Color::GREEN, {Modifier::FAINT});
    std::string italicText = stylize("[DEBUG] This is italic text", Color::BLUE, {Modifier::ITALIC});
    std::string underlinedText = stylize("[ERROR] This is underlined text", Color::RED, {Modifier::UNDERLINE});
    std::string blinkingText = stylize("[CRITICAL] This is blinking text", Color::EXT_PURPLE, {Modifier::BLINK});
    std::string reversedText = stylize("[NOTICE] This is reversed text", Color::CYAN, {Modifier::REVERSE});
    std::string hiddenText = stylize("[SECRET] This is hidden text", Color::BLACK, {Modifier::HIDDEN});

    std::cout << boldText << "\n";
    std::cout << faintText << "\n";
    std::cout << italicText << "\n";
    std::cout << underlinedText << "\n";
    std::cout << blinkingText << "\n";
    std::cout << reversedText << "\n";
    std::cout << hiddenText << "\n";

    std::cout << "\n\n#######Check combination full text########\n\n";
    std::string format_str1 = "[WARNING] {} is deprecated. Please use {} instead.";
    std::string warning_msg = formatter(format_str1, "methodA", "methodB");
    std::string stylized_warning_msg = stylize(warning_msg, Color::YELLOW, {Modifier::BOLD});
    std::cout << stylized_warning_msg << std::endl;

    std::string format_str2 = "[ERROR] Failed to open file: {}";
    std::string error_msg = formatter(format_str2, "/path/to/file");
    std::string stylized_error_msg = stylize(error_msg, Color::RED, {Modifier::BOLD, Modifier::UNDERLINE});
    std::cout << stylized_error_msg << std::endl;

    std::cout << "\n\n#######Check combination partial text########\n\n";
    std::string format_str3 = "{} Successfully connected to server: {}";
    std::string stylized_info_msg = stylize("[INFO]", Color::GREEN, {Modifier::FAINT});
    std::string info_msg = formatter(format_str3,stylized_info_msg, "192.168.1.1");
    std::cout << info_msg << std::endl;

    std::cout << "\n\n#######Check unicode symbols########\n";
    std::string format_str4 = "{} Triple integral symbol: {}";
    std::string stylized_info_msg_2 = stylize("[INFO]", Color::GREEN, {Modifier::FAINT});
    std::string info_msg_2 = formatter(format_str4, stylized_info_msg_2, "∭");
    std::cout << info_msg_2 << "\n\n";
}

void run_print_examples() {
    using namespace zero::fmt;

    println("####### Print and Println Examples ########");

    // Basic print and println
    print("This is a simple string to show a print() example.");
    println("A println() example. The precious line use print, so this one is in the same line.");
    println("This is a simple string to show a println() example. It is on a new line because the previous one was also a println().");

    // Formatting examples with print and println
    print("Formatted print: x = {}, y = {}, z = {}", 10, 20, 30);
    println("Formatted println: x = {}, y = {}, z = {}", 10, 20, 30);
    println("Another formatted println: The unseen {} is the deadliest, {}", "Yasuo", "but of course, he is on the enemy team");

    newln();
}

import std;
import tsuite;

void run_test_suite_example();

// Driver code
int main() {
    run_test_suite_example();
    return 0;
}

// Let's define some example test functions using the assertion function
void testAddition() {
    int result = 2 + 2;
    assertEquals(4, result);
}

// Passing two pointers to compare if the values that they point to are equals
void testPtrsAddition() {
    int result = 2 + 2;
    int expected = 4;
    assertEquals(&expected, &result);
}

void run_test_suite_example() {
    // Free tests cases registration examples

    // Register a new test case using a function pointer.
    TEST_CASE("Addition Test With Pointers", testPtrsAddition);

    // Users can register a new test case using lambdas, avoiding to write standalone functions
    TEST_CASE("Subtraction Test", []() {
        int result = 5 - 3;
        assertEquals(122435, result);
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

    // Don't forget to call this free function, to run all the tests written!
    RUN_TESTS();
}

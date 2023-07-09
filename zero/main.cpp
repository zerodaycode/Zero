import std;
import tsuite;

// Let's define some example test functions using the assertion function
void testAddition() {
    int result = 2 + 2;
    assertEquals(4, result);
}

// Driver code
int main() {
    // Register test cases using function pointers
    TEST_CASE("Addition Test", testAddition);

    // Register test cases using lambdas
    TEST_CASE("Subtraction Test", []() {
        int result = 5 - 3;
        assertEquals(122, result);
    });

    // We can group related test into a suite
    TestSuite suite;
    // Register test cases using function pointers into a test suite
    TEST_CASE(suite, "Addition Test", testAddition);
    // Forces a warning that alerts the user that the test will be discarded, since already
    // exists one with the same identifier in the given suite
    TEST_CASE(suite, "Addition Test", testAddition);

    runTests();

    return 0;
}

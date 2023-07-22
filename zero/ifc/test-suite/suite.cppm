/**
 * The Zero's project custom test-suite
 *
 * This is a minimalistic implementation of a test-suite
 * that mainly allows ourselves to develop our source code
 * with confidence, without depending on some third-party
 * changing standards, implementations while avoiding the
 * typical dependency pitfalls
*/

export module tsuite;
export import :assertions;

import std;

/**
 *
 */
struct TestResults {
    int passed = 0;
    int failed = 0;
    std::vector<std::string> warnings {};
};

// Forward declarations
export struct TestSuite;
export struct TestCase;
void runTest(const TestCase* testCase, TestResults& testResults);
void runFreeTestCases();

// Top-level containers. They hold pointers to the types to avoid:
// `arithmetic on a pointer to an incomplete type`
std::vector<TestSuite*> testSuites;
std::vector<TestCase*> freeTestCases;

export {
    /// Common group of related test cases
    struct TestSuite {
        std::string uuid;
        std::vector<TestCase*> cases {};
        TestResults results {};

        constexpr TestSuite() = delete;
        constexpr explicit TestSuite(std::string uuid)
            : uuid(std::move(uuid)) {}

        friend bool operator==(const TestSuite& lhs, const TestSuite& rhs) {
            return lhs.uuid == rhs.uuid;
        }
    };

    /// Define a struct to represent a test case
    struct TestCase {
        std::string name;
        std::function<void()> fn;

        TestCase(std::string name, std::function<void()> fn)
            : name(std::move(name)), fn(std::move(fn)) {}
    };

    void TEST_CASE(const std::string& tname, const std::function<void()> tfunc) {
        freeTestCases.push_back(new TestCase(tname, tfunc));
    }

    void TEST_CASE(TestSuite& tsuite, const std::string& tname, const std::function<void()> tfunc) {
        auto it = std::find_if(tsuite.cases.begin(), tsuite.cases.end(), [&](const TestCase* tcase) {
            return tcase->name == tname;
        });

        /// Check that the user didn't registered a test case with the same identifier
        if (it == tsuite.cases.end())
            tsuite.cases.emplace_back(new TestCase(tname, tfunc));
        else
            tsuite.results.warnings.emplace_back(
                "\033[38;5;220m[Warning\033[0m in suite: \033[38;5;165m" +
                    tsuite.uuid + "\033[0m\033[38;5;220m]\033[0m "
                       "Already exists a test case with the name: \033[38;5;117m"
                       + tname + "\033[0m. Skipping test case."
            );
        /// If this is the first time that the suite is being registered
        auto suites_it = std::find_if(testSuites.begin(), testSuites.end(), [&](const TestSuite* suite) {
            return suite->uuid == tsuite.uuid;
        });
        if (suites_it == testSuites.end())
            testSuites.push_back(&tsuite);
    }

    // Function to run all the test cases and suites
    void RUN_TESTS() {
        if (!freeTestCases.empty())
            runFreeTestCases();
        std::cout
            << "\nRunning test suites. Total suites found: " << testSuites.size()
            << std::endl;

        for (const auto& test_suite : testSuites) {
            std::cout << "Running test suite: \033[38;5;165m" << test_suite->uuid << "\033[m";

            for (const auto& warning : test_suite->results.warnings)
                std::cout << "\n    " << warning << std::endl;
            for (const auto& test_case : test_suite->cases)
                runTest(test_case, test_suite->results);

            std::cout << "\nTest suite [" << test_suite->uuid << "] summary:" << std::endl;
            std::cout << "    \033[32mPassed:\033[0m " << test_suite->results.passed << std::endl;
            std::cout << "    \033[31mFailed:\033[0m " << test_suite->results.failed << std::endl;
        }
    }
}

void runFreeTestCases() {
    TestResults freeTestsResults;
    std::cout << "Running free tests: " << std::endl;
    for (const auto& testCase : freeTestCases) {
        runTest(testCase, freeTestsResults);
        std::cout << std::endl;
    }

    std::cout << "Free tests summary:" << std::endl;
    std::cout << "    \033[32mPassed:\033[0m " << freeTestsResults.passed << std::endl;
    std::cout << "    \033[31mFailed:\033[0m " << freeTestsResults.failed << std::endl;

}

void runTest(const TestCase* const testCase, TestResults& results) {
    std::cout << "    Running test: \033[38;5;117m" << testCase->name << "\033[0m";

    try {
        // Call the test function
        testCase->fn();
        std::cout << " ... Result => \033[32mPassed!\033[0m";
        results.passed++;
    } catch (const std::exception& ex) {
        std::cout << " ... Result => \033[31mFailed\033[0m: " << ex.what();
        results.failed++;
    }
}
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
/**
 * @enum TestRunBehavior
 * @brief Defines the behavior of the test runner upon encountering test failures.
 *
 * This enum allows selecting different strategies for test execution, 
 * useful for various testing scenarios ranging from comprehensive error analysis 
 * to immediate failure response.
 */
export enum TestRunBehavior {
    /**
     * @brief Execute all tests regardless of failures.
     *
     * Use this mode when a complete test run is needed to gather full information 
     * about the system's state or to understand the full extent of the issues.
     */
    CONTINUE_ON_ERROR,

    /**
     * @brief Halt the execution of the current test suite or free tests upon a failure and proceed to the next suite or free test.
     *
     * This mode stops the execution of the current suite or set of free tests immediately upon encountering a failure, 
     * then proceeds to the next suite or free test. It's beneficial for quickly bypassing problematic tests 
     * while still executing the remaining tests.
     */
    HALT_SUITE_ON_FAIL,

    /**
     * @brief Abort all testing activities immediately upon any failure.
     *
     * Choose this mode when a single failure indicates a critical system issue, 
     * necessitating immediate attention and halting further tests until resolution.
     */
    ABORT_ALL_ON_FAIL
};
bool runTest(const TestCase* testCase, TestResults& testResults);
bool runFreeTestCases(const TestRunBehavior behavior);

// Top-level containers. They hold pointers to the types to avoid:
// `arithmetic on a pointer to an incomplete type`
std::vector<TestSuite*> testSuites;
std::vector<TestCase*> freeTestCases;


export {
    /**
     * Common group of related test cases, identified by a unique string
     */
    struct TestSuite {
        std::string uuid;
        std::vector<TestCase*> cases {};
        TestResults results {};

        TestSuite() = delete;
        /**
         * @short This ctr shouldn't exist, since {@link std::string} has a constructor
         * for convert cstr to std::string
         * @bug Clang16 under windows linking against libc++ with mingw,
         * when the TestSuite new instance receives a const char* in a different file
         * than the main file (in particular from a module), Clang refuses to compile
         * saying that there's no viable ctr for TestSuite receiving a const char*
         *
         * For further @details @see https://github.com/llvm/llvm-project/issues/64211
        */
        constexpr explicit TestSuite(const char* uuid)
            : uuid(std::move(uuid)) {}
        constexpr explicit TestSuite(std::string uuid)
            : uuid(std::move(uuid)) {}

        TestSuite(const TestSuite& rhs) = delete;
        TestSuite (TestSuite&& rhs) = delete;

        friend bool operator==(const TestSuite& lhs, const TestSuite& rhs) {
            return lhs.uuid == rhs.uuid;
        }
    };

    /**
     * @struct Holds the data for a particular user's test case.
     */
    struct TestCase {
        std::string name;
        std::function<void()> fn;

        /**
         * @note waiting for Clang to implement the {@link std::function] constructors as *constexpr*,
         * so we can make the {@link TestCase] constexpr-constructible
         *
         * @details  constexpr constructor's 2nd parameter type 'std::function<void ()>' is not a literal type
         * constexpr TestCase(std::string name, std::function<void()> fn)
         *
         * 'function<void ()>' is not literal because it is not an aggregate and has no constexpr constructors other than copy or move constructors
         * class _LIBCPP_TEMPLATE_VIS function<_Rp(_ArgTypes...)>
         */
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
    void RUN_TESTS(const TestRunBehavior behavior) {
        if (!freeTestCases.empty()) {
            if (runFreeTestCases(behavior) && behavior == FAIL_NUC) 
                return;
        }
        std::cout
            << "\nRunning test suites. Total suites found: " << testSuites.size()
            << std::endl;
        

        for (const auto& test_suite : testSuites) {
            std::cout << "Running test suite: \033[38;5;165m" << test_suite->uuid << "\033[m";

            for (const auto& warning : test_suite->results.warnings)
                std::cout << "\n    " << warning << std::endl;
            for (const auto& test_case : test_suite->cases) {
                if (!runTest(test_case, test_suite->results)) {
                    if (behavior == FAIL_FAST) break;
                    if (behavior == FAIL_NUC) {
                    std::cout << "\nTest suite [" << test_suite->uuid << "] summary:" << std::endl;
                    std::cout << "    \033[32mPassed:\033[0m " << test_suite->results.passed << std::endl;
                    std::cout << "    \033[31mFailed:\033[0m " << test_suite->results.failed << std::endl;
                    return;
                    }
                }
            }

            std::cout << "\nTest suite [" << test_suite->uuid << "] summary:" << std::endl;
            std::cout << "    \033[32mPassed:\033[0m " << test_suite->results.passed << std::endl;
            std::cout << "    \033[31mFailed:\033[0m " << test_suite->results.failed << std::endl;
        }
    }
}

bool runFreeTestCases(const TestRunBehavior behavior) {
    bool anyFailed = false;
    TestResults freeTestsResults;
    std::cout << "Running free tests: " << std::endl;
     for (const auto& testCase : freeTestCases) {
        if (!runTest(testCase, freeTestsResults)) {
            anyFailed = true;
            if (behavior == FAIL_FAST){
                std::cout << "\n    Free tests summary:" << std::endl;
                std::cout << "    \033[32mPassed:\033[0m " << freeTestsResults.passed << std::endl;
                std::cout << "    \033[31mFailed:\033[0m " << freeTestsResults.failed << std::endl;
                break;
            } 
        }

    std::cout << "\n    Free tests summary:" << std::endl;
    std::cout << "    \033[32mPassed:\033[0m " << freeTestsResults.passed << std::endl;
    std::cout << "    \033[31mFailed:\033[0m " << freeTestsResults.failed << std::endl;
    }
    return anyFailed;
}

bool runTest(const TestCase* const testCase, TestResults& results) {
    std::cout << "\n    Running test: \033[38;5;117m" << testCase->name << "\033[0m";

    try {
        // Call the test function
        testCase->fn();
        std::cout << " ... Result => \033[32mPassed!\033[0m";
        results.passed++;
        return true;
    } catch (const std::exception& ex) {
        std::cout << " ... Result => \033[31mFailed\033[0m: " << ex.what();
        results.failed++;
        return false;
    }
}
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
import zero;
import stylizer;
import formatter;
import print_utils;

using namespace zero::fmt;

/**
 * @struct TestResults
 * @brief Holds the results of test execution.
 *
 * This structure is used to track the outcomes of a series of tests, 
 * including the number of passed and failed tests, along with any warnings 
 * that might have been generated during test execution.
 *
 * @var passed
 * The count of tests that have successfully passed.
 *
 * @var failed
 * The count of tests that have failed.
 *
 * @var warnings
 * A list of warning messages generated during test execution. Warnings are
 * used to notify about non-critical issues or potential problems in the tests,
 * which do not necessarily constitute test failures. For example, a warning
 * can be used to indicate the duplication of a test case.
 */
struct TestResults {
	int passed = 0;
	int failed = 0;
	std::vector<std::string> warnings{};
};

// Forward declarations
export struct TestSuite;
export struct TestCase;
/**
 * @enum TestRunBehavior
 * @brief Defines the behavior of the test runner upon encountering test
 * failures.
 *
 * This enum allows selecting different strategies for test execution,
 * useful for various testing scenarios ranging from comprehensive error
 * analysis to immediate failure response.
 */
export enum TestRunBehavior {
	/**
	 * @brief Execute all tests regardless of failures.
	 *
	 * Use this mode when a complete test run is needed to gather full
	 * information about the system's state or to understand the full extent of
	 * the issues.
	 */
	CONTINUE_ON_ERROR,

	/**
	 * @brief Halt the execution of the current test suite or free tests upon a
	 * failure and proceed to the next suite or free test.
	 *
	 * This mode stops the execution of the current suite or set of free tests
	 * immediately upon encountering a failure, then proceeds to the next suite
	 * or free test. It's beneficial for quickly bypassing problematic tests
	 * while still executing the remaining tests.
	 */
	HALT_SUITE_ON_FAIL,

	/**
	 * @brief Abort all testing activities immediately upon any failure.
	 *
	 * Choose this mode when a single failure indicates a critical system issue,
	 * necessitating immediate attention and halting further tests until
	 * resolution.
	 */
	ABORT_ALL_ON_FAIL
};

/**
 * @brief Executes a single test case and updates the test results.
 *
 * This function runs an individual test case and captures its success or failure.
 * It updates the passed and failed count in the provided TestResults object.
 * If the test case throws an exception, it is caught and treated as a test failure.
 *
 * @param testCase Pointer to the @ref TestCase to be executed.
 * @param testResults Reference to a @ref TestResults object where the outcome (pass/fail) 
 *                    of the test will be recorded.
 * @return Returns true if the test case passed, false if it failed.
 */
bool runTest(const TestCase *testCase, TestResults &testResults);

/**
 * @brief Executes all free-standing test cases based on the specified behavior.
 *
 * A "free-standing test" refers to a test case that is not part of any test suite. 
 * These are individual tests executed independently, without being grouped in a suite.
 * This function iterates over and executes all such free-standing test cases. The behavior
 * of the function upon encountering a failed test is determined by the @ref TestRunBehavior 
 * parameter. It can either continue running the remaining tests or halt/abort execution.
 *
 * @param behavior The @ref TestRunBehavior (e.g., CONTINUE_ON_ERROR, HALT_SUITE_ON_FAIL, 
 *                 ABORT_ALL_ON_FAIL) that determines the function's response to test 
 *                 failures.
 * @return Returns true if any test case failed, false otherwise.
 */
bool runFreeTestCases(const TestRunBehavior behavior);

/**
 * @brief Executes all test cases within test suites based on the specified behavior.
 *
 * This function iterates over all registered test suites, executing the test cases 
 * within each suite. The execution behavior upon encountering a test failure is 
 * governed by the @ref TestRunBehavior parameter. Depending on this parameter, the function 
 * can continue with the next tests/suites, halt the current suite, or abort all tests.
 *
 * @param behavior The @ref TestRunBehavior (e.g., CONTINUE_ON_ERROR, HALT_SUITE_ON_FAIL, 
 *                 ABORT_ALL_ON_FAIL) that influences the function's handling of test 
 *                 failures.
 */
void runSuiteTestCases(const TestRunBehavior behavior);

/**
 * @brief Checks for errors post test execution based on test run behavior.
 *
 * This function is designed to be called after all tests have been executed under
 * certain TestRunBehaviors (CONTINUE_ON_ERROR, HALT_SUITE_ON_FAIL). It determines if 
 * any errors occurred during the test runs. 
 * 
 * In scenarios where tests are allowed to continue despite failures (CONTINUE_ON_ERROR)
 * or where test execution is halted only for the current suite upon failure 
 * (HALT_SUITE_ON_FAIL), this function provides a final check to ascertain if any errors
 * were encountered during the entire testing process.
 *
 * The function evaluates two sources of potential errors:
 * 1. Free test errors, indicated by the boolean parameter 'freeTestsErrors'.
 * 2. Suite test errors, determined by examining all test suites for any failures.
 *
 * If errors are found in either free tests or test suites, the function terminates the
 * program with an exit code of 1, signaling an error condition.
 *
 * @param freeTestsErrors Boolean indicating if there were errors in the free tests.
 */
void checkForTestErrors(const bool freeTestsErrors);

// Top-level containers. They hold pointers to the types to avoid:
// `arithmetic on a pointer to an incomplete type`
std::vector<TestSuite *> testSuites;
std::vector<TestCase *> freeTestCases;

export {
	/**
	 * Common group of related test cases, identified by a unique string
	 */
	struct TestSuite {
		std::string uuid;
		std::vector<TestCase *> cases{};
		TestResults results{};

		TestSuite() = delete;
		/**
		 * @short This ctr shouldn't exist, since {@link std::string} has a
		 * constructor for convert cstr to std::string
		 * @bug Clang16 under windows linking against libc++ with mingw,
		 * when the TestSuite new instance receives a const char* in a different
		 * file than the main file (in particular from a module), Clang refuses
		 * to compile saying that there's no viable ctr for TestSuite receiving
		 * a const char*
		 *
		 * For further @details @see
		 * https://github.com/llvm/llvm-project/issues/64211
		 */
		constexpr explicit TestSuite(const char *uuid)
			: uuid(std::move(uuid)) {}
		constexpr explicit TestSuite(std::string uuid)
			: uuid(std::move(uuid)) {}

		TestSuite(const TestSuite &rhs) = delete;
		TestSuite(TestSuite &&rhs) = delete;

		friend bool operator==(const TestSuite &lhs, const TestSuite &rhs) {
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
		 * @note waiting for Clang to implement the {@link std::function]
		 * constructors as *constexpr*, so we can make the {@link TestCase]
		 * constexpr-constructible
		 *
		 * @details  constexpr constructor's 2nd parameter type
		 * 'std::function<void
		 * ()>' is not a literal type constexpr TestCase(std::string name,
		 * std::function<void()> fn)
		 *
		 * 'function<void ()>' is not literal because it is not an aggregate and
		 * has no constexpr constructors other than copy or move constructors
		 * class _LIBCPP_TEMPLATE_VIS function<_Rp(_ArgTypes...)>
		 */
		TestCase(std::string name, std::function<void()> fn)
			: name(std::move(name)), fn(std::move(fn)) {}
	};

	void TEST_CASE(const std::string &tname,
				   const std::function<void()> tfunc) {
		freeTestCases.push_back(new TestCase(tname, tfunc));
	}

	void TEST_CASE(TestSuite & tsuite, const std::string &tname,
				   const std::function<void()> tfunc) {
		auto it = std::find_if(
			tsuite.cases.begin(), tsuite.cases.end(),
			[&](const TestCase *tcase) { return tcase->name == tname; });

		/// Check that the user didn't registered a test case with the same
		/// identifier
		if (it == tsuite.cases.end())
			tsuite.cases.emplace_back(new TestCase(tname, tfunc));
		else
			tsuite.results.warnings.emplace_back(
				stylize("[Warning in suite: ", Color::YELLOW, {}) +
				stylize(tsuite.uuid, Color::EXT_PURPLE, {}) +
				stylize("] Already exists a test case with the name: ", Color::YELLOW, {}) +
				stylize(tname, Color::EXT_SKY_BLUE, {}) + 
				stylize(". Skipping test case.", Color::YELLOW, {}));
		/// If this is the first time that the suite is being registered
		auto suites_it = std::find_if(
			testSuites.begin(), testSuites.end(),
			[&](const TestSuite *suite) { return suite->uuid == tsuite.uuid; });
		if (suites_it == testSuites.end())
			testSuites.push_back(&tsuite);
	}

	// Function to run all the test cases and suites
	void RUN_TESTS(const TestRunBehavior behavior = ABORT_ALL_ON_FAIL) {
		bool freeTestsErrors = false;
		if (!freeTestCases.empty()) {
			freeTestsErrors = runFreeTestCases(behavior);
		}
		runSuiteTestCases(behavior);

		checkForTestErrors(freeTestsErrors);
	}
}

void runSuiteTestCases(const TestRunBehavior behavior) {
	println("\nRunning test suites. Total suites found: {}", testSuites.size());


	for (const auto &test_suite : testSuites) {
		println("Running test suite:" + stylize(" {}", Color::EXT_PURPLE, {}), test_suite->uuid);


		for (const auto &warning : test_suite->results.warnings)
			println("\n    {}", warning);
		for (const auto &test_case : test_suite->cases) {
			if (!runTest(test_case, test_suite->results)) {

				if (behavior == HALT_SUITE_ON_FAIL) {
				  println(stylize("\n========================================"
                                    "\n[Halt Suite Tests] Stopping further tests of the suite ", Color::EXT_LIGHT_ORANGE, {Modifier::BOLD}) +
									stylize("{} ", Color::EXT_PURPLE, {}) +
									stylize("due to a failure."
                                    "\n========================================", Color::EXT_LIGHT_ORANGE, {Modifier::BOLD}), 
									test_suite->uuid);
					break;
				}

				if (behavior == ABORT_ALL_ON_FAIL) {
					println("Test suite [{}] summary:", test_suite->uuid);
					println(stylize("    Passed: {}", Color::GREEN, {}), test_suite->results.passed);
					println(stylize("    Failed: {}", Color::RED, {}), test_suite->results.failed);

					println(stylize("\n========================================"
									"\n[Abort] All further tests are aborted due to a failure in a test in this suite."
									"\n========================================", Color::RED, {Modifier::BOLD}));
					return;
				}
			}
		}

  		println("Test suite [{}] summary:", test_suite->uuid);
        println(stylize("    Passed: {}", Color::GREEN, {}), test_suite->results.passed);
		println(stylize("    Failed: {}", Color::RED, {}), test_suite->results.failed);
	}
}

bool runFreeTestCases(const TestRunBehavior behavior) {
	bool anyFailed = false;
	TestResults freeTestsResults;
    println("Running free tests:");

	for (const auto &testCase : freeTestCases) {
		if (!runTest(testCase, freeTestsResults)) {
			anyFailed = true;
			if (behavior == ABORT_ALL_ON_FAIL ||
				behavior == HALT_SUITE_ON_FAIL) {
				break;
			}
		}
	}

 	println("\nFree tests summary:");
    println(stylize("    Passed: {}", Color::GREEN, {}), freeTestsResults.passed);
    println(stylize("    Failed: {}", Color::RED, {}), freeTestsResults.failed);

	if (anyFailed) {
		if (behavior == HALT_SUITE_ON_FAIL) {
            println(stylize("\n========================================"
                            "\n[Halt Free Tests] Stopping further free tests due to a failure."
                            "\n========================================", Color::EXT_LIGHT_ORANGE, {Modifier::BOLD}));
        } else if (behavior == ABORT_ALL_ON_FAIL) {
            println(stylize("\n========================================"
                            "\n[Abort] All further tests are aborted due to a failure in free tests."
                            "\n========================================", Color::RED, {Modifier::BOLD}));
            std::exit(1);
        }
	}

	return anyFailed;
}

bool runTest(const TestCase *const testCase, TestResults &results) {
	print("\n    Running test: {}", stylize(testCase->name, Color::EXT_SKY_BLUE, {}));
	try {
		// Call the test function
		testCase->fn();
        print(" ... Result => {}", stylize("Passed!", Color::GREEN, {}));
		results.passed++;
		return true;
	} catch (const std::exception &ex) {
		println(" ... Result => {}: {}", stylize("Failed", Color::RED, {}), ex.what());
		results.failed++;
		return false;
	}
}


void checkForTestErrors(const bool freeTestsErrors) {
	
	bool suiteTestsErrors = std::any_of(
		testSuites.begin(), testSuites.end(),
		[](const TestSuite *suite) { return suite->results.failed > 0; });
	std::cout << freeTestsErrors << " " << suiteTestsErrors;
	if (suiteTestsErrors || freeTestsErrors) std::exit(1);
}
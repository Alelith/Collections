/**
 * @file test_colors.hpp
 * @brief ANSI color codes and test macros for console output
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 */

/**
 * @defgroup test_utilities Test Utilities
 * @brief Testing infrastructure and helper macros
 * 
 * @details This module provides color-coded console output macros and
 * test reporting utilities for the test suite. Uses ANSI escape codes
 * for terminal color support.
 * 
 * @section module_features_sec Features
 * - ANSI color definitions for colored terminal output
 * - Test header and section macros
 * - Pass/fail reporting macros
 * - Consistent test output formatting
 * 
 * @section module_usage_sec Usage
 * Include this header in test files and use the provided macros:
 * TEST_HEADER() for test file headers, TEST_GROUP() for test sections,
 * TEST_PASS() for successful tests, TEST_FAIL() for failures.
 */

#pragma once

/**
 * @def COLOR_RESET
 * @brief ANSI code to reset terminal color
 * @ingroup test_utilities
 */
#define COLOR_RESET   "\033[0m"

/**
 * @def COLOR_RED
 * @brief ANSI code for red text
 * @ingroup test_utilities
 */
#define COLOR_RED	 "\033[0;31m"

/**
 * @def COLOR_GREEN
 * @brief ANSI code for green text
 * @ingroup test_utilities
 */
#define COLOR_GREEN   "\033[0;32m"

/**
 * @def COLOR_YELLOW
 * @brief ANSI code for yellow text
 * @ingroup test_utilities
 */
#define COLOR_YELLOW  "\033[1;33m"

/**
 * @def COLOR_BLUE
 * @brief ANSI code for blue text
 * @ingroup test_utilities
 */
#define COLOR_BLUE	"\033[0;34m"

/**
 * @def COLOR_MAGENTA
 * @brief ANSI code for magenta text
 * @ingroup test_utilities
 */
#define COLOR_MAGENTA "\033[0;35m"

/**
 * @def COLOR_CYAN
 * @brief ANSI code for cyan text
 * @ingroup test_utilities
 */
#define COLOR_CYAN	"\033[0;36m"

/**
 * @def COLOR_BOLD
 * @brief ANSI code for bold text
 * @ingroup test_utilities
 */
#define COLOR_BOLD	"\033[1m"

/**
 * @def TEST_HEADER
 * @brief Prints a bold blue header for test file
 * @ingroup test_utilities
 * @param name Name of the test suite
 */
#define TEST_HEADER(name) std::cout << COLOR_BOLD << COLOR_BLUE << "=== Testing " << name << " ===" << COLOR_RESET << std::endl

/**
 * @def TEST_GROUP
 * @brief Prints a cyan message for test group
 * @ingroup test_utilities
 * @param msg Description of test group being executed
 */
#define TEST_GROUP(msg) std::cout << COLOR_CYAN << "Testing " << msg << "..." << COLOR_RESET << std::endl

/**
 * @def TEST_PASS
 * @brief Prints a green success message with checkmark
 * @ingroup test_utilities
 * @param msg Description of passed test
 */
#define TEST_PASS(msg) std::cout << COLOR_GREEN << "✓ " << msg << " passed" << COLOR_RESET << std::endl

/**
 * @def TEST_SUCCESS
 * @brief Prints a bold green success message for entire suite
 * @ingroup test_utilities
 * @param name Name of the test suite that passed
 */
#define TEST_SUCCESS(name) std::cout << "\n" << COLOR_BOLD << COLOR_GREEN << "✓✓✓ All " << name << " tests passed! ✓✓✓" << COLOR_RESET << "\n" << std::endl

/**
 * @def TEST_FAIL
 * @brief Prints a bold red failure message
 * @ingroup test_utilities
 * @param msg Description of failed test
 */
#define TEST_FAIL(msg) std::cerr << COLOR_BOLD << COLOR_RED << "✗ Test failed: " << msg << COLOR_RESET << std::endl

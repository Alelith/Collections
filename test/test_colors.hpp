#pragma once

// ANSI color codes
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[0;31m"
#define COLOR_GREEN   "\033[0;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_BLUE    "\033[0;34m"
#define COLOR_MAGENTA "\033[0;35m"
#define COLOR_CYAN    "\033[0;36m"
#define COLOR_BOLD    "\033[1m"

// Helper macros for colored output
#define TEST_HEADER(name) std::cout << COLOR_BOLD << COLOR_BLUE << "=== Testing " << name << " ===" << COLOR_RESET << std::endl
#define TEST_GROUP(msg) std::cout << COLOR_CYAN << "Testing " << msg << "..." << COLOR_RESET << std::endl
#define TEST_PASS(msg) std::cout << COLOR_GREEN << "✓ " << msg << " passed" << COLOR_RESET << std::endl
#define TEST_SUCCESS(name) std::cout << "\n" << COLOR_BOLD << COLOR_GREEN << "✓✓✓ All " << name << " tests passed! ✓✓✓" << COLOR_RESET << "\n" << std::endl
#define TEST_FAIL(msg) std::cerr << COLOR_BOLD << COLOR_RED << "✗ Test failed: " << msg << COLOR_RESET << std::endl

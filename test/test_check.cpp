/**
 * @file test_check.cpp
 * @brief Unit tests for character validation functions
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 * 
 * @details This file contains comprehensive unit tests for all
 * character validation and string comparison functions in the check
 * module. Tests cover alphabetic, numeric, alphanumeric, whitespace,
 * case detection, printable characters, and string operations.
 */

#include <iostream>
#include <cassert>
#include "test_colors.hpp"
#include "standard_functions/check.hpp"

/**
 * @brief Tests isAlphabetic function
 * 
 * @details Verifies that isAlphabetic correctly identifies uppercase
 * and lowercase letters while rejecting numbers, spaces, and special
 * characters.
 * 
 * @ingroup test_utilities
 */
void test_isAlphabetic() {
	TEST_GROUP("isAlphabetic");
	
	assert(isAlphabetic('a'));
	assert(isAlphabetic('m'));
	assert(isAlphabetic('z'));
	
	assert(isAlphabetic('A'));
	assert(isAlphabetic('M'));
	assert(isAlphabetic('Z'));
	
	assert(!isAlphabetic('0'));
	assert(!isAlphabetic('9'));
	assert(!isAlphabetic(' '));
	assert(!isAlphabetic('!'));
	assert(!isAlphabetic('@'));
	assert(!isAlphabetic('\n'));
	
	TEST_PASS("isAlphabetic");
}

/**
 * @brief Tests isNumeric function
 * 
 * @details Verifies that isNumeric correctly identifies decimal digits
 * (0-9) while rejecting letters, spaces, and special characters.
 * 
 * @ingroup test_utilities
 */
void test_isNumeric() {
	TEST_GROUP("isNumeric");
	
	assert(isNumeric('0'));
	assert(isNumeric('5'));
	assert(isNumeric('9'));
	
	assert(!isNumeric('a'));
	assert(!isNumeric('Z'));
	assert(!isNumeric(' '));
	assert(!isNumeric('!'));
	assert(!isNumeric('\n'));
	
	TEST_PASS("isNumeric");
}

/**
 * @brief Tests isAlphanumeric function
 * 
 * @details Verifies that isAlphanumeric correctly identifies letters
 * and digits while rejecting spaces and special characters.
 * 
 * @ingroup test_utilities
 */
void test_isAlphanumeric() {
	TEST_GROUP("isAlphanumeric");
	
	assert(isAlphanumeric('a'));
	assert(isAlphanumeric('Z'));
	
	assert(isAlphanumeric('0'));
	assert(isAlphanumeric('9'));
	
	assert(!isAlphanumeric(' '));
	assert(!isAlphanumeric('!'));
	assert(!isAlphanumeric('@'));
	assert(!isAlphanumeric('\n'));
	
	TEST_PASS("isAlphanumeric");
}

/**
 * @brief Tests isWhitespace function
 * 
 * @details Verifies that isWhitespace correctly identifies all
 * whitespace characters (space, tab, newline, carriage return,
 * vertical tab, form feed) while rejecting other characters.
 * 
 * @ingroup test_utilities
 */
void test_isWhitespace() {
	TEST_GROUP("isWhitespace");
	
	assert(isWhitespace(' '));
	assert(isWhitespace('\t'));
	assert(isWhitespace('\n'));
	assert(isWhitespace('\r'));
	assert(isWhitespace('\v'));
	assert(isWhitespace('\f'));
	
	assert(!isWhitespace('a'));
	assert(!isWhitespace('0'));
	assert(!isWhitespace('!'));
	
	TEST_PASS("isWhitespace");
}

/**
 * @brief Tests isUppercase function
 * 
 * @details Verifies that isUppercase correctly identifies uppercase
 * letters (A-Z) while rejecting lowercase letters, digits, and other
 * characters.
 * 
 * @ingroup testing
 */
void test_isUppercase() {
	TEST_GROUP("isUppercase");
	
	assert(isUppercase('A'));
	assert(isUppercase('M'));
	assert(isUppercase('Z'));
	
	assert(!isUppercase('a'));
	assert(!isUppercase('z'));
	assert(!isUppercase('0'));
	assert(!isUppercase(' '));
	
	TEST_PASS("isUppercase");
}

/**
 * @brief Tests isLowercase function
 * 
 * @details Verifies that isLowercase correctly identifies lowercase
 * letters (a-z) while rejecting uppercase letters, digits, and other
 * characters.
 * 
 * @ingroup testing
 */
void test_isLowercase() {
	TEST_GROUP("isLowercase");
	
	assert(isLowercase('a'));
	assert(isLowercase('m'));
	assert(isLowercase('z'));
	
	assert(!isLowercase('A'));
	assert(!isLowercase('Z'));
	assert(!isLowercase('0'));
	assert(!isLowercase(' '));
	
	TEST_PASS("isLowercase");
}

/**
 * @brief Tests isPrintable function
 * 
 * @details Verifies that isPrintable correctly identifies printable
 * ASCII characters (32-126) while rejecting control characters and
 * non-printable codes.
 * 
 * @ingroup testing
 */
void test_isPrintable() {
	TEST_GROUP("isPrintable");
	
	assert(isPrintable(' '));
	assert(isPrintable('a'));
	assert(isPrintable('Z'));
	assert(isPrintable('0'));
	assert(isPrintable('!'));
	assert(isPrintable('~'));
	
	assert(!isPrintable('\0'));
	assert(!isPrintable('\n'));
	assert(!isPrintable('\t'));
	assert(!isPrintable(127));
	
	TEST_PASS("isPrintable");
}

/**
 * @brief Tests strContains function
 * 
 * @details Verifies that strContains correctly searches for
 * character presence in strings. Tests include case sensitivity,
 * empty strings, null pointer handling, and special characters.
 * 
 * @ingroup testing
 */
void test_strContains() {
	TEST_GROUP("strContains");
	
	assert(strContains("hello", 'h'));
	assert(strContains("hello", 'e'));
	assert(strContains("hello", 'l'));
	assert(strContains("hello", 'o'));
	
	assert(!strContains("hello", 'x'));
	assert(!strContains("hello", 'H'));
	assert(!strContains("hello", '0'));
	
	assert(!strContains("", 'a'));
	
	assert(!strContains(nullptr, 'a'));
	
	assert(strContains("hello world!", ' '));
	assert(strContains("hello world!", '!'));
	
	TEST_PASS("strContains");
}

/**
 * @brief Tests strCompare function
 * 
 * @details Verifies that strCompare correctly performs exact string
 * equality comparison. Tests include case sensitivity, length
 * differences, null pointer handling, and special characters.
 * 
 * @ingroup testing
 */
void test_strCompare() {
	TEST_GROUP("strCompare");
	
	assert(strCompare("hello", "hello"));
	assert(strCompare("", ""));
	assert(strCompare("test123", "test123"));
	
	assert(!strCompare("hello", "world"));
	assert(!strCompare("hello", "Hello"));
	assert(!strCompare("abc", "abcd"));
	assert(!strCompare("abcd", "abc"));
	
	assert(!strCompare(nullptr, "hello"));
	assert(!strCompare("hello", nullptr));
	assert(!strCompare(nullptr, nullptr));
	
	assert(strCompare("hello world!", "hello world!"));
	assert(!strCompare("hello world", "hello world!"));
	
	TEST_PASS("strCompare");
}

int main() {
	TEST_HEADER("Check Functions");
	
	try {
		test_isAlphabetic();
		test_isNumeric();
		test_isAlphanumeric();
		test_isWhitespace();
		test_isUppercase();
		test_isLowercase();
		test_isPrintable();
		test_strContains();
		test_strCompare();
		
		TEST_SUCCESS("Check Functions");
		return 0;
	} catch (const std::exception& e) {
		TEST_FAIL(e.what());
		return 1;
	}
}

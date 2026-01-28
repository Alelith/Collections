/**
 * @file test_conversion.cpp
 * @brief Unit tests for type conversion functions
 * 
 * @details Comprehensive test suite that validates all numeric and
 * string conversion functions. Tests include edge cases, error
 * handling, boundary values, and special numeric values (NaN, Inf).
 * 
 * @ingroup testing
 * @author Super Library Team
 * @date 2024
 */

#include <iostream>
#include <cassert>
#include <cmath>
#include "test_colors.hpp"
#include "standard_functions/conversion.hpp"

/**
 * @brief Tests baseNumToString function with various bases
 * 
 * @details Verifies conversion of integers to strings in different
 * bases (binary, octal, decimal, hexadecimal). Tests include zero,
 * positive numbers, invalid bases, and boundary conditions.
 * 
 * @ingroup testing
 */
void test_baseNumToString() {
	TEST_GROUP("baseNumToString");
	
	assert(baseNumToString(0, 10) == "0");
	assert(baseNumToString(123, 10) == "123");
	assert(baseNumToString(-456, 10) == "-456");
	
	assert(baseNumToString(5, 2) == "101");
	assert(baseNumToString(15, 2) == "1111");
	assert(baseNumToString(0, 2) == "0");
	
	assert(baseNumToString(255, 16) == "FF");
	assert(baseNumToString(16, 16) == "10");
	assert(baseNumToString(0, 16) == "0");
	
	assert(baseNumToString(64, 8) == "100");
	assert(baseNumToString(8, 8) == "10");
	
	assert(baseNumToString(10, 1) == "");
	assert(baseNumToString(10, 37) == "");
	
	TEST_PASS("baseNumToString");
}

/**
 * @brief Tests intToString function
 * 
 * @details Verifies conversion of integers to decimal strings,
 * including zero, positive, and negative values with various
 * magnitudes.
 * 
 * @ingroup testing
 */
void test_intToString() {
	TEST_GROUP("intToString");
	
	assert(intToString(0) == "0");
	assert(intToString(123) == "123");
	assert(intToString(-456) == "-456");
	assert(intToString(1000) == "1000");
	assert(intToString(-9999) == "-9999");
	
	TEST_PASS("intToString");
}

/**
 * @brief Tests longToString function
 * 
 * @details Verifies conversion of long integers to decimal strings,
 * testing large positive and negative values.
 * 
 * @ingroup testing
 */
void test_longToString() {
	TEST_GROUP("longToString");
	
	assert(longToString(0L) == "0");
	assert(longToString(123456789L) == "123456789");
	assert(longToString(-987654321L) == "-987654321");
	assert(longToString(1000000L) == "1000000");
	
	TEST_PASS("longToString");
}

/**
 * @brief Tests floatToString function
 * 
 * @details Verifies conversion of floating-point numbers to strings,
 * including normal values, special values (NaN, infinity), and edge
 * cases. Tests platform-independent string representations.
 * 
 * @ingroup testing
 */
void test_floatToString() {
	TEST_GROUP("floatToString");
	
	string result = floatToString(0.0f);
	assert(result.find("0.000000") != string::npos || result == "0.000000");
	
	result = floatToString(123.456f);
	assert(result.find("123.45") != string::npos);
	
	result = floatToString(-456.789f);
	assert(result.find("456.78") != string::npos || result.find("456.79") != string::npos);
	
	assert(floatToString(0.0f / 0.0f) == "nan");
	assert(floatToString(1.0f / 0.0f) == "inf");
	assert(floatToString(-1.0f / 0.0f) == "-inf");
	
	TEST_PASS("floatToString");
}

/**
 * @brief Tests doubleToString function
 * 
 * @details Verifies conversion of double-precision floating-point
 * numbers to strings, including normal values and special values
 * (NaN, infinity).
 * 
 * @ingroup testing
 */
void test_doubleToString() {
	TEST_GROUP("doubleToString");
	
	string result = doubleToString(0.0);
	assert(result.find("0.000000") != string::npos || result == "0.000000");
	
	result = doubleToString(123.456);
	assert(result.find("123.45") != string::npos);
	
	result = doubleToString(-456.789);
	assert(result.find("456.78") != string::npos || result.find("456.79") != string::npos);
	
	assert(doubleToString(0.0 / 0.0) == "nan");
	assert(doubleToString(1.0 / 0.0) == "inf");
	assert(doubleToString(-1.0 / 0.0) == "-inf");
	
	TEST_PASS("doubleToString");
}

/**
 * @brief Tests stringToInt function
 * 
 * @details Verifies conversion of strings to integers, including
 * positive/negative values, leading signs, partial parsing of mixed
 * content, and error handling for invalid input.
 * 
 * @ingroup testing
 */
void test_stringToInt() {
	TEST_GROUP("stringToInt");
	
	assert(stringToInt("0") == 0);
	assert(stringToInt("123") == 123);
	assert(stringToInt("-456") == -456);
	assert(stringToInt("+789") == 789);
	assert(stringToInt("1000") == 1000);
	
	assert(stringToInt("123abc") == 123);
	assert(stringToInt("456.789") == 456);
	
	assert(stringToInt("") == 0);
	
	assert(stringToInt("abc") == 0);
	
	TEST_PASS("stringToInt");
}

/**
 * @brief Tests stringToLong function
 * 
 * @details Verifies conversion of strings to long integers,
 * including large values, signs, partial parsing, and empty string
 * handling.
 * 
 * @ingroup testing
 */
void test_stringToLong() {
	TEST_GROUP("stringToLong");
	
	assert(stringToLong("0") == 0L);
	assert(stringToLong("123456789") == 123456789L);
	assert(stringToLong("-987654321") == -987654321L);
	assert(stringToLong("+111111") == 111111L);
	
	assert(stringToLong("123abc") == 123L);
	
	assert(stringToLong("") == 0L);
	
	TEST_PASS("stringToLong");
}

/**
 * @brief Tests stringToFloat function
 * 
 * @details Verifies conversion of strings to floating-point numbers,
 * including decimal values, special values (NaN, infinity), and
 * empty string handling.
 * 
 * @ingroup testing
 */
void test_stringToFloat() {
	TEST_GROUP("stringToFloat");
	
	assert(std::abs(stringToFloat("0.0") - 0.0f) < 0.001f);
	assert(std::abs(stringToFloat("123.456") - 123.456f) < 0.001f);
	assert(std::abs(stringToFloat("-456.789") - (-456.789f)) < 0.001f);
	assert(std::abs(stringToFloat("+789.012") - 789.012f) < 0.001f);
	
	assert(std::abs(stringToFloat("100") - 100.0f) < 0.001f);
	
	float nan_val = stringToFloat("nan");
	assert(nan_val != nan_val);
	assert(stringToFloat("inf") == 1.0f / 0.0f);
	assert(stringToFloat("-inf") == -1.0f / 0.0f);
	
	assert(stringToFloat("") == 0.0f);
	
	TEST_PASS("stringToFloat");
}

/**
 * @brief Tests stringToDouble function
 * 
 * @details Verifies conversion of strings to double-precision
 * floating-point numbers, including high-precision values, special
 * values (NaN, infinity), and empty string handling.
 * 
 * @ingroup testing
 */
void test_stringToDouble() {
	TEST_GROUP("stringToDouble");
	
	assert(std::abs(stringToDouble("0.0") - 0.0) < 0.000001);
	assert(std::abs(stringToDouble("123.456789") - 123.456789) < 0.000001);
	assert(std::abs(stringToDouble("-456.789012") - (-456.789012)) < 0.000001);
	assert(std::abs(stringToDouble("+789.012345") - 789.012345) < 0.000001);
	
	assert(std::abs(stringToDouble("1000") - 1000.0) < 0.000001);
	
	double nan_val = stringToDouble("nan");
	assert(nan_val != nan_val);
	assert(stringToDouble("inf") == 1.0 / 0.0);
	assert(stringToDouble("-inf") == -1.0 / 0.0);
	
	assert(stringToDouble("") == 0.0);
	
	TEST_PASS("stringToDouble");
}

/**
 * @brief Tests toUppercase character conversion
 * 
 * @details Verifies conversion of lowercase letters to uppercase,
 * while preserving uppercase letters, digits, and special characters.
 * 
 * @ingroup testing
 */
void test_toUppercase() {
	TEST_GROUP("toUppercase");
	
	assert(toUppercase('a') == 'A');
	assert(toUppercase('m') == 'M');
	assert(toUppercase('z') == 'Z');
	
	assert(toUppercase('A') == 'A');
	assert(toUppercase('Z') == 'Z');
	
	assert(toUppercase('0') == '0');
	assert(toUppercase(' ') == ' ');
	assert(toUppercase('!') == '!');
	
	TEST_PASS("toUppercase");
}

/**
 * @brief Tests toLowercase character conversion
 * 
 * @details Verifies conversion of uppercase letters to lowercase,
 * while preserving lowercase letters, digits, and special characters.
 * 
 * @ingroup testing
 */
void test_toLowercase() {
	TEST_GROUP("toLowercase");
	
	assert(toLowercase('A') == 'a');
	assert(toLowercase('M') == 'm');
	assert(toLowercase('Z') == 'z');
	
	assert(toLowercase('a') == 'a');
	assert(toLowercase('z') == 'z');
	
	assert(toLowercase('0') == '0');
	assert(toLowercase(' ') == ' ');
	assert(toLowercase('!') == '!');
	
	TEST_PASS("toLowercase");
}

/**
 * @brief Tests edge cases in conversion functions
 * 
 * @details Verifies correct handling of special cases including zero
 * values, negative zero, large numbers, and mixed alphanumeric strings.
 * 
 * @ingroup testing
 */
void test_conversion_edge_cases() {
	TEST_GROUP("Conversion edge cases");
	
	assert(intToString(0) == "0");
	assert(stringToInt("0") == 0);
	
	string result = floatToString(-0.0f);
	assert(result.find("0") != string::npos);
	
	assert(stringToLong("999999999") == 999999999L);
	
	assert(stringToInt("123abc456") == 123);
	
	TEST_PASS("Conversion edge cases");
}

int main() {
	TEST_HEADER("Conversion Functions");
	
	try {
		test_baseNumToString();
		test_intToString();
		test_longToString();
		test_floatToString();
		test_doubleToString();
		test_stringToInt();
		test_stringToLong();
		test_stringToFloat();
		test_stringToDouble();
		test_toUppercase();
		test_toLowercase();
		test_conversion_edge_cases();
		
		TEST_SUCCESS("Conversion Functions");
		return 0;
	} catch (const std::exception& e) {
		TEST_FAIL(e.what());
		return 1;
	}
}

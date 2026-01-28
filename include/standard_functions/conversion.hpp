/**
 * @file conversion.hpp
 * @brief Type conversion and formatting utilities
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 */

#ifndef CONVERSION_HPP
#define CONVERSION_HPP

#include <string>
using std::string;

/**
 * @defgroup type_conversion Type Conversion Module
 * @brief Functions for converting between numeric and string types
 * 
 * @details This module provides comprehensive conversion utilities for
 * transforming numeric types to strings and vice versa. Supports
 * multiple numeric bases, floating-point formatting, and special value
 * handling (NaN, infinity). Also includes character case conversion.
 * 
 * @section module_features_sec Features
 * - Arbitrary base numeric to string conversion (base 2-36)
 * - Integer type conversions (int, long)
 * - Floating-point conversions (float, double) with precision control
 * - String to numeric parsing functions
 * - Character case conversion (uppercase/lowercase)
 * - Special value handling (NaN, infinity, negative zero)
 * 
 * @section module_usage_sec Usage
 * Conversion functions are straightforward to use. Numeric to string
 * functions always return valid strings. String to numeric functions
 * may throw exceptions for invalid input. All functions handle edge
 * cases and special values appropriately.
 */

string baseNumToString(long value, int base);
string intToString(int value);
string longToString(long value);
string floatToString(float value);
string doubleToString(double value);
int stringToInt(const string& str);
long stringToLong(const string& str);
float stringToFloat(const string& str);
double stringToDouble(const string& str);
char toUppercase(char c);
char toLowercase(char c);

#endif

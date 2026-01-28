/**
 * @file check.hpp
 * @brief Character validation and string comparison utilities
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 */

#ifndef CHECK_HPP
#define CHECK_HPP

/**
 * @defgroup char_validation Character Validation Module
 * @brief Functions for character type checking and validation
 * 
 * @details This module provides a comprehensive set of functions to
 * validate character types and perform string operations. All functions
 * are designed to be efficient and work with ASCII character encoding.
 * 
 * @section module_features_sec Features
 * - Alphabetic character detection (a-z, A-Z)
 * - Numeric digit validation (0-9)
 * - Whitespace detection (space, tab, newline, etc.)
 * - Case detection (uppercase/lowercase)
 * - Printable character validation
 * - String search and comparison operations
 * 
 * @section module_usage_sec Usage
 * All functions accept single characters or C-style strings as input
 * and return boolean values. Character validation functions are
 * safe for all input values and handle edge cases appropriately.
 */

bool isAlphabetic(char c);
bool isNumeric(char c);
bool isAlphanumeric(char c);
bool isWhitespace(char c);
bool isUppercase(char c);
bool isLowercase(char c);
bool isPrintable(char c);
bool strContains(const char* str, char c);
bool strCompare(const char* str1, const char* str2);

#endif

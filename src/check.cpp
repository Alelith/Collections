/**
 * @file check.cpp
 * @brief Implementation of character validation functions
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 */

/**
 * @brief Checks if a character is alphabetic
 * 
 * @details Validates whether the given character is an alphabetic letter
 * in the English alphabet (a-z or A-Z). Uses ASCII value ranges for
 * efficient validation.
 * 
 * @ingroup char_validation
 * 
 * @param[in] c Character to validate
 * @return true if character is alphabetic, false otherwise
 */
bool isAlphabetic(char c) {
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

/**
 * @brief Checks if a character is a numeric digit
 * 
 * @details Validates whether the given character is a decimal digit
 * (0-9). Uses ASCII value range for efficient validation.
 * 
 * @ingroup char_validation
 * 
 * @param[in] c Character to validate
 * @return true if character is a digit, false otherwise
 */
bool isNumeric(char c) {
	return (c >= '0' && c <= '9');
}

/**
 * @brief Checks if a character is alphanumeric
 * 
 * @details Validates whether the given character is either alphabetic
 * (a-z, A-Z) or numeric (0-9). Combines alphabetic and numeric checks.
 * 
 * @ingroup char_validation
 * 
 * @param[in] c Character to validate
 * @return true if character is alphanumeric, false otherwise
 */
bool isAlphanumeric(char c) {
	return isAlphabetic(c) || isNumeric(c);
}

/**
 * @brief Checks if a character is whitespace
 * 
 * @details Validates whether the given character is a whitespace
 * character including space, tab, newline, carriage return, vertical
 * tab, or form feed.
 * 
 * @ingroup char_validation
 * 
 * @param[in] c Character to validate
 * @return true if character is whitespace, false otherwise
 */
bool isWhitespace(char c) {
	return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f';
}

/**
 * @brief Checks if a character is uppercase
 * 
 * @details Validates whether the given character is an uppercase
 * alphabetic letter (A-Z). Uses ASCII value range for efficient
 * validation.
 * 
 * @ingroup char_validation
 * 
 * @param[in] c Character to validate
 * @return true if character is uppercase, false otherwise
 */
bool isUppercase(char c) {
	return (c >= 'A' && c <= 'Z');
}

/**
 * @brief Checks if a character is lowercase
 * 
 * @details Validates whether the given character is a lowercase
 * alphabetic letter (a-z). Uses ASCII value range for efficient
 * validation.
 * 
 * @ingroup char_validation
 * 
 * @param[in] c Character to validate
 * @return true if character is lowercase, false otherwise
 */
bool isLowercase(char c) {
	return (c >= 'a' && c <= 'z');
}

/**
 * @brief Checks if a character is printable
 * 
 * @details Validates whether the given character is a printable ASCII
 * character (space through tilde, values 32-126). Non-printable
 * control characters return false.
 * 
 * @ingroup char_validation
 * 
 * @param[in] c Character to validate
 * @return true if character is printable, false otherwise
 */
bool isPrintable(char c) {
	return (c >= 32 && c <= 126);
}

/**
 * @brief Searches for a character in a string
 * 
 * @details Scans through a null-terminated C-style string to determine
 * if it contains the specified character. Returns false if the string
 * pointer is null.
 * 
 * @ingroup char_validation
 * 
 * @param[in] str Null-terminated string to search
 * @param[in] c Character to search for
 * @return true if character is found in string, false otherwise
 */
bool strContains(const char* str, char c) {
	if (str == nullptr) return false;
	while (*str) {
		if (*str == c) return true;
		++str;
	}
	return false;
}

/**
 * @brief Compares two strings for equality
 * 
 * @details Performs character-by-character comparison of two
 * null-terminated C-style strings. Returns true only if both strings
 * are identical in content and length. Returns false if either pointer
 * is null.
 * 
 * @ingroup char_validation
 * 
 * @param[in] str1 First null-terminated string
 * @param[in] str2 Second null-terminated string
 * @return true if strings are equal, false otherwise
 */
bool strCompare(const char* str1, const char* str2) {
	if (str1 == nullptr || str2 == nullptr) return false;
	while (*str1 && *str2) {
		if (*str1 != *str2) return false;
		++str1;
		++str2;
	}
	return *str1 == *str2;
}

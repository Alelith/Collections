/**
 * @file conversion.cpp
 * @brief Implementation of type conversion functions
 * 
 * @author Lilith Estévez Boeta
 * @date 2025-01-28
 */

#include <string>
using std::string;

/**
 * @brief Converts a number to string representation in any base
 * 
 * @details Converts a signed long integer to its string representation
 * in the specified base (2-36). Uses digits 0-9 and letters A-Z for
 * bases above 10. Handles negative numbers with leading minus sign.
 * 
 * @ingroup type_conversion
 * 
 * @param[in] value Integer value to convert
 * @param[in] base Numeric base for conversion (must be 2-36)
 * @return String representation of the number in specified base
 * @retval "" Empty string if base is out of valid range
 */
string baseNumToString(long value, int base) {
	const char* digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if (base < 2 || base > 36) return "";

	bool isNegative = value < 0;
	unsigned int uvalue = isNegative ? -value : value;

	string result;
	do {
		result = digits[uvalue % base] + result;
		uvalue /= base;
	} while (uvalue > 0);

	if (isNegative) result = '-' + result;
	return result;
}

/**
 * @brief Converts an integer to decimal string
 * 
 * @details Converts a signed integer to its decimal (base 10) string
 * representation. Wrapper around baseNumToString for convenience.
 * 
 * @ingroup type_conversion
 * 
 * @param[in] value Integer value to convert
 * @return Decimal string representation of the integer
 */
string intToString(int value) {
	return baseNumToString(value, 10);
}

/**
 * @brief Converts a long integer to decimal string
 * 
 * @details Converts a signed long integer to its decimal (base 10)
 * string representation. Wrapper around baseNumToString for
 * convenience.
 * 
 * @ingroup type_conversion
 * 
 * @param[in] value Long integer value to convert
 * @return Decimal string representation of the long integer
 */
string longToString(long value) {
	return baseNumToString(value, 10);
}

/**
 * @brief Converts a float to string with fixed precision
 * 
 * @details Converts a floating-point number to string with 6 decimal
 * places of precision. Handles special values (NaN, infinity) with
 * appropriate string representations. Correctly formats negative zero.
 * 
 * @ingroup type_conversion
 * 
 * @param[in] value Float value to convert
 * @return String representation with 6 decimal places
 * @retval "nan" If value is Not-a-Number
 * @retval "inf" If value is positive infinity
 * @retval "-inf" If value is negative infinity
 */
string floatToString(float value) {
	if (value != value) return "nan";
	if (value == 1.0f / 0.0f) return "inf";
	if (value == -1.0f / 0.0f) return "-inf";

	bool isNegative = value < 0;
	if (isNegative) value = -value;

	long intPart = static_cast<long>(value);
	float fracPart = value - intPart;

	string result = baseNumToString(intPart, 10);
	if (isNegative && intPart == 0) result = "-" + result;

	result += ".";
	
	for (int i = 0; i < 6; ++i) {
		fracPart *= 10;
		int digit = static_cast<int>(fracPart);
		result += '0' + digit;
		fracPart -= digit;
	}

	return result;
}

/**
 * @brief Converts a double to string with fixed precision
 * 
 * @details Converts a double-precision floating-point number to string
 * with 6 decimal places of precision. Handles special values (NaN,
 * infinity) with appropriate string representations. Correctly formats
 * negative zero.
 * 
 * @ingroup type_conversion
 * 
 * @param[in] value Double value to convert
 * @return String representation with 6 decimal places
 * @retval "nan" If value is Not-a-Number
 * @retval "inf" If value is positive infinity
 * @retval "-inf" If value is negative infinity
 */
string doubleToString(double value) {
	if (value != value) return "nan";
	if (value == 1.0 / 0.0) return "inf";
	if (value == -1.0 / 0.0) return "-inf";

	bool isNegative = value < 0;
	if (isNegative) value = -value;

	long intPart = static_cast<long>(value);
	double fracPart = value - intPart;

	string result = baseNumToString(intPart, 10);
	if (isNegative && intPart == 0) result = "-" + result;

	result += ".";
	
	for (int i = 0; i < 6; ++i) {
		fracPart *= 10;
		int digit = static_cast<int>(fracPart);
		result += '0' + digit;
		fracPart -= digit;
	}

	return result;
}

/**
 * @brief Parses a string to integer
 * 
 * @details Converts a decimal string representation to a signed
 * integer. Handles optional leading sign (+ or -). Stops parsing at
 * first non-digit character. Returns 0 for empty strings.
 * 
 * @ingroup type_conversion
 * 
 * @param[in] str String to parse
 * @return Parsed integer value
 * @retval 0 If string is empty
 */
int stringToInt(const string& str) {
	if (str.empty()) return 0;

	int result = 0;
	int sign = 1;
	size_t i = 0;

	if (str[0] == '-') {
		sign = -1;
		i = 1;
	}
	else if (str[0] == '+')
		i = 1;

	for (; i < str.length(); ++i) {
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + (str[i] - '0');
		else
			break;
	}

	return result * sign;
}

/**
 * @brief Parses a string to long integer
 * 
 * @details Converts a decimal string representation to a signed long
 * integer. Handles optional leading sign (+ or -). Stops parsing at
 * first non-digit character. Returns 0 for empty strings.
 * 
 * @ingroup type_conversion
 * 
 * @param[in] str String to parse
 * @return Parsed long integer value
 * @retval 0 If string is empty
 */
long stringToLong(const string& str) {
	if (str.empty()) return 0;

	long result = 0;
	int sign = 1;
	size_t i = 0;

	if (str[0] == '-') {
		sign = -1;
		i = 1;
	}
	else if (str[0] == '+')
		i = 1;

	for (; i < str.length(); ++i) {
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + (str[i] - '0');
		else
			break;
	}

	return result * sign;
}

/**
 * @brief Parses a string to float
 * 
 * @details Converts a string representation to a float value. Handles
 * optional leading sign, decimal point, and special values ("nan",
 * "inf", "-inf"). Stops parsing at first invalid character.
 * 
 * @ingroup type_conversion
 * 
 * @param[in] str String to parse
 * @return Parsed float value
 * @retval 0.0f If string is empty
 * @retval NaN If string is "nan"
 * @retval +infinity If string is "inf"
 * @retval -infinity If string is "-inf"
 */
float stringToFloat(const string& str) {
	if (str.empty()) return 0.0f;
	if (str == "nan") return 0.0f / 0.0f;
	if (str == "inf") return 1.0f / 0.0f;
	if (str == "-inf") return -1.0f / 0.0f;

	float result = 0.0f;
	float sign = 1.0f;
	size_t i = 0;

	if (str[0] == '-') {
		sign = -1.0f;
		i = 1;
	}
	else if (str[0] == '+')
		i = 1;

	for (; i < str.length() && str[i] != '.'; ++i)
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10.0f + (str[i] - '0');

	if (i < str.length() && str[i] == '.') {
		++i;
		float fraction = 0.1f;
		for (; i < str.length(); ++i) {
			if (str[i] >= '0' && str[i] <= '9') {
				result += (str[i] - '0') * fraction;
				fraction *= 0.1f;
			}
			else
				break;
		}
	}

	return result * sign;
}

/**
 * @brief Parses a string to double
 * 
 * @details Converts a string representation to a double value. Handles
 * optional leading sign, decimal point, and special values ("nan",
 * "inf", "-inf"). Stops parsing at first invalid character.
 * 
 * @ingroup type_conversion
 * 
 * @param[in] str String to parse
 * @return Parsed double value
 * @retval 0.0 If string is empty
 * @retval NaN If string is "nan"
 * @retval +infinity If string is "inf"
 * @retval -infinity If string is "-inf"
 */
double stringToDouble(const string& str) {
	if (str.empty()) return 0.0;
	if (str == "nan") return 0.0 / 0.0;
	if (str == "inf") return 1.0 / 0.0;
	if (str == "-inf") return -1.0 / 0.0;

	double result = 0.0;
	double sign = 1.0;
	size_t i = 0;

	if (str[0] == '-') {
		sign = -1.0;
		i = 1;
	}
	else if (str[0] == '+')
		i = 1;

	for (; i < str.length() && str[i] != '.'; ++i)
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10.0 + (str[i] - '0');

	if (i < str.length() && str[i] == '.') {
		++i;
		double fraction = 0.1;
		for (; i < str.length(); ++i) {
			if (str[i] >= '0' && str[i] <= '9') {
				result += (str[i] - '0') * fraction;
				fraction *= 0.1;
			}
			else
				break;
		}
	}

	return result * sign;
}

/**
 * @brief Converts a character to uppercase
 * 
 * @details Converts a lowercase letter (a-z) to its uppercase
 * equivalent (A-Z). Non-alphabetic characters are returned unchanged.
 * 
 * @ingroup type_conversion
 * 
 * @param[in] c Character to convert
 * @return Uppercase version of character if lowercase, otherwise
 *         unchanged
 */
char toUppercase(char c) {
	if (c >= 'a' && c <= 'z')
		return c - ('a' - 'A');
	return c;
}

/**
 * @brief Converts a character to lowercase
 * 
 * @details Converts an uppercase letter (A-Z) to its lowercase
 * equivalent (a-z). Non-alphabetic characters are returned unchanged.
 * 
 * @ingroup type_conversion
 * 
 * @param[in] c Character to convert
 * @return Lowercase version of character if uppercase, otherwise
 *         unchanged
 */
char toLowercase(char c) {
	if (c >= 'A' && c <= 'Z')
		return c + ('a' - 'A');
	return c;
}

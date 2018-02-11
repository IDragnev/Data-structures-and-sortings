#include "StringHelpFunctions.h"
#include <stdexcept>

bool isDigit(char c)
{
	return (c >= '0' && c <= '9');
}


//
//find the '0'
//then return to the last non-zero symbol
//
void toEnd(const char* &ptr)
{
	while (*ptr)
		ptr++;

	--ptr;
}


//
//while *str is not '0' and is ' '
//move forward
//
void skipSpaces(const char* &str)
{
	while (*str && *str == ' ')
		++str;
}


//
//if not a digit (and not '\0'), move forward
//
void toFirstDigit(const char* &ptr)
{
	while (!isDigit(*ptr) && *ptr)
			ptr++;
}


void toLastDigit(const char* &ptr)
{
	//move to the first non-digit 
	while (isDigit(*ptr) && *ptr)
		ptr++;

	//return to the digit before it
	--ptr;
}


const char* findFirstDigit(const char* ptr)
{
	toFirstDigit(ptr);

	return ptr;
}

const char* findLastDigit(const char* ptr)
{
	toLastDigit(ptr);

	return ptr;
}



//
//find the number of symbols between the two pointers
//including the ends
//
int count(const char* ptr1, const char* ptr2)
{
	int count = 0;

	while (ptr1 <= ptr2)
	{
		count++;
		ptr1++;
	}
	return count;
}


//
//return the length of the string
//
int strLen(const char* str)
{
	if (!str) return 0;

	int len = 0;

	while (*str)
	{
		str++;
		len++;
	}

	return len;
}


//
//copy source to dest
//
// \ if dest is null, and exception is thrown
// \ if source is null, the function does nothing
//
// \ if maxSymbols (to copy) is exceeded by source, and exception is thrown
//
void strCopy(char* dest, size_t maxSymbols, const char* source)
{
	if (!dest) throw std::invalid_argument("Destination buffer cannot be null");
	
	if (source)
	{
		if (maxSymbols < strLen(source) + 1) throw std::invalid_argument("Destination buffer not large enough");

		while (*source)
		{
			*dest = *source;
			dest++; source++;
		}

		*dest = '\0';
	}
}


//
//concatenate two strings
//
// \ if dest is null an exception is thrown
//
// \ if the second string is null, the function does nothing
//
void strCat(char* str1, const char* str2)
{
	if(!str1) throw std::invalid_argument("Destination buffer cannot be null");

	if (str2)
	{
		//move to '0' of str1
		while (*str1)
			str1++;

		//start copying str2 from there
		while (*str2)
		{
			*str1 = *str2;
			str1++; str2++;
		}

		//mark the end
		*str1 = '\0';
	}
}


//
//compare two strings
//
// \ the function assumes both arguments are valid strings
//
int strCmp(const char* str1, const char* str2)
{
	while (*str1)
	{
		if (*str1 != *str2)
			return *str1 - *str2;

		str1++; str2++;
	}

	return *str1 - *str2;
}


bool isUpper(char c)
{
	return (c >= 'A' && c <= 'Z');
}


bool isLower(char c)
{
	return (c >= 'a' && c <= 'z');
}


char toUpper(char c)
{
	if (isLower(c))
		return c - ('a' - 'A');

	return c;
}


char toLower(char c)
{
	if (isUpper(c))
		return c + ('a' - 'A');

	return c;
}


bool isLetter(char c)
{
	return (isUpper(c) || isLower(c));
}


int toInt(char c)
{
	if (isDigit(c))
		return c - '0';

	return c;
}


long long strToInt(const char* str)
{
	if (!str) return 0;

	int sum = 0;

	//skip non-digits
	toFirstDigit(str);

	//to check the sign
	char start = *(str - 1);

	while (isDigit(*str))
	{
		sum *= 10;
		sum += toInt(*str);
		str++;
	}

	if (start == '-')
		sum *= -1;

	return sum;
}


const char* numberToString(long long number)
{
	//if the number is negative, add a char for its sign
	size_t size = (number > 0) ? digitsCount(number) + 1 : digitsCount(number) + 2;

	char* buffer = new char[size] { 0, };

	int i = size - 2;

	//if the number is negative, make it positive
	//and add a minus in the string
	if (number < 0)
	{
		number *= -1;
		buffer[0] = '-';
	}

	while (number > 0)
	{
		buffer[i] = (number % 10) + '0';
		number /= 10;
		--i;
	}

	return buffer;
}


int digitsCount(long long digit)
{
	if (digit < 0)
		digit *= -1;

	int count = 0;

	while (digit > 0)
	{
		digit /= 10;
		count++;
	}

	return count;
}



int digitsCount(const char* string)
{
	if (!string) return 0;

	int count = 0;
	
	while (*string)
	{
		if (isDigit(*string))
			count++;

		string++;
	}

	return count;
}



//
// the function assumes all parameters are valid pointers
//
// \ if start > end, the buffer is left empty with a valid end
//
void copyFromEnds(char* buffer, const char* start, const char* end)
{
	while (start <= end)
	{
		*buffer = *start;
		++start;
		++buffer;
	}

	*buffer = '\0';	
}
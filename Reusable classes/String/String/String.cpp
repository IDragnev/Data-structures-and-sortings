#include "String.h"
#define NULL 0

#include <stdexcept>

//---------------------------------------------------------------
//
//GET AND SET
//

//
//if str is NULL return an empty string
//else return str
//
String::operator char *()
{
	return (str) ? str : "";
}

//
//if str is NULL return an empty string
//else return str
//
const char* String::getValue()const
{
	return (str) ? str : "";
}


String::operator const char *()const
{
	return getValue();
}




//
//if the sent value is NULL 
//free the pointer and set str as NULL
//
//else reconstruct str with the sent value
//
void String::setValue(const char* value)
{
	if (!value)
	{
		delete[] str;
		str = NULL;
		return;
	}

	int size = strLen(value) + 1;
	char* buffer = new char[size];
	strCopy(buffer, size, value);

	delete[] str;
	str = buffer;
}


//
//get the length of the string
//
// 0 if str is NULL, and strLen if not NULL
//
int String::len()const
{
	return (str) ? strLen(str) : 0;
}


//
//get the string as an integer
//
long long String::toDigit()const
{
	return strToInt(str);
}


//----------------------------------------------------------------------------------------------
//
//CTORS
//

//
//holds a NULL value by default
//
String::String()
	:
	str(NULL)
{
	;
}



//
//reconstructs str with the sent value
//
String::String(const char* value)
	:
	str(NULL)
{
	setValue(value);
}


//
//reconstructs str with other's str
//
String::String(const String& other)
	:
	str(NULL)
{
	setValue(other.str);
}



//
//reconstructs str with other's str
//
String& String::operator=(const String& other)
{
	if (this != &other)
		setValue(other.str);
	
	return *this;
}


String& String::operator=(const char* string)
{
	setValue(string);

	return *this;
}


//
//makes a new string with two 'boxes'
//one of which is the symbol
//and the other is '\0'
//
String::String(char c)
	:
	str(NULL)
{
	str = new char[2];
	str[0] = c;
	str[1] = '\0';
}


//
//free str
//
String::~String()
{
	delete[] str;
}



//----------------------------------------------------------------------
//
//OPERATORS
//

bool operator==(const String& s1, const String& s2)
{
	return strCmp(s1, s2) == 0;
}

bool operator!=(const String& s1, const String& s2)
{
	return !(s1 == s2);
}

bool operator>(const String& s1, const String& s2)
{
	return strCmp(s1, s2) > 0;
}


bool operator>=(const String& s1, const String& s2)
{
	return (s1 > s2) || (s1 == s2);
}


bool operator<(const String& s1, const String& s2)
{
	return !(s1 >= s2);
}


bool operator<=(const String& s1, const String& s2)
{
	return !(s1 > s2);
}



//
//if the sent value is NULL, return
//
//else reconstruct str with concatenated string
//
String& String::operator+=(const char* value)
{
	if (!value)
		return *this;

	int len1 = len();
	int len2 = strLen(value);

	int size = len1 + len2 + 1;
	char* buffer = new char[size];

	//copy current str
	strCopy(buffer, size, getValue());
	//'append' value
	strCat(buffer, value);

	delete[] str;
	str = buffer;

	return *this;
}



String operator+(const String& string1, const String& string2)
{
	String temp(string1);

	temp += string2;

	return temp;
}


String operator+(const String& string, const char* str)
{
	String temp(string);

	temp += str;

	return temp;
}



char& String::operator[](int index)
{
	if (index<0 || index >= len())
		throw std::out_of_range("Index out of range");

	return str[index];
}


const char& String::operator[](int index)const
{
	if (index<0 || index >= len())
		throw std::out_of_range("Index out of range");

	return str[index];
}


//
//appends the char to str
//
String& String::operator+=(char c)
{
	//make a temporary string
	String temp(c);

	//if str is NULL
	//just set it with c
	if (!str)
	{
		setValue(temp);
		return *this;
	}
	
	//else append to str
	*this += temp;

	return *this;
}



String operator+(const String& string, char c)
{
	String temp(string);

	temp += c;

	return temp;
}


String operator+(char c, const String& string)
{
	//make a temp. empty string
	String s;

	//append c to it
	s += c;

	//append string
	s += string;

	return s;
}



String operator+(const char* str, const String& string)
{
	String temp(str);

	temp += string;                                         

	return temp;
}



#include "String.h"
#include <stdexcept>
#include <utility>


//---------------------------------------------------------------
//
//GET AND SET
//

//
//if str is nullptr return an empty string
//else return str
//
String::operator char *()
{
	return (str) ? str : "";
}

//
//if str is nullptr return an empty string
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
//if the sent value is nullptr 
//free the pointer and set str as nullptr
//
//else reconstruct str with the sent value
//
void String::setValue(const char* value)
{
	if (!value)
	{
		delete[] str;
		str = nullptr;
		return;
	}

	size_t size = strLen(value) + 1;
	char* buffer = new char[size];
	strCopy(buffer, size, value);

	delete[] str;
	str = buffer;
}


//
//get the length of the string
//
int String::len()const
{
	//strLen handles a null value
	return strLen(str);
}


//----------------------------------------------------------------------------------------------
//
//CTORS
//

//
//holds a null value by default
//
String::String()
	:
	str(nullptr)
{
	;
}



//
//reconstructs str with the sent value
//
String::String(const char* value)
	:
	str(nullptr)
{
	setValue(value);
}


//
//reconstructs str with other's str
//
String::String(const String& other)
	:
	str(nullptr)
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
	str(nullptr)
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


//
//move constructor
//
//transfers source's string to this object
//
String::String(String&& source)
	:
	str(source.str)
{
	source.str = nullptr;
}



//
//move assignment
//
//frees old memory and transfers other's string
//to this object
//
String& String::operator=(String&& other)
{
	if (this != &other)
	{
		delete[] str;

		str = other.str;
		other.str = nullptr;
	}

	return *this;
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
//if the sent value is null, return
//else reconstruct str with concatenated string
//
String& String::operator+=(const char* value)
{
	if (!value)
		return *this;

	size_t size = this->len() + strLen(value) + 1;
	char* buffer = new char[size];

	//copy this->str (could be null) and 'append' value
	strCopy(buffer, size, getValue());
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
	String temp(c);

	//if str is null just set it with c
	if (!str)
	{
		setValue(temp);
	}
	else //else append to it
	{
		*this += temp;
	}

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
	String str(c);

	str += string;

	return str;
}



String operator+(const char* str, const String& string)
{
	String temp(str);

	temp += string;                                         

	return temp;
}



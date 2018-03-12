#include "String.h"
#include <utility>

//---------------------------------------------------------------
//
//GET AND SET
//


const char* String::getValue()const
{
	return (str != nullptr) ? str : "";
}


String::operator const char *()const
{
	return getValue();
}



void String::setValue(const char* value)
{
	if (!value)
	{
		delete[] str;
		str = nullptr;
	}
	else
	{
		size_t size = strlen(value) + 1;
		char* buffer = new char[size];
		strcpy_s(buffer, size, value);

		delete[] str;
		str = buffer;
	}
}



size_t String::len()const
{
	return (str != nullptr) ? strlen(str) : 0;
}



void String::appendToValue(const char* value)
{
	if (value)
	{
		size_t size = strlen(value);

		//if not empty
		if (size > 0)
		{
			size += (this->len() + 1);
			char* buffer = new char[size];

			//getValue() because str could be null
			strcpy_s(buffer, size, getValue());
			strcat_s(buffer, size, value);

			delete[] str;
			str = buffer;
		}
	}
}


//----------------------------------------------------------------------------------------------
//
//CTORS
//



String::String()
	:
	str(nullptr)
{
	;
}


String::String(const char* value)
	:
	str(nullptr)
{
	setValue(value);
}


String::String(const String& other)
	:
	str(nullptr)
{
	setValue(other.str);
}



String::String(char c)
	:
	str(nullptr)
{
	str = new char[2];
	str[0] = c;
	str[1] = '\0';
}



String::~String()
{
	delete[] str;
}



//
//move constructor
//
String::String(String&& source)
	:
	str(source.str)
{
	source.str = nullptr;
}




//
// combined operator= taking by value and using the copy-and-swap idiom
//
// \ if rhs is an rvalue, 'other' will be initialized with move c-tor
//
// \ if rhs is an lvalue, 'other' will be copy-constructed which is fine
//   because we would have to reconstruct other's str anyway
//
// \ if rhs is const char*, 'other' will be constructed with String(const char*)
//   which is fine again, because we would have to reconstruct this->str anyway
//
// After constructing 'other' with rhs, data is swapped and 'other' destroys old data.
//
//String& String::operator=(String other)
//{
//	std::swap(this->str, other.str);
//
//	return *this;
//}
//



//
// (!) setValue frees old memory (if any)
//
String& String::operator=(const String& other)
{
	if (this != &other)
	{
		setValue(other.str);
	}

	return *this;
}



//
//move assignment, can be called for rvalues only 
//(including const char* which will move-construct an rvalue object)
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
	return strcmp(s1, s2) == 0;
}

bool operator!=(const String& s1, const String& s2)
{
	return !(s1 == s2);
}

bool operator>(const String& s1, const String& s2)
{
	return strcmp(s1, s2) > 0;
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





String& String::operator+=(const char* value)
{
	appendToValue(value);

	return *this;
}


String operator+(const String& lhs, const String& rhs)
{
	String result(lhs);

	result += rhs;

	return result;
}


String operator+(const String& lhs, const char* rhs)
{
	String result(lhs);

	result += rhs;

	return result;
}



String& String::operator+=(char c)
{
	static char temp[2];

	temp[0] = c;
	temp[1] = '\0';
	
	appendToValue(temp);

	return *this;
}



String operator+(const String& lhs, char rhs)
{
	String result(lhs);

	result += rhs;

	return result;
}


String operator+(char lhs, const String& rhs)
{
	String result(lhs);

	result += rhs;

	return result;
}



String operator+(const char* lhs, const String& rhs)
{
	String result(lhs);

	result += rhs;

	return result;
}



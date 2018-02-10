#ifndef __STRING_H_INCLUDED__
#define __STRING_H_INCLUDED__

#include "StringHelpFunctions.h"

class String
{
public:
	String();                                 
	String(char);                            
	String(const char* value);
	String(const String&);
	~String();

	String& operator=(const String& other);
	String& operator=(const char*);

	operator char*();
	operator const char*()const;

	int len()const;                          

	String& operator+=(const char*);          
	String& operator+=(char);

	long long toDigit()const;

	char& operator[](int);
	const char& operator[](int)const;

private:
	char* str;

private:
	const char* getValue()const;           
	void setValue(const char*);               
};


String operator+(const String&, char);
String operator+(char, const String&);
String operator+(const String&, const String&);
String operator+(const char*, const String&);
String operator+(const String&, const char*);

bool operator==(const String& s1, const String& s2); 
bool operator!=(const String& s1, const String& s2);
bool operator>(const String& s1, const String& s2);  
bool operator>=(const String& s1, const String& s2);
bool operator<(const String& s1, const String& s2); 
bool operator<=(const String& s1, const String& s2);

#endif // __STRING_H_INCLUDED__
#ifndef __STRING_HELPERS_H_INCLUDED__
#define __STRING_HELPERS_H_INCLDUED__

int strLen(const char*);                                          //get the length of a string
int strCmp(const char*, const char*);                             //compare two strings
void strCopy(char* dest,size_t destSize, const char* source);     //copy source into dest
void strCat(char*, const char*);                                  //concatenate two strings

bool isLetter(char);                                              //is the symbol a letter
bool isUpper(char);                                               //is the symbol a capital letter 
bool isLower(char);                                               //is the symbol a lower letter
bool isDigit(char);                                               //is the symbol a digit

char toUpper(char);                                               //get the upper of the symbol passed
char toLower(char);                                               //get the lower of the symbol passed

void toEnd(const char* &ptr);                                     //move the pointer to the end of the string (before '\0')

int digitsCount(long long);                                       //return the number of the digits in a number
int digitsCount(const char*);                                     //return the number of the digits in a string

void toFirstDigit(const char* &ptr);                              //move the pointer to the first digit in the string
void toLastDigit(const char* &ptr);                               //move the pointer to the last digit in the string

const char* findFirstDigit(const char*);                          //return the address of the first digit in the string passed
const char* findLastDigit(const char*);                           //return the address of the last digit in the passed string

int count(const char* start, const char* end);                    //get the number of symbols between start and end

void skipSpaces(const char* &str);                                //skip spaces in a string

void copyFromEnds(char* buffer, const char* start, const char* end);  //copy the symbols from start to end to buffer

const char* numberToString(long long);                            //return the number converted to a string
int toInt(char);                                                  //return the symbol converted to an integer(only works for digits)
long long strToInt(const char* numberStr);                        //return the passed string to a integer(should be a number)

#endif //__STRING_HELPERS_H_INCLUDED__
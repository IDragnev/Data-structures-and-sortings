#include <iostream>
#include "String.h"

int main()
{
	String str;
	String another("ale");

	str = String("some temp");

	str = "do sth";

	str += "asd";

	str += 'A';

	str = another;

	std::cout << 'c' + String("asd") << std::endl;
	std::cout << "asd" + String('c') << std::endl;
	std::cout << "asd" + str << std::endl;

	return 0;
}
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

	return 0;
}
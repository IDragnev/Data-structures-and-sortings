#include <iostream>

#include "DynamicArray.h"


int main()
{
	try 
	{
		std::cout << "Making an empty int array..\n";

		DynamicArray<int> arr;

		std::cout << arr << std::endl;

		std::cout << "Filling it with 1,2, .. , 19 \n";

		for (int i = 0; i < 20; ++i)
			arr += i;

		std::cout << "Result: \n";

		std::cout << arr << std::endl;

		std::cout << "\nRemoving 1,4,7,10 and 13 : \n";

		for (int i = 1; i < arr.getCount(); i += 3)
			arr.remove(i);

		std::cout << arr << std::endl;

		std::cout << "\nMaking another array with copy: \n";
		DynamicArray<int> arr2(arr);

		std::cout << arr2 << std::endl;

		std::cout << "\nAdding some integers to it...\n\nResult: \n";

		for (int i = 10; i < 50; i += 8)
			arr2 += i;

		std::cout << arr2 << std::endl;

		std::cout << "\nAssigning array2 = array1. \n\nResult: \n";

		arr2 = arr;

		std::cout << arr2 << std::endl;

		std::cout << "\narr1 + arr2 :\n";

		std::cout << arr + arr2 << std::endl;
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	return 0;
}
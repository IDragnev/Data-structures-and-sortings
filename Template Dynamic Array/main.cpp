#include <iostream>

#include "DynamicArray.h"
#include "OrderedDynamicArray.h"

int DynArrTest()
{
	try
	{
		std::cout << "Making an empty int array..\n";

		DynamicArray<int> arr;

		std::cout << arr << std::endl;

		std::cout << "Filling it with 0,1,2, .. , 19 \n";

		for (int i = 0; i < 20; ++i)
			arr += i;

		std::cout << "Result: \n";

		std::cout << arr << std::endl;

		std::cout << "\nRemoving from positions 1,4,7,10 and 13 : \n";

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

		std::cout << "\nAdding 999 at the position 2 of arr1 (should be third) : \n";
		arr.addAt(999, 2);

		std::cout << arr << std::endl;


		std::cout << "\narr + 1000 :\n";
		std::cout << arr + 1000 << std::endl;

		std::cout << "\n666 + arr :\n";
		std::cout << 666 + arr << std::endl;

	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	return 0;
}
int OrderedDynArrTest()
{
	try
	{
		std::cout << "Making an empty int ordered array..\n";

		OrderedDynamicArray<int> arr;

		std::cout << arr << std::endl;

		std::cout << "Filling it with 0,1,2, .. , 19 \n";

		for (int i = 0; i < 20; ++i)
			arr += i;

		std::cout << "Result: \n";

		std::cout << arr << std::endl;

		std::cout << "\nRemoving pos 1: \n";

		arr.remove(1);

		std::cout << arr << std::endl;

		std::cout << "\nRemoving pos 4: \n";

		arr.remove(4);

		std::cout << arr << std::endl;

		std::cout << "\nRemoving pos 9: \n";

		arr.remove(9);

		std::cout << arr << std::endl;

		std::cout << "\nMaking another ordered array with copy: \n";
		OrderedDynamicArray<int> arr2(arr);

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


		std::cout << "\narr + 1000 :\n";
		std::cout << arr + 1000 << std::endl;

		std::cout << "\n666 + arr :\n";
		std::cout << 666 + arr << std::endl;
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	return 0;
}


int main()
{
	return OrderedDynArrTest();
}
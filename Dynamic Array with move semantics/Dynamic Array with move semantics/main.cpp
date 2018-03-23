#include <iostream>
#include "DArray.h"


DArray<int> duplicate(const DArray<int>& arr)
{
	DArray<int> copy(arr);

	return copy;
}


int main()
{
	DArray<int> arr;

	for (int i = 0; i < 10; ++i)
		arr.insert(i);

	DArray<int> arr2(10);

	for (int i = 10; i < 15; ++i)
		arr2.insert(i);

	arr.insert(std::move(arr2));

	DArray<int> arr3;

	arr3 = duplicate(arr);


	return 0;
}
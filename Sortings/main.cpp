#include <iostream>
#include <stdlib.h>
#include <random>
#include <ctime>

#include "../Template Dynamic Array/DynamicArray.h"

//sortings 
#include "MergeSort.h"
#include "InsertionSort.h"
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "ShakerSort.h"

int main()
{
	srand(time(NULL));

	try
	{
		std::cout << "\nHow many elements to sort ? \n";

		int x;
		std::cin >> x;

		DynamicArray<int> arr(x);

		for (int i = 0; i < x; ++i)
		{
			arr.add(rand() % 1000);
		}

		time_t beg = time(NULL);

		//insertionSort(arr, 0, arr.getCount() - 1);
		//mergeSort(arr, 0, arr.getCount() - 1);
		//selectionSort(arr, 0, arr.getCount() - 1);
		//bubbleSort(arr, 0, arr.getCount() - 1);
		shakerSort(arr, 0, arr.getCount() - 1);

		time_t end = time(NULL);

		std::cout << "\nSorted for " << end - beg << " seconds!\n";

		std::cout << "\nResult: \n";
		std::cout << arr << std::endl;
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}


	return 0;
}
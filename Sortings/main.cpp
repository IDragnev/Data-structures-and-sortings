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
#include "QuickSort.h"
#include "ShellSort.h"
#include "SelectionMethod.h"
#include "CountingSort.h"
#include "HeapSort.h"

void fillRandomly(DynamicArray<int>& arr, int gap)
{
	int size = arr.getSize();

	for (int i = 0; i < size; ++i)
	{
		arr.add(rand() % gap);
	}
}

int main()
{
	srand(time(NULL));

	try
	{
		int x;
		int gap;

		std::cout << "\nHow many elements to sort ? \n";
		std::cin >> x;

		std::cout << "\nUp to which number? \n";
		std::cin >> gap;

		DynamicArray<int> arr(x);

		fillRandomly(arr, gap);
		
		time_t beg = time(NULL);

		//insertionSort(arr, 0, arr.getCount() - 1);
		//selectionSort(arr, 0, arr.getCount() - 1);
		//bubbleSort(arr, 0, arr.getCount() - 1);
		//shakerSort(arr, 0, arr.getCount() - 1);
		//shellSort(arr, 0, arr.getCount() - 1);
		//quickSort(arr, 0, arr.getCount() - 1);
		//recursiveSelect(arr, 0, arr.getCount() - 1, 5);
		//iterativeSelect(arr, 0, arr.getCount() - 1, 5);
		//mergeSort(arr, 0, arr.getCount() - 1);
		//countingSort(arr, 0, gap);

		HeapSort<int> sorter;
		sorter.sort(arr, 1, 15);

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
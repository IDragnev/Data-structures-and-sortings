#include "../Template Dynamic Array/DynamicArray.h"


template <typename T>
void bubbleSort(DynamicArray<T> &arr, int beg, int end)
{
	//the end of the sorted subarray 
	//(initially the one before the first element)
	int sorted = beg - 1;

	bool isChanged = true;

	//while not sorted
	while (isChanged)
	{
		isChanged = false;

		//do one pass of bubble sort

		//from the penult element down to the last before the sorted subarray
		for (int current = end - 1; current > sorted; --current)
		{
			//if current is greater than the one after it 
			if (arr[current] > arr[current + 1])
			{
				//swap them
				std::swap(arr[current], arr[current + 1]);

				//mark the change
				isChanged = true;
			}
		}

		//update the sorted subarray
		++sorted;
	}
}
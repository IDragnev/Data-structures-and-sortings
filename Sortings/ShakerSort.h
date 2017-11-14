#include "../Template Dynamic Array/DynamicArray.h"

template <typename T>
void shakerSort(DynamicArray<T> &arr, int start, int end)
{
	//the flag
	bool swapped = true;

	while (swapped)
	{
		//reset flag
		swapped = false;

		//bubble sort from left to right
		for (int i = start; i < end; ++i)
		{
			if (arr[i] > arr[i + 1])
			{
				std::swap(arr[i], arr[i + 1]);
				swapped = true;
			}
		}

		// if nothing moved the array is sorted.
		if (!swapped) break;

		// otherwise reset the flag
		swapped = false;

		//update the right sorted subarray
		--end;

		//bubble sort from right to left
		for (int i = end - 1; i >= start; --i)
		{
			if (arr[i] > arr[i + 1])
			{
				std::swap(arr[i], arr[i + 1]);
				swapped = true;
			}
		}

		//update left sorted subarray
		++start;
	}
}

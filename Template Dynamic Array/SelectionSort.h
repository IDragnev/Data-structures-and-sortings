#include "DynamicArray.h"

template <typename T>
void selectionSort(DynamicArray<T> &arr, int beg, int end)
{
	//from the first to the one before the last
	for (int sorted = beg; sorted < end; ++sorted)
	{
		//the index of the min. element
		//(which is the current)
		int min = sorted;

		//from the next element to the end
		//search for the smallest element in the 
		//subarray arr[sorted + 1, ... , end] which is also
		//smaller than arr[sorted]
		for (int current = sorted + 1; current <= end; ++current)
		{
			//if the current is smaller than the min.
			if (arr[min] > arr[current])
			{ 
				//change the index of the min. element
				min = current;
			}
		}

		//if there was such element
		if (min != sorted)
		{
			//swap them
			std::swap(arr[min], arr[sorted]);
		}
	}
}
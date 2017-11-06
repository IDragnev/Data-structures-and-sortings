#include "DynamicArray.h"
 
template <typename T>
void bubbleSort(DynamicArray<T> &arr, int beg, int end)
{
	//from the first element to the last
	for (int sorted = beg; sorted <= end; ++sorted)
	{
		//from the last to the end of the sorted subarray
		for (int current = end; current > sorted; current--)
		{
			//if the current is smaller than the one before it
			if (arr[current] < arr[current - 1])
			{
				//swap them
				std::swap(arr[current], arr[current - 1]);
			}
		}
	}
}
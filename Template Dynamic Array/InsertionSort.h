#include "DynamicArray.h"

template <typename T>
void insertionSort(DynamicArray<T> &arr, int beg, int end)
{
	//from the second element to the last
	for (int i = beg + 1; i <= end; ++i)
	{
		//mark the key value
		T key = arr[i];

		//from the one before it
		int j = i - 1;

		//while the current element is greater
		//than the key element, shift it 1 pos. to the right
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			--j;
		}

		//insert the key in its place
		arr[j + 1] = key;
	}
}

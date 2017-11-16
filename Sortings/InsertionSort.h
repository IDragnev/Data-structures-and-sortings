#include "../Template Dynamic Array/DynamicArray.h"

template <typename T>
void insertionSort(DynamicArray<T> &arr, int beg, int end)
{
	//put the min. element in front
	//by doing 1 pass of bubble sort
	for (int i = end; i > beg; --i)
	{
		if (arr[i] < arr[i - 1])
			std::swap(arr[i], arr[i - 1]);
	}


	//from the third element to the last
	for (int i = beg + 2; i <= end; ++i)
	{
		//mark the key value
		//in order to 'empty' the spot
		T key = arr[i];

		//the empty spot
		int j = i;

		//while the current element is greater
		//than the key element, shift it 1 pos. to the right
		while (arr[j - 1] > key)
		{
			arr[j] = arr[j - 1];
			--j;
		}

		//insert the key in its place
		arr[j] = key;
	}
}

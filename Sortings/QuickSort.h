#include "../Template Dynamic Array/DynamicArray.h"



//
//the auxiliary operation
//
template <typename T>
int partition(DynamicArray<T>& arr, int beg, int end)
{
	//the pivot
	T &pivot = arr[end];

	int i = beg - 1; 

	//from the first element to the pivot
	for (int j = beg; j < end; ++j)
	{
		//if the current element is not greater
		//than the pivot
		if (arr[j] <= pivot)
		{
			//increment left part
			++i;

			//put the current in the left part
			if(i != j)
				std::swap(arr[i], arr[j]);
		}
		//move to the next element
	}

	//put the pivot between the two parts
	std::swap(arr[i + 1], arr[end]);

	//and return its location
	return (i + 1 != end) ? (i + 1) : (beg + end) / 2;
}


template <typename T>
void quickSort(DynamicArray<T>& arr, int beg, int end)
{
	//if more than one element
	if (beg < end)
	{
		//get the location of the pivot
		int middle = partition(arr, beg, end);

		//sort left part recursively
		quickSort(arr, beg, middle - 1);

		//sort right part recursively
		quickSort(arr, middle + 1, end);
	}
}
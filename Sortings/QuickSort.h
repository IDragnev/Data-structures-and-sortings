#include "../Template Dynamic Array/DynamicArray.h"

template <typename T>
void insertionSort(DynamicArray<T> &arr, int beg, int end);

template <typename T>
void swapif(T& a, T& b)
{
	if (b < a)
		std::swap(a, b);
}



template <typename T>
void quickSort(DynamicArray<T>& arr, int beg, int end)
{
	int size = end - beg + 1;

	if (size > 1)
	{
		if (size < 25)
		{
			return insertionSort(arr, beg, end);
		}
		else 
		{
			// median-of-3 with beg, end and middle
			int middle = size / 2;
			swapif(arr[beg], arr[middle]);
			swapif(arr[beg], arr[end]);
			swapif(arr[middle], arr[end]);
		
			//put the pivot in the penult position
			//because arr[end] is bigger than it
			//and there is no need to include it in the partitioning
			std::swap(arr[middle], arr[end - 1]);

			//partition without the most left and right elements
			int pivot = partition(arr, beg + 1, end - 1);

			//sort left part recursively
			quickSort(arr, beg, pivot - 1);

			//sort right part recursively
			quickSort(arr, pivot + 1, end);
		}
	}
}




	
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
			if (i != j)
				std::swap(arr[i], arr[j]);
		}
		//move to the next element
	}

	//put the pivot between the two parts
	std::swap(arr[i + 1], arr[end]);

	//and return its location
	return (i + 1 != end) ? (i + 1) : (beg + end) / 2;
}
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
			//get the location of the pivot
			int middle = partition(arr, beg, end);

			//sort left part recursively
			quickSort(arr, beg, middle - 1);

			//sort right part recursively
			quickSort(arr, middle + 1, end);
		}
	}
}



//
//the auxiliary operation
//
template <typename T>
int partition(DynamicArray<T> &arr, int beg, int end)
{
	int size = end - beg + 1;

	assert(size >= 3);

	// median-of-3 with beg, end and middle
	int middle = size / 2;
	swapif(arr[beg], arr[middle]);
	swapif(arr[beg], arr[end]);
	swapif(arr[middle], arr[end]);

	//put the pivot in the penult position
	//because arr[end] is bigger than it
	//and there is no need to include it in the partitioning
	std::swap(arr[middle], arr[end - 1]);

	//the pivot
	T &pivot = arr[end - 1];

	//now partition the array without 
	//including the most left and right elements
	//because they were already sorted with pivot
	int left = beg + 1;   //++beg;
	int right = end - 1;  //--end;

	//the [ x <= pivot ] part
	int i = left - 1;
	
	//from the most left to the pivot
	for (int j = left; j < right; ++j)
	{
		//if x <= pivot
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
	std::swap(arr[i + 1], arr[right]);

	//and return its location
	return (i + 1 != right) ? (i + 1) : (left + right) / 2;
}

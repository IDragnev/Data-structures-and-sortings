#include "../Template Dynamic Array/DynamicArray.h"

//
// merge two parts of an array:
//
// left part -> arr[beg, ... , middle]
// right part -> arr[middle+1, ... , end]
//
template <typename T>
void merge(DynamicArray<T> &arr, int beg, int middle, int end)
{
	// the beginning of the left part
	int leftArr = beg;

	// the beginning of the right part 
	int rightArr = middle + 1;

	int size = end - beg + 1;

	//the new array (to be filled sorted)
	DynamicArray<T> buffer(size);

	//while at least one of the parts is not empty
	while (leftArr <= middle || rightArr <= end)
	{
		//while the left part is not empty AND 
		//the right part is empty OR the left part's element is smaller
		//write to the sorted array and move forward in the left part
		while (leftArr <= middle && (rightArr > end || arr[leftArr] < arr[rightArr]))
		{
			buffer.add(arr[leftArr++]);
		}

		//while the right part is not empty AND
		//the left part is empty OR the right part's element is smaller or equal
		//write to the sorted array and move forward in the right part
		while (rightArr <= end && (leftArr > middle || arr[rightArr] <= arr[leftArr]))
		{
			buffer.add(arr[rightArr++]);
		}
	}

	//copy back to arr
	for (int i = 0; i < size; ++i)
	{
		arr[beg + i] = buffer[i];
	}
}


//
//sorts the subarray arr[beg, ... , end]
//by splitting it in two halves :
//
// arr[beg, .. , middle] ^ arr[middle + 1, ... end]
// which are then sorted recursively 
//
//then the two halves are merged toghether
//in the subarray arr[beg, ... , end]
//
template <typename T>
void mergeSort(DynamicArray<T> &arr, int beg, int end)
{
	//if more than one element
	if (beg < end)
	{
		//find the middle
		int middle = (beg + end) / 2;

		//sort the left part
		mergeSort(arr, beg, middle);

		//sort the right part
		mergeSort(arr, middle + 1, end);

		//merge them in the subarray
		merge(arr, beg, middle, end);
	}
}

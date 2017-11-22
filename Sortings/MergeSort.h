#include "../Template Dynamic Array/DynamicArray.h"

template <typename T>
void insertionSort(DynamicArray<T> &arr, int beg, int end);

//
// merge two (sorted!) parts of an array:
//
// left part -> arr[beg, ... , middle]
// right part -> arr[middle+1, ... , end]
//
template <typename T>
void simpleMerge(DynamicArray<T> &arr, int beg, int middle, int end)
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
// merge two (sorted!) parts of an array:
//
// left part -> arr[beg, ... , middle]
// right part -> arr[middle+1, ... , end]
//
//by first putting them in an auxiliary array
//but putting the right part in reverse order
//in order to make some kind of sentinels
//this way
//
template <typename T>
void bitonicMerge(DynamicArray<T> &arr, int beg, int middle, int end)
{
	int size = end - beg + 1;

	//the auxiliary array
	DynamicArray<T> aux(size);
	
	//copy left part in its original order                                            //because the right part is coppied in reverse order in the aux
	for (int i = beg; i <= middle; ++i)                                               //the biggest element in the array will lie 'between' the two parts
		aux += arr[i];                                                                //thus acting as a sentinel once reached by one of the parts
																					  //and the checking for emptiness of either parts is not needed!
	//copy right part in reverse order                                                //[1][2][3][10][12][15]  [17][9][8][4][3][0]
	for (int j = end; j > middle; --j)                                                //once the sentinel is reached, the part in which it was
		aux += arr[j];                                                                //is empty and all the copies will be made from the other part
	
	//the smallest element of the left part             
	int leftPart = 0;
	//the smallest element of the right part
	int rightPart = aux.getCount() - 1;
	
	//from the first element to the last
	for (int current = beg; current <= end; ++current)
	{
		//if the left part's smallest element is smaller or equal
		//to the right part's smallest element
		if (aux[leftPart] <= aux[rightPart])
		{
			//write it and move forward in the left part
			arr[current] = aux[leftPart++];
		}
		else
		{
			//write the right part's min. element
			//and move left in the right part
			arr[current] = aux[rightPart--];
		}
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
	int size = end - beg + 1;
	
	//if more than one element
	if (size > 1)
	{
		if (size < 25)
		{
			return insertionSort(arr, beg, end);
		}
		else
		{
			//find the middle
			int middle = (beg + end) / 2;

			//sort the left part
			mergeSort(arr, beg, middle);

			//sort the right part
			mergeSort(arr, middle + 1, end);

			//merge them in the subarray
			bitonicMerge(arr, beg, middle, end);
		}
	}
}

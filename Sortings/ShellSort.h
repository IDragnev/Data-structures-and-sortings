#include "../Template Dynamic Array/DynamicArray.h"


template <typename T>
void shellSort(DynamicArray<T>& arr, int beg, int end)
{
	//the step
	int h = 1;

	//the size of the subarray
	int size = end - beg + 1;

	//find the biggest number of the sequence
	//that will fit the size
	while (h < size / 9)      
		h = 3 * h + 1;

	//for each h in the sequence
	for (; h > 0; h /= 3)           // h /= 3; does the same job as h = (h-1) / 3;
	{
		//sort the h-subarray
		for (int i = beg + h; i <= end; i++)
		{
			//save the value of the key element
			T key(arr[i]);

			//the empty spot
			int j = i;

			//insert. sort the h-subarray
			while (j >= beg + h && key < arr[j - h])
			{
				arr[j] = arr[j - h];
				j -= h;
			}

			//insert it in its place
			arr[j] = key;
		}
	}
}

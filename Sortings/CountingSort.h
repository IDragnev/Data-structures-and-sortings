#include "../Template Dynamic Array/DynamicArray.h"


//
//sort an integer array such that  a <= arr[i] <= b for each i 
//
void countingSort(DynamicArray<int>& arr, int smallest, int biggest)
{
	//the interval : [smallest, ... , biggest]
	//the size of the interval
	int size = biggest - smallest + 1;

	//the array in which  we will count the times
	//an integer from the interval was found in the original array
	int* timesFound = new int[size] {0, };

	//the size of the array-to-be-sorted
	int stop = arr.getCount();

	//count the times an integer from the interval
	//is found in the array
	for (int i = 0; i < stop; ++i)
		++timesFound[arr[i] - smallest];                    // timesFound[smallest - smallest] = timesFound[0] ,  timesFound[biggest - smallest] = timesFound[n], ...

	int pos = 0;
	//for each integer in the interval (in timesFound)
	for (int i = 0; i < size; ++i)
	{
		//write the integer from the interval in the array
		//exactly the times it was found 
		for (int count = 0; count < timesFound[i]; ++count)
		{
			//write it and move to the next position
			arr[pos++] = i + smallest;                        // i + smallest regenerates the integer from the interval:  0 + smallest = smallest, n + smallest = biggest, ...   
		}
	}

	delete[] timesFound;
}
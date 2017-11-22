#include "../Template Dynamic Array/DynamicArray.h"


template <typename T>
int partition(DynamicArray<T>& arr, int beg, int end);

//
//partition the array around the element arr[position]
//such that each element before it is <=
//and each element after it is >=
//but the array may not be sorted
//
template <typename T>
void recursiveSelect(DynamicArray<T>& arr, int beg, int end, int position)
{
	if (beg > end) return;

	//partition around element arr[i]
	int i = partition(arr, beg, end);

	//if the partition element's position is the one we wanted we are done

	//if we partitioned the array around a smaller position
	//we should work on the right subarray
	if (i < position)
	{
		return recursiveSelect(arr, i + 1, end, position);
	}
	//else if we partitioned it around a bigger position
	//we should work on the left subarray
	else if (i > position)
	{
		return recursiveSelect(arr, beg, i - 1, position);
	}
}


//
//partition the array around the element arr[position]
//such that each element before it is <=
//and each element after it is >=
//but the array may not be sorted
//
template <typename T>
void iterativeSelect(DynamicArray<T>& arr, int beg, int end, int position)
{
	while (end > beg)
	{
		//partition around element arr[i]
		int i = partition(arr, beg, end);

		//if we partitioned it around a bigger position 
		//we should work on the left subarray
		if (i >= position)	
			end = i - 1;

		//if we partitioned the array around a smaller position
		//we should work on the right subarray
		if (i <= position)
			beg = i + 1;

		//if the position we seek was matched by partition
		//beg will become greater than end
		//and the loop will end
	}
}
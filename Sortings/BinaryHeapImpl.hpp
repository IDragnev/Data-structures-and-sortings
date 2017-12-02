

//
//sift the specified node
//down the tree until the heap property holds
//
template <typename T>
void siftDown(DynamicArray<T>& arr, int position, int bottom)
{
	T hand = arr[position];

	//while there are children for the current node
	while (2 * position < bottom - 1)
	{
		//find left child
		int maxChild = 2 * position + 1;

		//if there is another child and it is greater
		if (maxChild < bottom - 1 && arr[maxChild + 1] > arr[maxChild])
			++maxChild;  //go to the right child

		//if not out of the tree
		if (maxChild < bottom)
		{
			//if the greater child is greater than the hand
			if (hand < arr[maxChild])
			{
				//move the child up
				arr[position] = arr[maxChild];

				//go down to the child's position
				position = maxChild;
			}
			else //the heap property holds and this is its right position
				break;
		}
	}

	//put it in its right position
	arr[position] = hand;
}



//
//build a heap on a dynamic array
//
template <typename T>
void buildHeap(DynamicArray<T>& arr)
{
	int size = arr.getCount();
	
	//from the first non-leaf to the root of the tree
	for (int i = size / 2; i >= 0; --i)
	{
		//sift it down on its correct position
		siftDown(arr, i, size);
	}
}



template <typename T>
void heapSort(DynamicArray<T>& arr)
{
	//build a heap on it
	buildHeap(arr);

	int size = arr.getCount();

	//from the last leaf to the first child of the root
	for (int i = size - 1; i > 0; --i)
	{
		//swap the max element (the root) with the last leaf
		std::swap(arr[0], arr[i]);

		//sift the leaf down
		siftDown(arr, 0, i);
		
		//i is decremented to the last leaf again...
	}
}
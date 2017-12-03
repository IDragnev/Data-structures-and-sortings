#include "../Template Dynamic Array/DynamicArray.h"


template <typename T>
class HeapSort
{
public:
	void sort(DynamicArray<T>& arr, int beg, int end);

private:
	void heapSort(DynamicArray<T>& arr);
	void buildHeap(DynamicArray<T>& arr);
	void siftDown(DynamicArray<T>& arr, int position);

private:
	int root;
	int last;
};



template <typename T>
void HeapSort<T>::sort(DynamicArray<T>& arr, int beg, int end)
{
	this->root = beg;
	this->last = end;

	heapSort(arr);
}


template <typename T>
void HeapSort<T>::heapSort(DynamicArray<T>& arr)
{
	//build a heap on it
	buildHeap(arr);

	//from the last leaf to the first child of the root
	while (last > root)
	{
		//swap the max element (the root) with the last leaf
		//and decrement the leaves of the tree
		std::swap(arr[root], arr[last--]);

		//sift the new root down
		siftDown(arr, root);
	}
}


//
//build a heap on a dynamic array
//
template <typename T>
void HeapSort<T>::buildHeap(DynamicArray<T>& arr)
{
	int firstNonLeaf = root + ((last - root + 1) / 2) - 1;

	//from the first non-leaf to the root of the tree
	for (int i = firstNonLeaf; i >= root; --i)
	{
		//sift it down to its correct position
		siftDown(arr, i);
	}
}



//
//sift the specified node
//down the tree until the heap property holds
//
template <typename T>
void HeapSort<T>::siftDown(DynamicArray<T>& arr, int position)
{
	T hand = arr[position];

	//left child = 2 * position - root + 1;

	//while there are children for the current node
	while (2 * position - root < last)
	{
		//find left child
		int maxChild = 2 * position - root + 1;

		//if there is another child and it is greater
		if (maxChild < last && arr[maxChild + 1] > arr[maxChild])
			++maxChild;  //go to the right child

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

	//put it in its right position
	arr[position] = hand;
}




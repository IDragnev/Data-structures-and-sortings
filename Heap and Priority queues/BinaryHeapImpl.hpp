

namespace BinaryHeap
{

	template <typename T, typename Function>
	BinaryHeap<T, Function>::BinaryHeap(const Function& compare, int size)
		:
		compareFn(compare),
		elements(size)
	{
		;
	}



	template <typename T, typename Function>
	void siftDown(BinaryHeap<T, Function>& heap, int position)
	{
		DynamicArray<T>& arr = heap.elements;
		
		//the last node in the heap
		int last = arr.getCount() - 1;
	
		T hand = arr[position];

		//while there are children for the current node
		while (2 * position < last)
		{
			//find left child
			int maxChild = 2 * position + 1;

			//if there is another child and it is greater
			if (maxChild < last && heap.compareFn(arr[maxChild], arr[maxChild + 1]))
				++maxChild;  //go to the right child

			//if the greater child is greater than the hand
			if (heap.compareFn(hand, arr[maxChild]))
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



	template <typename T, typename Function>
	void siftUp(BinaryHeap<T, Function>& heap, int position)
	{
		DynamicArray<T>& arr = heap.elements;	

		T hand = arr[position];

		//until the root is reached
		while (position > 0)
		{
			int parent = (position - 1) / 2;

			//if its parent is not greater than the hand
			if (heap.compareFn(arr[parent], hand))
			{
				//pull it down
				arr[position] = arr[parent];

				//and move up the heap
				position = parent;
			}
			else //the heap property holds
				break;
		}

		//put it in its correct position
		arr[position] = hand;	
	}



	template <typename T, typename Function>
	void buildHeap(BinaryHeap<T, Function>& heap)
	{
		//from the first non-leaf to the root
		for (int i = (heap.elements.getCount() - 2) / 2; i >= 0; --i);
		{
			//sift it down to its correct position
			siftDown(heap, i);
		}
	}


	template <typename T, typename Function>
	T peekOptimal(const BinaryHeap<T, Function>& heap)
	{
		return heap.elements[0];
	}


	template <typename T, typename Function>
	T extractOptimal(BinaryHeap<T, Function>& heap)
	{
		DynamicArray<T>& arr = heap.elements;

		//save the optimal element
		T optimal = arr[0];

		//swap the root with the last element
		std::swap(arr[0], arr[arr.getCount() - 1]);
		
		//and remove the ex-root
		arr.remove(arr.getCount() - 1);

		//sift the new root to its correct position
		siftDown(heap, 0);

		return optimal;
	}


	template <typename T, typename Function>
	void insert(BinaryHeap<T, Function>& heap, const T& value)
	{
		//add it as the last leaf
		heap.elements.add(value);

		//and sift it up to its correct position
		siftUp(heap, heap.elements.getCount() - 1);
	}


	template <typename T, typename Function>
	void greatenKey(BinaryHeap<T, Function>& heap, int index, const T& key)
	{
		DynamicArray<T>& arr = heap.elements;

		//must be greater
		assert(heap.compareFn(arr[index], key));

		//change its key 
		arr[index] = key;

		//and sift it up
		siftUp(heap, index);
	}
}
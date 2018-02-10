
//---------------------------------------------------------------------------------------------------
//
// 'BIG 4'
//


template <typename T>
void initHeap(Heap<T>& heap, T* data, int size, int count)
{
	heap.data = data;
	heap.count = count;
	heap.size = size;
}


template <typename T>
void destroyHeap(Heap<T>& heap)
{
	delete[] heap.data;

	heap.data = nullptr;
}



template <typename T>
void copyFrom(const Heap<T>& from, Heap<T>& to)
{
	T* buffer = new T[from.size];

	for (int i = 0; i < from.count; ++i)
		buffer[i] = from.data[i];

	destroyHeap(to);
	assert(to.data == nullptr);

	initHeap(to, buffer, from.size, from.count);
}



template <typename T>
void resize(Heap<T>& heap, int newSize)
{
	T* buffer = new T[newSize];

	int newCount = (heap.count <= newSize) ? heap.count : newSize;

	//copy needed objects only
	for (int i = 0; i < newCount; ++i)
		buffer[i] = heap.data[i];

	destroyHeap(heap);
	assert(heap.data == nullptr);

	initHeap(heap, buffer, newSize, newCount);
}



//---------------------------------------------------------------------------------------------------
//
// SIMPLE
//


template <typename T>
inline bool isEmpty(const Heap<T>& heap)
{
	return heap.count == 0;
}


inline int getParent(int index)
{
	return (index - 1) / 2;
}

inline int getLeftChild(int index)
{
	return 2 * index + 1;
}

inline int getRightChild(int index)
{
	return 2 * index + 2;
}




//---------------------------------------------------------------------------------------------------
//
// COMPLEX
//


//
//max heap
//
template <typename T>
void siftDown(Heap<T>& heap, int position)
{
	T hand = heap.data[position];

	//the last leaf in the heap
	int last = heap.count - 1;

	//while there are children for the current node
	while (2 * position < last)
	{
		//the left child
		int maxChild = getLeftChild(position);

		//if there is a second child and it is greater, go to it
		if (maxChild < last && heap.data[maxChild] < heap.data[maxChild + 1])
			++maxChild;

		//if the greater child is greater than the hand
		if (hand < heap.data[maxChild])
		{
			//pull the child up
			heap.data[position] = heap.data[maxChild];

			//and go to its position
			position = maxChild;
		}
		else //if the greater of the children is not greater than the hand, the heap property holds
			break;
	}

	//put it in its place
	heap.data[position] = hand;
}



template <typename T>
void siftUp(Heap<T>& heap, int position)
{
	T hand = heap.data[position];

	//until the root is reached
	while (position > 0)
	{
		// ( index - 1 ) / 2
		int parent = getParent(position);

		//if the hand is greater than its parent
		if (heap.data[parent] < hand)
		{
			//pull the parent down
			heap.data[position] = heap.data[parent];

			//and go up to its position
			position = parent;
		}
		else //if the hand is not greater than its parent, the heap property holds
			break;
	}

	//put it in its place
	heap.data[position] = hand;
}




template <typename T>
void insert(Heap<T>& heap, const T& obj)
{
	if (heap.count == heap.size)
		resize(heap, 2 * heap.size);

	//insert it
	heap.data[heap.count++] = obj;

	//and sift it up
	siftUp(heap, heap.count - 1);
}


template <typename T>
void buildMaxHeap(Heap<T>& heap)
{
	int lastNonLeaf = (heap.count - 2) / 2;

	//from the first non-leaf (leaves are max heaps)
	//to the root
	for (; lastNonLeaf >= 0; --lastNonLeaf)
	{
		//sift the node down
		siftDown(heap, lastNonLeaf);
	}
}




template <typename T>
void heapSort(T* arr, int size)
{
	Heap<T> heap;
	init(heap, arr, size, size);

	//build a max heap on its array
	buildMaxHeap(heap);

	int last = heap.count - 1;

	//from the last leaf to the left child of the root
	while (last > 0)
	{
		//swap the root with the last leaf
		std::swap(arr[0], arr[last--]);

		//update count (for siftDown)
		--heap.count;

		//sift the new root down
		siftDown(heap, 0);
	}
}



//--------------------------------------------------------------------
//
//PRIORITY QUEUE FUNCTIONS
//


template <typename T>
T getMax(const Heap<T>& heap)
{
	return heap.data[0];
}


template <typename T>
T extractMax(Heap<T>& heap)
{
	//save root
	T max = heap.data[0];

	//put the last leaf in its place
	heap.data[0] = heap.data[heap.count - 1];

	//update count
	--heap.count;

	//sift the new root down if not empty
	if (!isEmpty(heap))
		siftDown(heap, 0);

	return max;
}



template <typename T>
void greatenKey(Heap<T>& heap, int position, const T& key)
{
	//new key must be greater
	assert(heap.data[position] < key);

	//update key
	heap.data[position] = key;

	//sift it up
	siftUp(heap, position);
}
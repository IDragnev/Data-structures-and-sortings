#include "../Template Dynamic Array/DynamicArray.h"
#include <assert.h>

namespace BinaryHeap
{
	template <typename T, typename Function>
	struct BinaryHeap
	{
		BinaryHeap(const Function& compare, int size = 16);

		DynamicArray<T> elements;
		const Function compareFn;
	};


	//
	//build a heap on its elements
	//
	template <typename T, typename Function>
	void buildHeap(BinaryHeap<T, Function>& heap);


	//
	//get the optimal element without extracting it
	//
	template <typename T, typename Function>
	T peekOptimal(const BinaryHeap<T, Function>& heap);


	//
	//get the optimal element by removing it from the heap
	//
	template <typename T, typename Function>
	T extractOptimal(BinaryHeap<T, Function>& heap);


	//
	//insert a key in the heap
	//
	template <typename T, typename Function>
	void insert(BinaryHeap<T, Function>& heap, const T& value);


	//
	//sift a 'node' up until the heap property holds
	//
	template <typename T, typename Function>
	void siftUp(BinaryHeap<T, Function>& heap, int index);


	//
	//sift a 'node' down until the heap property holds
	//
	template <typename T, typename Function>
	void siftDown(BinaryHeap<T, Function>& heap, int index);


	//
	//increase/decrease a key and update the node's position
	//acc. to its new 'priority'
	//
	template <typename T, typename Function>
	void greatenKey(BinaryHeap<T, Function>& heap, int index, const T& key);
}

#include "BinaryHeapImpl.hpp"
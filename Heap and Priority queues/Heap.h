#ifndef __HEAP_H_INCLUDED__
#define __HEAP_H_INCLUDED__

#include <assert.h>

template <typename T>
struct Heap
{
	int size;
	int count;
	T* data;
};


template <typename T>
void initHeap(Heap<T>& heap, T* data, int size, int count);

template <typename T>
void destroyHeap(Heap<T>& heap);

template <typename T>
void copyFrom(const Heap<T>& from, Heap<T>& to);

template <typename T>
void resize(Heap<T>& heap, int newSize);

template <typename T>
bool isEmpty(const Heap<T>&);



int getParent(int index);

int getLeftChild(int index);

int getRightChild(int index);



template <typename T>
void insert(Heap<T>& heap, const T&);

template <typename T>
void siftDown(Heap<T>& heap, int pos);

template <typename T>
void siftUp(Heap<T>& heap, int pos);

template <typename T>
void buildMaxHeap(Heap<T>& heap);

template <typename T>
void heapSort(T* heap, int size);


//priority queue functions
template <typename T>
T extractMax(Heap<T>& heap);

template <typename T>
T getMax(const Heap<T>& heap);

template <typename T>
void greatenKey(Heap<T>& heap, int index, const T& key);

#include "HeapImpl.hpp"
#endif //__HEAP_H_INCLUDED__
#ifndef __ST_QUEUE_H_INCLUDED__
#define __ST_QUEUE_H_INCLDUED__

#include "DynamicArray.h"

template <typename T>
class StaticQueue
{
public:
	StaticQueue(int size = 16);
	StaticQueue(const StaticQueue<T>&) = default;
	~StaticQueue() = default;

	StaticQueue<T>& operator=(const StaticQueue<T>&) = default;

	bool isEmpty()const;                                       //is the queue empty
	bool isFull()const;                                        //is the queue full

	void enqueue(const T&);                                    //enqueue an element
	T dequeue();                                               //dequeue an element

private:
	int head;                                                  //the head of the queue
	int tail;                                                  //the tail of the queue
	DynamicArray<T> elements;                                  //the underlying container of the queue
};

#include "StaticQueueImpl.hpp"


#endif //__DYN_QUEUE_H_INCLUDED__
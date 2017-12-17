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

	bool isEmpty()const;                                    
	bool isFull()const;                                        
	T peek()const;

	void enqueue(const T&);                                    
	T dequeue();                                               

private:
	int head;                                                 
	int tail;                                                  
	DynamicArray<T> elements;                                  
};

#include "StaticQueueImpl.hpp"


#endif //__DYN_QUEUE_H_INCLUDED__
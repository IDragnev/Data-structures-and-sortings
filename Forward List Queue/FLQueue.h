#ifndef __FORWARD_LIST_QUEUE_H_INCLUDED__
#define __FORWARD_LIST_QUEUE_H_INCLUDED__

#include "Node.h"
#include <stdexcept>
#include <iostream>
#include <assert.h>

template <typename T>
class FLQueue
{
public:
	FLQueue();
	FLQueue(const FLQueue<T>&);
	~FLQueue();

	FLQueue<T>& operator=(const FLQueue<T>&);

	bool isEmpty()const;                                    

	void enqueue(const T&);                                   
	T dequeue();                                             

private:
	Node<T>* head;
	Node<T>* tail;

private:
	static void clearChain(const Node<T>* firstNode);
	static Node<T>* cloneChain(const Node<T>* firstNode, Node<T>** lastNode = NULL);
};

#include "FLQueueImpl.hpp"

#endif //__FORWARD_LIST_QUEUE_H_INCLUDED__
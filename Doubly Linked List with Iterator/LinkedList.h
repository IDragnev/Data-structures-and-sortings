#ifndef __DOUBLY_LINKED_TAB_LIST_H_INCLUDED__
#define __DOUBLY_LINKED_TAB_LIST_H_INCLUDED__

#include "Node.h"
#include "ListIterator.h"
#include <assert.h>
#include <stdexcept>

template <typename T>
class LinkedList
{
public:
	LinkedList();
	LinkedList(const LinkedList<T>&);
	~LinkedList();

	LinkedList<T>& operator=(const LinkedList<T>&);

	int getCount()const;
	bool isEmpty()const;

	ListIterator<T> getHead();
	ListIterator<T> getTail();

	void appendList(const LinkedList<T>&);

public:
	void setHead(const T&);
	void setTail(const T&);

	void addAsHead(const T&);
	void addAsTail(const T&);

	void removeHead();
	void removeTail();

	void removeAt(ListIterator<T>& it);

	void removeBefore(ListIterator<T>& it);
	void removeAfter(ListIterator<T>& it);

	void insertAfter(ListIterator<T>& it, const T&);
	void insertBefore(ListIterator<T>& it, const T&);

private:
	int count;
	Node<T>* head;
	Node<T>* tail;

private:
	void clear();
	void checkIsEmtpy()const;

private:
	static Node<T>* findEndOfChain(Node<T>* firstNode);
	static Node<T>* cloneChain(const Node<T>* firstNode);
	static void clearChain(const Node<T>* firstNode);
};

#include "LinkedListImpl.hpp"

#endif //__DOUBLY_LINKED_TAB_LIST_H_INCLUDED__

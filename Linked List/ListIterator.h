#ifndef __LIST_ITERATOR_H_INCLUDED__
#define __LIST_ITERATOR_H_INCLUDED__


#include "Node.h"
#include <stdexcept>

template <typename Key>
class ListIterator
{
public:
	ListIterator(Node<Key>* startNode);
	ListIterator(const ListIterator<Key>&) = default;
	~ListIterator() = default;

	ListIterator<Key>& operator=(const ListIterator<Key>&) = default;

	bool isDone()const;             //is the traversal finished

	void first();                   //return iterator to beginning
	void next();                    //move iterator to the next node

	const Key& getCurrent()const;   //get the value of the current node
	void setCurrent(const Key&);    //set the value of the current node

private:
	Node<Key>* start;               //pointer to the start of the list
	Node<Key>* current;             //pointer to the current node of the list
};

#include "ListIteratorImpl.hpp"

#endif //__LIST_ITERATOR_H_INCLUDED__
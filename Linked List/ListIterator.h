#ifndef __LIST_ITERATOR_H_INCLUDED__
#define __LIST_ITERATOR_H_INCLUDED__


#include "Node.h"
#include <stdexcept>


template <typename Key>
class ListIterator
{
	template<typename Key>
	friend class LinkedList;
public:
	ListIterator(Node<Key>* startNode, const LinkedList<Key>* owner);
	ListIterator(const ListIterator<Key>&) = default;
	~ListIterator() = default;

	ListIterator<Key>& operator=(const ListIterator<Key>&) = default;

	bool operator!()const;             //returns true if the traversal is finished
	operator bool()const;              //returns ture if the traversal has not finished

	void first();                      //return iterator to beginning

	ListIterator<Key>& operator++();   //move iterator to the next node
	ListIterator<Key> operator++(int); //move iterator to he next node (postfix)

	Key& operator*();                  //returns the value of the current node
	const Key& operator*()const;       //returns the value of the current node

	bool operator==(const ListIterator<Key>&)const;

private:
	Node<Key>* start;               //pointer to the start of the list
	Node<Key>* current;             //pointer to the current node of the list
	const LinkedList<Key>* owner;     //pointer to the owner of the iterator
};

#include "ListIteratorImpl.hpp"

#endif //__LIST_ITERATOR_H_INCLUDED__
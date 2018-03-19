#ifndef __SINGLY_LINKED_LIST_ITERATOR_H_INCLUDED__
#define __SINGLY_LINKED_LIST_ITERATOR_H_INCLUDED__

#include "Node.h"

template <typename Key>
class SinglyLinkedListIterator
{
	template <typename Key>
	friend class SinglyLinkedList;
private:
	SinglyLinkedListIterator(Node<Key>* startNode, const SinglyLinkedList<Key>* owner);

public:
	Key& operator*();

	SinglyLinkedListIterator<Key>& operator++();   
	SinglyLinkedListIterator<Key> operator++(int); 

	bool operator!()const;             
	operator bool()const;             
	
	template <typename Key>
	friend bool operator==(const SinglyLinkedListIterator<Key>&, const SinglyLinkedListIterator<Key>&);
	template <typename Key>
	friend bool operator!=(const SinglyLinkedListIterator<Key>&, const SinglyLinkedListIterator<Key>&);

private:
	Node<Key>* current;            
	const SinglyLinkedList<Key>* owner;
};

#include "SinglyLinkedListIteratorImpl.hpp"
#endif //__SINGLY_LINKED_LIST_ITERATOR_H_INCLUDED__
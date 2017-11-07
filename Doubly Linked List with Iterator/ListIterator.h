#ifndef __LIST_ITER_H_INCLUDED__
#define __LIST_ITER_H_INCLUDED__

#include "Node.h"

template <typename T>
class ListIterator
{
	template <typename T>
	friend class LinkedList;
private:
	ListIterator(Node<T>* beg, const LinkedList<T>* list);

public:
	ListIterator(const ListIterator<T>&) = default;
	~ListIterator() = default;

	ListIterator<T>& operator=(const ListIterator<T>&) = default;

	T& operator*();

	ListIterator<T>& operator++();
	ListIterator<T> operator++(int);

	ListIterator<T>& operator--();
	ListIterator<T> operator--(int);

	bool operator!()const;
	operator bool()const;

	bool operator==(const ListIterator<T>&)const;

private:
	Node<T>* current;
	const LinkedList<T>* owner;
};

#include "ListIteratorImpl.hpp"

#endif //__LIST_ITER_H_INCLUDED__
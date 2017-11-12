#ifndef __FOR_LIST_ITERATOR_H_INCLUDED__
#define __FOR_LIST_ITERATOR_H_INCLUDED__

#include "Node.h"
#include <stdexcept>

template <typename Key>
class ForwardListIterator
{
	template<typename Key>
	friend class ForwardList;
private:
	ForwardListIterator(Node<Key>* startNode, const ForwardList<Key>* owner);

public:
	ForwardListIterator(const ForwardListIterator<Key>&) = default;
	~ForwardListIterator() = default;

	ForwardListIterator<Key>& operator=(const ForwardListIterator<Key>&) = default;

	Key& operator*();

	ForwardListIterator<Key>& operator++();   
	ForwardListIterator<Key> operator++(int); 

	bool operator!()const;             
	operator bool()const;             
	
	bool operator==(const ForwardListIterator<Key>&)const;

private:
	Node<Key>* current;            
	const ForwardList<Key>* owner;
};

#include "ForwardListIteratorImpl.hpp"

#endif //__LIST_ITERATOR_H_INCLUDED__
#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

#include <iostream>

template <typename Key>
class Node
{
public:
	Node(const Key& data, Node<Key>* successor = NULL);
	Node(const Node<Key>& other) = default;
	~Node() = default;

	Node<Key>& operator=(const Node<Key>&) = default;

	bool hasSuccessor()const;                     

public:  
	Node<Key>* next;                                   //the successor
	Key data;                                          //the data of the node
};

#include "NodeImpl.hpp"

#endif // __NODE_H_INCLUDED__
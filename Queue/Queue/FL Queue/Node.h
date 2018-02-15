#ifndef __FORWARD_LIST_QUEUE_NODE_H_INCLUDED__
#define __FORWARD_LIST_QUEUE_NODE_H_INCLUDED__

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
	Node<Key>* next;                                
	Key data;                                          
};

#include "NodeImpl.hpp"

#endif // __FORWARD_LIST_QUEUE_NODE_H_INCLUDED__
#ifndef __TEMPLATE_NODE_H_INCLUDED__
#define __TEMPLATE_NODE_H_INCLUDED__

#include <iostream>

template <typename T>
class Node
{
public:
	Node(const T& data, Node* previous = NULL, Node* next = NULL);
	Node(const Node&) = default;
	~Node() = default;

	Node& operator=(const Node&) = default;

	bool hasSuccessor()const;
	bool hasPredecessor()const;

public:
	Node* next;
	Node* previous;
	T data;
};

#include "NodeImpl.hpp"

#endif //__TEMPLATE_NODE_H_INCLUDED__
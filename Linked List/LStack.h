#ifndef __LINKED_LIST_STACK_H_INCLUDED__
#define __LINKED_LIST_STACK_H_INCLUDED__

#include "Node.h"
#include <assert.h>
#include <stdexcept>

template <typename T>
class LStack
{
public: 
	LStack();                                    //stack is empty when constructed
	LStack(const LStack<T>&);
	~LStack();

	LStack<T>& operator=(const LStack<T>&);

	void push(const T&);                         //push on the top of the stack
	T pop();                                     //get the top of the stack (removed)
	const T& peek()const;                        //get the top of the stack (not removed)

	bool isEmpty()const;                         //is the stack empty 

private:
	Node<T>* top;                                //pointer to the node at the top of the stack

private:
	void copyFrom(const LStack<T>&);             //copy the chain of nodes of another stack
	void clear();                                //clear current chain of nodes

private:
	static Node<T>* cloneChain(const Node<T>*);  //clone a chain of nodes by its first node
	static void clearChain(const Node<T>*);      //clear a chain of nodes by its first node
};

#include "LStackImpl.hpp"

#endif  //__LINKED_LIST_STACK_H_INCLUDED__


#ifndef __DYNSTACK_H_INCLUDED__
#define __DYNSTACK_H_INCLUDED__

#include "DynamicArray.h"


template <typename T>
class DynamicStack
{
public:
	DynamicStack();                                                 //constructs the underlying container with default size (10) and sets top as -1
	DynamicStack(const DynamicStack<T>&) = default;
	~DynamicStack() = default;

	DynamicStack<T>& operator=(const DynamicStack<T>&) = default;

	T pop();                                                        //get the top element of the stack	 
	void push(const T&);                                            //add an element on the top of the stack 
	bool isEmpty()const;                                            //is the stack empty

private:
	int top;                                                        //the top of the stack
	DynamicArray<T> elements;                                       //the elements of the stack (its underlying container)
};

#include "DynamicStackImpl.hpp"
#endif //__STACK_H_INCLUDED__
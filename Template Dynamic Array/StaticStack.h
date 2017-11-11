#ifndef __STATIC_STACK_H_INCLUDED__
#define __STATIC_STACK_H_INCLUDED__

#include "DynamicArray.h"

template <typename T>
class StaticStack
{
public:
	StaticStack(int size = 16);                                     //constructs its array with default objects, top is -1
	StaticStack(const StaticStack<T>&) = default;
	~StaticStack() = default;

	StaticStack<T>& operator=(const StaticStack<T>&) = default;

	bool isEmpty()const;                                            //is the stack empty
	void push(const T&);                                            //push the element on the top of the stack
	T pop();                                                        //get the top element of the stack

private:
	int top;                                                        //the top of the stack
	DynamicArray<T> elements;                                       //the underlying container
};

#include "StaticStackImpl.hpp"

#endif //__STATIC_STACK_H_INCLUDED__
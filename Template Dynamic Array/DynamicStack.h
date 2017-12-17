#ifndef __DYNSTACK_H_INCLUDED__
#define __DYNSTACK_H_INCLUDED__

#include "DynamicArray.h"

template <typename T>
class DynamicStack
{
public:
	DynamicStack(int size = 16);                                                 
	DynamicStack(const DynamicStack<T>&) = default;
	~DynamicStack() = default;

	DynamicStack<T>& operator=(const DynamicStack<T>&) = default;

	bool isEmpty()const;      
	const T& peek()const;

	void push(const T&);                                          
	T pop();                                                       

private:
	int top;                                                       
	DynamicArray<T> elements;                                      
};

#include "DynamicStackImpl.hpp"
#endif //__STACK_H_INCLUDED__
#ifndef __DYNSTACK_H_INCLUDED__
#define __DYNSTACK_H_INCLUDED__

#include "DynamicArray.h"


template <typename T>
class DynamicStack
{
public:
	DynamicStack();                                                 
	DynamicStack(const DynamicStack<T>&) = default;
	~DynamicStack() = default;

	DynamicStack<T>& operator=(const DynamicStack<T>&) = default;

	T pop();                                                       
	void push(const T&);                                          
	bool isEmpty()const;                                            

private:
	int top;                                                       
	DynamicArray<T> elements;                                      
};

#include "DynamicStackImpl.hpp"
#endif //__STACK_H_INCLUDED__
#ifndef __STATIC_STACK_H_INCLUDED__
#define __STATIC_STACK_H_INCLUDED__

#include "../../Template Dynamic Array/DynamicArray.h"

template <typename T>
class StaticStack
{
public:
	StaticStack(int size = 16);                                  
	StaticStack(const StaticStack<T>&) = default;
	~StaticStack() = default;

	StaticStack<T>& operator=(const StaticStack<T>&) = default;

	bool isEmpty()const;    
	const T& peek()const;

	void push(const T&); 
	T pop();                                                        

private:
	int top;                                                       
	DynamicArray<T> elements;                                      
};

#include "StaticStackImpl.hpp"

#endif //__STATIC_STACK_H_INCLUDED__
#ifndef __LINKED_LIST_STACK_H_INCLUDED__
#define __LINKED_LIST_STACK_H_INCLUDED__

#include "Node.h"
#include <assert.h>
#include <stdexcept>

template <typename T>
class LStack
{
public: 
	LStack();                                   
	LStack(const LStack<T>&);
	~LStack();

	LStack<T>& operator=(const LStack<T>&);

	bool isEmpty()const;                        
	const T& peek()const;

	void push(const T&);                       
	T pop();                                     

private:
	Node<T>* top;                               

private:
	void copyFrom(const LStack<T>&);             
	void clear();                               

private:
	static Node<T>* cloneChain(const Node<T>*); 
	static void clearChain(const Node<T>*);     
};

#include "LStackImpl.hpp"

#endif  //__LINKED_LIST_STACK_H_INCLUDED__


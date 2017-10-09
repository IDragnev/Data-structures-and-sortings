#ifndef __STACK_H_INCLUDED__
#define __STACK_H_INCLUDED__


template <typename T>
class Stack
{
public:
	Stack(int size = 10);
	Stack(const Stack<T>&);
	~Stack();

	Stack& operator=(const Stack&);

	T& pop();
	const T& pop()const;

	void push(const T&);
};



#endif //__STACK_H_INCLUDED__
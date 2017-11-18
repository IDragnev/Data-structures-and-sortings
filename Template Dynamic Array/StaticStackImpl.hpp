

//
//constructs the array to be filled with default objects (count = size)
//so that all can be available to the stack
//
template <typename T>
StaticStack<T>::StaticStack(int size)
	:
	top(-1),
	elements(size, size)
{
	;
}



template <typename T>
inline bool StaticStack<T>::isEmpty()const
{
	return top == -1;
}



template <typename T>
void StaticStack<T>::push(const T& object)
{
	if (top == elements.getSize() - 1)
		throw std::overflow_error("Stack overflow!");

	//increment top
	++top;

	//push object on the stack
	elements[top] = object;
}


template <typename T>
T StaticStack<T>::pop()
{
	if (isEmpty())
		throw std::underflow_error("Stack underflow!");

	//return object by value and post-decrement top
	return elements[top--];
}
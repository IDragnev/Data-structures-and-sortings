
template <typename T>
DynamicStack<T>::DynamicStack(int size)
	:
	top(-1),
	elements(size)
{
	;
}


template <typename T>
inline bool DynamicStack<T>::isEmpty()const
{
	return top == -1;
}


//
//cannot overflow
//
template <typename T>
void DynamicStack<T>::push(const T& object)
{
	//increment top
	++top;

	//if the top is now exactly after the last object in the array, use add
	if (top == elements.getCount())
		elements.add(object);
	else  //else (top is between 0 and count-1) write on elements[top]
		elements[top] = object;
}


template <typename T>
T DynamicStack<T>::pop()
{
	if (isEmpty())
		throw std::underflow_error("Stack underflow!");

	//return object by value and post-decrement top
	return elements[top--];
}


template <typename T>
const T& DynamicStack<T>::peek()const
{
	if (isEmpty())
		throw std::logic_error("Stack is empty!");

	return elements[top];
}


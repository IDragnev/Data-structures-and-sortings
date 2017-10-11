

template <typename T>
StaticQueue<T>::StaticQueue(int size)
	:
	head(0),
	tail(0),
	elements(size,size)
{
	;
}


template <typename T>
inline bool StaticQueue<T>::isEmpty()const
{
	return head == tail;
}


template <typename T>
inline int StaticQueue<T>::incremented(int value)
{
	assert(value < elements.getSize());

	//if head/tail == size - 1, make it 0
	//else just increment it
	return (value == (elements.getSize() - 1)) ? 0 : ++value;
}



template <typename T>
void StaticQueue<T>::enqueue(const T& element)
{
	if (incremented(tail) == head)
		throw std::overflow_error("Queue overflow!");

	//enqueue it
	elements[tail] = element;

	//increment tail
	tail = incremented(tail);
}


template <typename T>
T StaticQueue<T>::dequeue()
{
	if (isEmpty())
		throw std::underflow_error("Queue underflow!");

	//get the first element
	T &object = elements[head];

	//increment head
	head = incremented(head);

	return object;
}

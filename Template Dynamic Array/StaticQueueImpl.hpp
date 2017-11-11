

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
inline bool StaticQueue<T>::isFull()const
{
	return (tail + 1) % elements.getSize() == head;
}


template <typename T>
inline bool StaticQueue<T>::isEmpty()const
{
	return head == tail;
}



template <typename T>
void StaticQueue<T>::enqueue(const T& element)
{
	if (isFull())
		throw std::overflow_error("Queue is full!");

	//enqueue it
	elements[tail] = element;

	//increment tail
	tail = (tail + 1) % elements.getSize();
}


template <typename T>
T StaticQueue<T>::dequeue()
{
	if (isEmpty())
		throw std::underflow_error("Queue is empty!");

	//get the first element
	T &object = elements[head];

	//increment head
	head = (head + 1) % elements.getSize();

	return object;
}

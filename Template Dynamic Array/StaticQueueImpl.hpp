

template <typename T>
StaticQueue<T>::StaticQueue(int size)
	:
	head(0),
	tail(0),
	elements(size,size)
{
	;
}


//
//queue is full when there is exactly one 
//vacant place
//
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
		throw std::logic_error("Queue is full!");

	//enqueue it
	elements[tail] = element;

	//increment tail
	tail = (tail + 1) % elements.getSize();
}


template <typename T>
T StaticQueue<T>::dequeue()
{
	//get the first object,
	//peek throws an exception if
	//the queue is empty
	T object = peek();

	//increment head
	head = (head + 1) % elements.getSize();

	return object;
}



template <typename T>
T StaticQueue<T>::peek()const
{
	if (isEmpty())
		throw std::logic_error("Queue is empty!");

	return elements[head];
}
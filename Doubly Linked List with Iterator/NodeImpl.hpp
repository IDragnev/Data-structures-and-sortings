
template <typename T>
Node<T>::Node(const T& data, Node* previous, Node* next)
	:
	next(next),
	previous(previous),
	data(data)
{
	;
}


template <typename T>
bool Node<T>::hasSuccessor()const
{
	return next != NULL;
}


template <typename T>
bool Node<T>::hasPredecessor()const
{
	return previous != NULL;
}
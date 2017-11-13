
template <typename Key>
Node<Key>::Node(const Key& data, Node<Key>* successor)
	:
	next(successor),
	data(data)
{
	;
}


template <typename Key>
bool Node<Key>::hasSuccessor()const
{
	return next != NULL;
}

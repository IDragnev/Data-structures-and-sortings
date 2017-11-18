

template <typename Key>
ForwardListIterator<Key>::ForwardListIterator(Node<Key>* startNode, const ForwardList<Key>* owner)
	:
	current(startNode),
	owner(owner)
{
	;
}


//
//returns true if the traversal has not ended
//
template <typename Key>
ForwardListIterator<Key>::operator bool()const
{
	return current != NULL;
}



//
//returns true if the traversal has ended
//
template <typename Key>
bool ForwardListIterator<Key>::operator!()const
{
	return current == NULL;
}



//
//advance to the next node in the list
//
template <typename Key>
ForwardListIterator<Key>& ForwardListIterator<Key>::operator++()
{
	if (current)
		current = current->next;

	return *this;
}


template <typename Key>
ForwardListIterator<Key> ForwardListIterator<Key>::operator++(int)
{
	ForwardListIterator<Key> temp(*this);

	++(*this);

	return temp;
}


//
//return the data of the current node
//
template <typename Key>
Key& ForwardListIterator<Key>::operator*()
{
	return current->data;
}



//
//owner and current should be the same
//
template <typename Key>
bool ForwardListIterator<Key>::operator==(const ForwardListIterator<Key>& iter)const
{
	return (this->current == iter.current && this->owner == iter.owner);
}

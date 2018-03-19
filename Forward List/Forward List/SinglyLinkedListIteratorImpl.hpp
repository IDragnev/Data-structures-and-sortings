

template <typename Key>
SinglyLinkedListIterator<Key>::SinglyLinkedListIterator(Node<Key>* startNode, const SinglyLinkedList<Key>* owner)
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
SinglyLinkedListIterator<Key>::operator bool()const
{
	return current != nullptr;
}



//
//returns true if the traversal has ended
//
template <typename Key>
bool SinglyLinkedListIterator<Key>::operator!()const
{
	return current == nullptr;
}



//
//advance to the next node in the list (if not null)
//
template <typename Key>
SinglyLinkedListIterator<Key>& SinglyLinkedListIterator<Key>::operator++()
{
	if (current)
		current = current->next;

	return *this;
}


template <typename Key>
SinglyLinkedListIterator<Key> SinglyLinkedListIterator<Key>::operator++(int)
{
	SinglyLinkedListIterator<Key> temp(*this);

	++(*this);

	return temp;
}


//
//return the data of the current node
//
template <typename Key>
Key& SinglyLinkedListIterator<Key>::operator*()
{
	return current->data;
}



//
//owner and current should be the same
//
template <typename Key>
bool operator==(const SinglyLinkedListIterator<Key>& lhs, const SinglyLinkedListIterator<Key>& rhs)
{
	return (lhs.current == rhs.current && lhs.owner == rhs.owner);
}


template <typename Key>
bool operator!=(const SinglyLinkedListIterator<Key>& lhs, const SinglyLinkedListIterator<Key>& rhs)
{
	return !(lhs == rhs);
}
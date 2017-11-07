
template <typename T>
ListIterator<T>::ListIterator(Node<T>* beg, const LinkedList<T>* ownerList)
	:
	current(beg),
	owner(ownerList)
{
	;
}



//
//return the data of the current node
//
template <typename T>
inline T& ListIterator<T>::operator*()
{
	return current->data;
}



//
//advance to the next node
//
template <typename T>
ListIterator<T>& ListIterator<T>::operator++()
{
	if (current)
		current = current->next;

	return *this;
}


template <typename T>
ListIterator<T> ListIterator<T>::operator++(int)
{
	ListIterator<T> temp(*this);

	++(*this);

	return temp;
}


//
//go to the previous node
//
template <typename T>
ListIterator<T>& ListIterator<T>::operator--()
{
	if (current)
		current = current->previous;

	return *this;
}


template <typename T>
ListIterator<T> ListIterator<T>::operator--(int)
{
	ListIterator<T> temp(*this);

	--(*this);

	return temp;
}


//
//returns true if the traversal has not ended
//
template <typename T>
inline ListIterator<T>::operator bool()const
{
	return current != NULL;
}



//
//returns true if the traversal has ended
//
template <typename T>
inline bool ListIterator<T>::operator!()const
{
	return current == NULL;
}



//
//current node and owner must be the same
//
template <typename T>
bool ListIterator<T>::operator==(const ListIterator<T>& iter)const
{
	return (this->current == iter.current) && (this->owner == iter.owner);
}
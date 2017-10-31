

//
//initializes both start and current
//to point to the passed starting node
//
template <typename Key>
ListIterator<Key>::ListIterator(Node<Key>* startNode,const LinkedList<Key>* ownerList)
	:
	start(startNode),
	current(startNode),
	owner(ownerList)
{
	;
}




//
//returns true if the traversal has not ended
//
template <typename Key>
ListIterator<Key>::operator bool()const
{
	return current != NULL;
}



//
//returns true if the traversal has ended
//
template <typename Key>
bool ListIterator<Key>::operator!()const
{
	return current == NULL;
}



//
//advance to the next node in the list
//
template <typename Key>
ListIterator<Key>& ListIterator<Key>::operator++()
{
	if (current)
		current = current->next;

	return *this;
}


template <typename Key>
ListIterator<Key> ListIterator<Key>::operator++(int)
{
	ListIterator<Key> temp(*this);

	++(*this);

	return temp;
}


//
//returns iterator to beginning
//
template <typename Key>
void ListIterator<Key>::first()
{
	current = start;
}




//
//return the data of the current node
//
template <typename Key>
Key& ListIterator<Key>::operator*()
{
	return current->data;
}

//
//return the data of the current node
//
template <typename Key>
const Key& ListIterator<Key>::operator*()const
{
	return current->data;
}


//
//owner,start and current should be the same
//
template <typename Key>
bool ListIterator<Key>::operator==(const ListIterator<Key>& iter)const
{
	return (this->current == iter.current && 
		    this->owner == iter.owner && 
		    this->start == iter.start);
}

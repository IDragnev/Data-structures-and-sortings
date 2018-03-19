
//---------------------------------------------------------------------------------------
//
//GETTERS 
//


template <typename T>
inline bool SinglyLinkedList<T>::isEmpty()const
{
	return count == 0;
}



template <typename T>
inline void SinglyLinkedList<T>::throwExceptionIfEmpty()const
{
	if (isEmpty())
		throw std::logic_error("List is empty!");
}


template <typename T>
inline int SinglyLinkedList<T>::getCount()const
{
	return count;
}


template <typename T>
SinglyLinkedListIterator<T> SinglyLinkedList<T>::getHead()
{
	return SinglyLinkedListIterator<T>(head, this);
}


template <typename T>
SinglyLinkedListIterator<T> SinglyLinkedList<T>::getTail()
{
	return SinglyLinkedListIterator<T>(tail, this);
}



//-------------------------------------------------------------------------------------------
//
//SET
//


template <typename T>
void SinglyLinkedList<T>::nullMembers()
{
	head = nullptr;
	tail = nullptr;
	count = 0;
}



template <typename T>
void SinglyLinkedList<T>::setHead(const T& value)
{
	throwExceptionIfEmpty();

	head->data = value;
}



template <typename T>
void SinglyLinkedList<T>::setTail(const T& value)
{
	throwExceptionIfEmpty();

	tail->data = value;
}



//-------------------------------------------------------------------------------------------
//
//UTILITY
//


template <typename T>
void SinglyLinkedList<T>::clearChain(const Node<T>* firstNode)
{
	if (firstNode != nullptr)
	{
		const Node<T>* currentNode = firstNode;
		const Node<T>* oldNode = firstNode;

		while (currentNode != nullptr)
		{
			oldNode = currentNode;

			currentNode = currentNode->next;

			delete oldNode;
		}
	}
}



template <typename T>
void SinglyLinkedList<T>::empty()
{
	clearChain(head);

	nullMembers();
}



template <typename T>
Node<T>* SinglyLinkedList<T>::cloneChain(const Node<T>* firstNode, Node<T>** endOfChain)
{
	assert(firstNode);
	Node<T>* newChainHead = nullptr;

	try
	{
		newChainHead = new Node<T>(firstNode->data);

		const Node<T>* nodeToCopy = firstNode->next;

		Node<T>* newChainTail = newChainHead;

		while (nodeToCopy != nullptr)
		{
			newChainTail->next = new Node<T>(nodeToCopy->data);

			newChainTail = newChainTail->next;

			nodeToCopy = nodeToCopy->next;
		}

		if (endOfChain != nullptr)
			*endOfChain = newChainTail;

		return newChainHead;
	} 
	catch (std::bad_alloc&)
	{		
		clearChain(newChainHead);

		throw;
	}
}



template <typename T>
void SinglyLinkedList<T>::appendList(const SinglyLinkedList<T>& other)
{
	if ( ! other.isEmpty() )
	{
		Node<T>* newChainTail = nullptr;
		Node<T>* newChainHead = cloneChain(other.head, &newChainTail);

		appendChainAndUpdateCount(newChainHead, newChainTail, other.count);
	}
}



template <typename T>
void SinglyLinkedList<T>::appendList(SinglyLinkedList<T>&& source)
{
	if ( ! source.isEmpty() )
	{
		appendChainAndUpdateCount(source.head, source.tail, source.count);

		source.nullMembers();
	}
}



template <typename T>
void SinglyLinkedList<T>::appendChainAndUpdateCount(Node<T>* first, Node<T>* last, int count)
{
	assert(first && last);

	if ( this->isEmpty() )
	{
		this->head = first;
	}
	else
	{
		this->tail->next = first;
	}

	this->tail = last;
	this->count += count;
}



template <typename T>
Node<T>* SinglyLinkedList<T>::findNodeBefore(const Node<T>* node)const
{
	Node<T>* current = head;

	while (current != nullptr && current->next != node)
	{
		current = current->next;
	}

	return current;
}





//------------------------------------------------------------------------------------
//
//CTORS
//


template <typename T>
SinglyLinkedList<T>::SinglyLinkedList()
	:
	count(0),
	head(nullptr),
	tail(nullptr)
{
	;
}



template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other)
	:
	count(0),
	head(nullptr),
	tail(nullptr)
{
	appendList(other);
	assert(count == other.count);
}



template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T>&& source)
	:
	head(source.head),
	tail(source.tail),
	count(source.count)
{
	source.nullMembers();
}



template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other)
{
	if (this != &other)
	{
		swapContentsWithReconstructedParameter(other);
	}

	return *this;
}


template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList<T>&& source)
{
	if (this != &source)
	{
		swapContentsWithReconstructedParameter(std::move(source));
	}

	return *this;
}



//
// \ if the argument is an rvalue, temp will be move-constructed with it
// 
// \ if the argument is an lvalue, temp will be copy-constructed from it
//
template <typename T>
void SinglyLinkedList<T>::swapContentsWithReconstructedParameter(SinglyLinkedList<T> temp)
{
	std::swap(this->head, temp.head);
	std::swap(this->tail, temp.tail);
	std::swap(this->count, temp.count);
}



template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
	clearChain(head);
}



//-------------------------------------------------------------------------------------
//
//INSERTION AND REMOVAL
//


//
//add a node with the passed data as a head node
//
template <typename T>
void SinglyLinkedList<T>::insertAsHead(const T& value)
{
	//the new node's successor is the current head node
	Node<T>* newHead = new Node<T>(value, this->head);

	//if the list is emtpy, set tail
	if (isEmpty())
	{
		this->tail = newHead;
	}

	//update head and count
	this->head = newHead;

	++count;
}



//
//add a node with the passed data as the new tail
//
template <typename T>
void SinglyLinkedList<T>::insertAsTail(const T& value)
{
	//has no successor as a tail
	Node<T>* newTail = new Node<T>(value);

	//if the list is empty, update head
	if (isEmpty())
	{
		this->head = newTail;
	}
	else //update the successor of current tail
	{	
		this->tail->next = newTail;
	}

	//update tail and count
	this->tail = newTail;

	++count;
}




//
//remove the head node
//
// \ if the list is empty, an exception is thrown
//
template <typename T>
void SinglyLinkedList<T>::removeHead()
{
	throwExceptionIfEmpty();

	assert(head);

	//keep the address of the old head node
	Node<T>* oldHead = head;

	//move head to the next node in the list
	head = head->next;

	//if this was the only node in the list
	//update tail to nullptr 
	if(head == nullptr)
	{
		tail = nullptr;
	}

	//free old head and update count
	delete oldHead;

	--count;
}




//
//remove the specified node from the list
//
// \ if the pointer is nullptr, the function does nothing
//
template <typename T>
void SinglyLinkedList<T>::removeAt(Node<T>* node)
{
	if (node)
	{
		if (node == head)
		{
			removeHead();
		}
		//if it is not the head node, there are at least
		//two nodes in the list
		else
		{
			//find the node before the one we want to delete
			Node<T>* nodeBefore = findNodeBefore(node);

			assert(nodeBefore);

			//if the node we are about to delete is the tail, update tail
			if (node == tail)
			{
				tail = nodeBefore;
			}

			//update the successor of the previous node
			nodeBefore->next = node->next;

			//free node and update count
			delete node;

			--count;
		}
	}
}


//
//remove the node the sent iterator is pointing to
//
// \ if the iterator is not from this list an exception is thrown
//
template <typename T>
void SinglyLinkedList<T>::removeAt(SinglyLinkedListIterator<T>& iterator)
{
	if (iterator.owner != this)
		throw std::invalid_argument("Invalid iterator passed!");

	removeAt(iterator.current);

	//invalidate iterator
	iterator.current = nullptr;
}



template <typename T>
void SinglyLinkedList<T>::removeTail()
{
	return removeAt(tail);
}



//
//insert a node with the sent data
//exactly after the sent node
//
// \ if the pointer is nullptr
//   or it points to the tail node
//   insertAsTail is called 
//
template <typename T>
void SinglyLinkedList<T>::insertAfter(Node<T>* node, const T& data)
{
	if (!node || node == tail)
	{
		insertAsTail(data);
	}
	else //insert after it
	{
		//if it does not point to the tail (and is not nullptr), it has a successor
		assert(node->next);

		//newNode's successor is node's current successor
		Node<T>* newNode = new Node<T>(data, node->next);

		//update node's successor as the new node
		node->next = newNode;

		++count;
	}
}




//
//add a new node with the sent data
//exactly after the sent iterator's current
//
// \ if the iterator is not from this list
//   std::invalid_arg is thrown
//
template <typename T>
void SinglyLinkedList<T>::insertAfter(SinglyLinkedListIterator<T>& iterator, const T& data)
{
	if (iterator.owner != this)
		throw std::invalid_argument("Invalid iterator passed!");

	insertAfter(iterator.current, data);
}



//
//insert a node with the sent data 
//exactly before the sent node
//
// \ if the pointer is nullptr or points to the head,
//    insertAsHead is called
//
template <typename T>
void SinglyLinkedList<T>::insertBefore(Node<T>* node, const T& data)
{
	if (!node || node == head)
	{
		insertAsHead(data);
	}
	else
	{
		//it has a predecessor, because it is not the head node (and is not null)
		Node<T>* previous = findNodeBefore(node);
		
		assert(previous);

		//insert after its predecessor
		insertAfter(previous, data);
	}
}



//
//insert a new node with the sent data
//exactly before the sent iterator's current
//
// \ if the iterator is not from this list
//   std::invalid_arg is thrown
//
template <typename T>
void SinglyLinkedList<T>::insertBefore(SinglyLinkedListIterator<T>& iterator, const T& data)
{
	if (iterator.owner != this)
		throw std::invalid_argument("Invalid iterator passed!");

	insertBefore(iterator.current, data);
}



//
//remove the node after the one the iterator points to
//
// \ if the iterator is not from this list
//   std::invalid_arg is thrown
//
template <typename T>
void SinglyLinkedList<T>::removeAfter(SinglyLinkedListIterator<T>& iterator)
{
	if (iterator.owner != this)
		throw std::invalid_argument("Invalid iterator passed!");

	removeAt(iterator.current->next);
}




//
//remove the node before the one the iterator points to
//
// \ if the iterator is not from this list
//   std::invalid_arg is thrown
//
template <typename T>
void SinglyLinkedList<T>::removeBefore(SinglyLinkedListIterator<T>& iterator)
{
	if (iterator.owner != this)
		throw std::invalid_argument("Invalid iterator passed!");

	//find the one before it and remove it
	remoteAt( findNodeBefore(iterator.current) );
}

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


template <typename T>
void SinglyLinkedList<T>::insertAsHead(const T& item)
{
	Node<T>* newHead = new Node<T>(item, this->head);

	if ( isEmpty() )
	{
		this->tail = newHead;
	}

	this->head = newHead;
	++count;
}



template <typename T>
void SinglyLinkedList<T>::insertAsTail(const T& item)
{
	Node<T>* newTail = new Node<T>(item);

	if ( isEmpty() )
	{
		this->head = newTail;
	}
	else 
	{	
		this->tail->next = newTail;
	}

	this->tail = newTail;
	++count;
}



template <typename T>
void SinglyLinkedList<T>::removeHead()
{
	throwExceptionIfEmpty();

	assert(head);

	Node<T>* oldHead = head;
	
	head = head->next;

	if(head == nullptr)
	{
		tail = nullptr;
	}

	delete oldHead;
	--count;
}



template <typename T>
void SinglyLinkedList<T>::removeAt(Node<T>* node)
{
	if (node)
	{
		if (node == head)
		{
			removeHead();
		}
		//if it is not the head node, there are at least two nodes in the list
		else
		{
			Node<T>* nodeBefore = findNodeBefore(node);

			assert(nodeBefore);

			if (node == tail)
			{
				tail = nodeBefore;
			}

			
			nodeBefore->next = node->next;

			delete node;
			--count;
		}
	}
}



template <typename T>
void SinglyLinkedList<T>::removeAt(SinglyLinkedListIterator<T>& iterator)
{
	if (iterator.owner != this)
		throw std::invalid_argument("Invalid iterator passed!");

	removeAt(iterator.current);

	iterator.current = nullptr;
}



template <typename T>
void SinglyLinkedList<T>::removeTail()
{
	return removeAt(tail);
}



template <typename T>
void SinglyLinkedList<T>::insertAfter(Node<T>* node, const T& data)
{
	if (node == nullptr || node == tail)
	{
		insertAsTail(data);
	}
	else 
	{
		//if it does not point to the tail and is not null, it has a successor
		assert(node->next);

		Node<T>* newNode = new Node<T>(data, node->next);

		node->next = newNode;

		++count;
	}
}



template <typename T>
void SinglyLinkedList<T>::insertAfter(SinglyLinkedListIterator<T>& iterator, const T& data)
{
	if (iterator.owner != this)
		throw std::invalid_argument("Invalid iterator passed!");

	insertAfter(iterator.current, data);
}



template <typename T>
void SinglyLinkedList<T>::insertBefore(Node<T>* node, const T& data)
{
	if (node == nullptr || node == head)
	{
		insertAsHead(data);
	}
	else
	{
		//it has a predecessor, because it is not the head node and is not null
		Node<T>* previous = findNodeBefore(node);
		
		assert(previous);

		insertAfter(previous, data);
	}
}



template <typename T>
void SinglyLinkedList<T>::insertBefore(SinglyLinkedListIterator<T>& iterator, const T& data)
{
	if (iterator.owner != this)
		throw std::invalid_argument("Invalid iterator passed!");

	insertBefore(iterator.current, data);
}



template <typename T>
void SinglyLinkedList<T>::removeAfter(SinglyLinkedListIterator<T>& iterator)
{
	if (iterator.owner != this)
		throw std::invalid_argument("Invalid iterator passed!");

	removeAt(iterator.current->next);
}




template <typename T>
void SinglyLinkedList<T>::removeBefore(SinglyLinkedListIterator<T>& iterator)
{
	if (iterator.owner != this)
		throw std::invalid_argument("Invalid iterator passed!");

	removeAt( findNodeBefore(iterator.current) );
}
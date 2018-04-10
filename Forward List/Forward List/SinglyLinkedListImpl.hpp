
template <typename T>
inline bool SinglyLinkedList<T>::isEmpty()const
{
	return count == 0;
}


template <typename T>
inline void SinglyLinkedList<T>::throwExceptionIfEmpty()const
{
	if ( isEmpty() )
		throw std::logic_error("List is empty!");
}


template <typename T>
inline typename SinglyLinkedList<T>::countType SinglyLinkedList<T>::getCount()const
{
	return count;
}


template <typename T>
inline SinglyLinkedListIterator<T> SinglyLinkedList<T>::getHead()
{
	return SinglyLinkedListIterator<T>(head, this);
}


template <typename T>
inline SinglyLinkedListIterator<T> SinglyLinkedList<T>::getTail()
{
	return SinglyLinkedListIterator<T>(tail, this);
}



template <typename T>
inline void SinglyLinkedList<T>::nullifyMembers()
{
	count = 0;
	head = nullptr;
	tail = nullptr;
}



template <typename T>
inline void SinglyLinkedList<T>::setHead(const T& data)
{
	throwExceptionIfEmpty();

	head->data = data;
}



template <typename T>
inline void SinglyLinkedList<T>::setTail(const T& data)
{
	throwExceptionIfEmpty();

	tail->data = data;
}



template <typename T>
void SinglyLinkedList<T>::clearChainStartingAt(const Node<T>* firstNode)
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
inline void SinglyLinkedList<T>::empty()
{
	clearChainStartingAt(head);

	nullifyMembers();
}



template <typename T>
Node<T>* SinglyLinkedList<T>::cloneChainStartingAt(const Node<T>* firstNode, Node<T>** endOfChain)
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
		clearChainStartingAt(newChainHead);

		throw;
	}
}



template <typename T>
void SinglyLinkedList<T>::appendList(const SinglyLinkedList<T>& other)
{
	if ( ! other.isEmpty() )
	{
		Node<T>* newChainTail = nullptr;
		Node<T>* newChainHead = cloneChainStartingAt(other.head, &newChainTail);

		appendChainAndUpdateCount(newChainHead, newChainTail, other.count);
	}
}



template <typename T>
void SinglyLinkedList<T>::appendList(SinglyLinkedList<T>&& source)
{
	if ( ! source.isEmpty() )
	{
		appendChainAndUpdateCount(source.head, source.tail, source.count);

		source.nullifyMembers();
	}
}



template <typename T>
void SinglyLinkedList<T>::appendChainAndUpdateCount(Node<T>* first, Node<T>* last, countType count)
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


template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() :
	count(0),
	head(nullptr),
	tail(nullptr)
{
	;
}


template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other)	:
	SinglyLinkedList<T>()
{
	appendList(other);
	assert(count == other.count);
}



template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T>&& source) :
	head(source.head),
	tail(source.tail),
	count(source.count)
{
	source.nullifyMembers();
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


template <typename T>
inline void SinglyLinkedList<T>::swapContentsWithReconstructedParameter(SinglyLinkedList<T> temp)
{
	std::swap(this->head, temp.head);
	std::swap(this->tail, temp.tail);
	std::swap(this->count, temp.count);
}


template <typename T>
inline SinglyLinkedList<T>::~SinglyLinkedList()
{
	clearChainStartingAt(head);
}



template <typename T>
void SinglyLinkedList<T>::insertAsHead(const T& item)
{
	Node<T>* newHead = new Node<T>(item, this->head);

	if ( isEmpty() )
		this->tail = newHead;

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
		tail = nullptr;

	delete oldHead;
	--count;
}



template <typename T>
void SinglyLinkedList<T>::removeAt(Node<T>* node)
{
	if (node != nullptr)
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
				tail = nodeBefore;
			
			nodeBefore->next = node->next;

			delete node;
			--count;
		}
	}
}



template <typename T>
inline void SinglyLinkedList<T>::removeAt(SinglyLinkedListIterator<T>& iterator)
{
	throwExceptionIfInvalid(iterator);

	removeAt(iterator.current);

	iterator.current = nullptr;
}



template <typename T>
inline void SinglyLinkedList<T>::removeTail()
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
		//if it is not the tail and is not null, it has a successor
		assert(node->next);

		Node<T>* newNode = new Node<T>(data, node->next);

		node->next = newNode;

		++count;
	}
}



template <typename T>
void SinglyLinkedList<T>::insertAfter(SinglyLinkedListIterator<T>& iterator, const T& data)
{
	throwExceptionIfInvalid(iterator);

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
	throwExceptionIfInvalid(iterator);

	insertBefore(iterator.current, data);
}



template <typename T>
void SinglyLinkedList<T>::removeAfter(SinglyLinkedListIterator<T>& iterator)
{
	throwExceptionIfInvalid(iterator);

	removeAt(iterator.current->next);
}


template <typename T>
inline void SinglyLinkedList<T>::removeBefore(SinglyLinkedListIterator<T>& iterator)
{
	throwExceptionIfInvalid(iterator);

	removeAt( findNodeBefore(iterator.current) );
}


template <typename T>
inline void SinglyLinkedList<T>::throwExceptionIfInvalid(const SinglyLinkedListIterator<T>& iterator) const 
{
	if (iterator.owner != this)
		throw std::invalid_argument("Invalid iterator passed!");
}
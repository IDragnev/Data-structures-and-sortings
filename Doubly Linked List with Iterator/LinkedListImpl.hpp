//-----------------------------------------------------------------------------------
//
//GET AND SET
//

template <typename T>
int LinkedList<T>::getCount()const
{
	return count;
}


template <typename T>
bool LinkedList<T>::isEmpty()const
{
	return count == 0;
}



//
//if the list is empty, an exception is thrown
//
//it will be called in each operation that cannot be
//executed if the list is emtpy
//
template <typename T>
void LinkedList<T>::checkIsEmtpy()const
{
	if (isEmpty())
		throw std::logic_error("List is empty!");
}



//
//sets the data of the head node with the passed value
//
//if the list is empty, an exception is thrown
//
template <typename T>
void LinkedList<T>::setHead(const T& data)
{
	checkIsEmtpy();

	head->data = data;
}



//
//sets the data of the tail node with the passed value
//
//if the list is empty, an exception is thrown
//
template <typename T>
void LinkedList<T>::setTail(const T& data)
{
	checkIsEmtpy();

	tail->data = data;
}


//
//return a list iterator which 'points' to 
//the last node in the list
//
// \ the iterator is 'done' if the list is empty
//                                 (tail is NULL)
//
template <typename T>
ListIterator<T> LinkedList<T>::getTail()
{
	return ListIterator<T>(tail, this);
}


//
//return a list iterator which 'points' to 
//the first node in the list
//
// \ the iterator is 'done' if the list is empty
//                                 (head is NULL)
//
template <typename T>
ListIterator<T> LinkedList<T>::getHead()
{
	return ListIterator<T>(head, this);
}


//-----------------------------------------------------------------------------------
//
//UTILITY
//



//
//move forward in the chain while possible
//and return the address of the last node
//
template <typename T>
Node<T>* LinkedList<T>::findEndOfChain(Node<T>* firstNode)
{
	assert(firstNode);

	Node<T>* current = firstNode;

	//while there is an actual successor
	//move forward in the chain
	while (current->next)
		current = current->next;

	return current;
}



//
//clear a whole chain of nodes
//by the address of its first node
//
//if the firstNode pointer is NULL 
//the function does nothing
//
template <typename T>
void LinkedList<T>::clearChain(const Node<T>* firstNode)
{
	if (firstNode)
	{
		const Node<T>* current = firstNode;
		const Node<T>* oldCurrent = firstNode;

		//while there is an actual node to delete
		while (current)
		{
			//save the address of the current node
			oldCurrent = current;

			//move to the next node in the chain
			current = current->next;

			//free the 'old current'
			delete oldCurrent;
		}
	}
}




//
//clone a chain by the address of its first node
//
//in case of bad_alloc the reconstructed chain is cleared
//and the exception is rethrown
//
template <typename T>
Node<T>* LinkedList<T>::cloneChain(const Node<T>* firstNode)
{
	assert(firstNode);
	Node<T>* newChain = NULL;

	try
	{
		//the start of the new chain
		newChain = new Node<T>(firstNode->data);

		//the node which we will copy next (initially points to the second node of the passed chain)
		const Node<T>* readFrom = firstNode->next;

		//the node to which we will attach the copied node (initially points to newChain)
		Node<T>* attachTo = newChain;

		//while there is an actual node to copy
		while (readFrom)
		{
			assert(attachTo->next == NULL);
			//attach the new node
			attachTo->next = new Node<T>(readFrom->data, attachTo);

			//move to the current end of chain
			attachTo = attachTo->next;

			//move to the next node to copy
			readFrom = readFrom->next;
		}

		return newChain;
	}
	catch (std::bad_alloc& ex)
	{
		clearChain(newChain);

		throw;
	}
}




//
//clear the current chain of nodes
//and make tail, head and count 0
//
template <typename T>
void LinkedList<T>::removeAll()
{
	clearChain(head);

	head = NULL;
	tail = NULL;
	count = 0;
}




//
//append other list's chain of nodes
//to this
//
template <typename T>
void LinkedList<T>::appendList(const LinkedList<T>& other)
{
	//if other is empty, leave
	if (other.isEmpty())
		return;

	//clone other list's chain of nodes
	Node<T>* newChain = cloneChain(other.head);

	//the first node of the new chain should not have a predecessor
	assert(newChain->previous == NULL);

	//if the list is empty, attach the chain to the head pointer
	if (isEmpty())
	{
		this->head = newChain;
	}
	else //else attach it to the tail node
	{
		newChain->previous = this->tail;

		this->tail->next = newChain;
	}

	//update tail
	this->tail = findEndOfChain(newChain);

	//increase count
	this->count += other.count;
}




//-----------------------------------------------------------------------------------
//
//BIG 4
//



//
//the list is empty when constructed
//
template <typename T>
LinkedList<T>::LinkedList()
	:
	count(0),
	head(NULL),
	tail(NULL)
{
	;
}




//
//initialize members as 0
//and append other's chain of nodes 
//
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
	:
	count(0),
	head(NULL),
	tail(NULL)
{
	appendList(other);
	assert(count == other.count);
}



//
//Make a copy of other's chain and store
//the copy in the current object.
//
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
	if (this != &other)
	{
		//Make a copy of other.
		LinkedList<T> temp(other);

		//Swap the current object's chain
		//with the temporary object's chain.
		std::swap(head, temp.head);
		std::swap(tail, temp.tail);

		//Swap count and let temp go out of scope
		//and destroy the old chain.
		std::swap(count, temp.count);
	}

	return *this;
}



//
//free the chain of nodes
//
template <typename T>
LinkedList<T>::~LinkedList()
{
	clearChain(head);
}



//-----------------------------------------------------------------------------------------------
//
//INSERTION AND REMOVAL
//


//
//add a node with the passed data
//as head node
//
template <typename T>
void LinkedList<T>::addAsHead(const T& data)
{
	//make a new node and set its predecessor to be NULL
	//and its successor to be the current head node
	Node<T>* newHead = new Node<T>(data, NULL, this->head);

	//if the list is emtpy, set tail
	if (isEmpty())
	{
		this->tail = newHead;
	}
	else //set current head's previous
	{
		this->head->previous = newHead;
	}

	//update head
	this->head = newHead;

	//update count
	++count;
}



//
//remove the head node
//
//if the list is empty, an exception is thrown
//
template <typename T>
void LinkedList<T>::removeHead()
{
	checkIsEmtpy();

	assert(head != NULL);

	//keep the address of the old head node
	Node<T>* oldHead = head;

	//move to the next node in the list
	head = head->next;

	//if this was the only node in the list
	if (head == NULL)
	{
		//update tail to be NULL too
		tail = NULL;
	}
	else //unlink the new head with the old head
	{
		head->previous = NULL;
	}

	//free old head
	delete oldHead;

	//update count 
	--count;

}



//
//add a node with the passed value
//as the new tail
//
template <typename T>
void LinkedList<T>::addAsTail(const T& data)
{
	//add a new node with no successor and the current tail
	//as its predecessor
	Node<T>* newTail = new Node<T>(data, tail, NULL);

	//if the list is empty
	if (isEmpty())
	{
		//update head
		this->head = newTail;
	}
	else
	{
		//update the successor of current tail
		this->tail->next = newTail;
	}

	//update tail
	this->tail = newTail;

	//update count
	++count;
}




//
//remove the tail node
//
//if the list is empty, an exception is thrown
//
template <typename T>
void LinkedList<T>::removeTail()
{
	checkIsEmtpy();

	assert(tail != NULL);

	//save the address of the old tail
	Node<T>* oldTail = this->tail;

	//move to the previous node in the list
	tail = tail->previous;

	//if this was the only node in the list
	if (tail == NULL)
	{
		//update head to be NULL too
		head = NULL;
	}
	else //unlink the new tail with the old tail
	{
		tail->next = NULL;
	}

	//free old head
	delete oldTail;

	//update count 
	--count;
}



//
//remove the node from the list
//
//if the pointer is NULL,just leave
//
template <typename T>
void LinkedList<T>::removeAt(Node<T>* node)
{
	//if not NULL
	if (node)
	{
		//if it's the head node
		if (node == head)
		{
			removeHead();
		}
		//else if it points to the tail node
		else if (node == tail)
		{
			removeTail();
		}
		else // this means node has both successor AND predecessor
		{
			assert(node->hasSuccessor() && node->hasPredecessor());

			//link node's neighbours toghether
			node->next->previous = node->previous;
			node->previous->next = node->next;

			//free node
			delete node;

			//decrease count
			--count;
		}
	}
}



//
//remove the node at which the iterator is
//
// \ if the iterator is not from this list
//   std::invalid_arg is thrown
//
template <typename T>
void LinkedList<T>::removeAt(ListIterator<T>& it)
{
	if (it.owner != this)
		throw std::invalid_argument("Invalid iterator passed!");

	//remove it
	removeAt(it.current);

	//invalidate iterator
	it.current = NULL;
}


//
//remove the node before the one the iterator points to
//
// \ if the iterator is not from this list
//   std::invalid_arg is thrown
//
template <typename T>
void LinkedList<T>::removeBefore(ListIterator<T>& it)
{
	if (it.owner != this)
		throw std::invalid_argument("Invalid iterator passed!");

	//remove the one before it
	removeAt(it.current->previous);

	//invalidate iterator
	it.current = NULL;
}



//
//remove the node after the one the iterator points to
//
// \ if the iterator is not from this list
//   std::invalid_arg is thrown
//
template <typename T>
void LinkedList<T>::removeAfter(ListIterator<T>& it)
{
	if (it.owner != this)
		throw std::invalid_argument("Invalid iterator passed!");

	//remove the one after it
	removeAt(it.current->next);

	//invalidate iterator
	it.current = NULL;
}




//
//add a new node with the sent data
//exactly after the sent node
//
// \ if the pointer is NULL
//   or it points to the tail node
//   addAsTail is called 
//
template <typename T>
void LinkedList<T>::insertAfter(Node<T>* node, const T& data)
{
	//if NULL or tail
	if (!node || node == tail)
	{
		addAsTail(data);
	}
	else //else insert after it
	{
		//if it does not point to the tail (and is not NULL) it has a successor
		assert(node->hasSuccessor());

		//insert it exactly after the node
		Node<T>* newNode = new Node<T>(data, node, node->next);

		//update node successor's predecessor
		node->next->previous = newNode;

		//update node's successor as the new node
		node->next = newNode;

		//increment count
		++count;
	}
}



//
//add a new node with the sent data
//exactly after the iterator's current
//
// \ if the iterator is not from this list
//   std::invalid_arg is thrown
//
template <typename T>
void LinkedList<T>::insertAfter(ListIterator<T>& it, const T& data)
{
	if (it.owner != this)
		throw std::invalid_argument("Invalid iterator passed!");

	//insert it
	insertAfter(it.current, data);
}


//
//insert a node with the sent data 
//exactly before the sent node
//
// \ if the pointer is NULL or points to the head
//    addAsHead is called
//
template <typename T>
void LinkedList<T>::insertBefore(Node<T>* node, const T& data)
{
	//if NULL or points to the head node, insert before the head
	if (!node || node == head)
	{
		addAsHead(data);
	}
	else
	{
		//it has a predecessor, because it is not the head node
		assert(node->hasPredecessor());

		//insert after its predecessor
		insertAfter(node->previous, data);
	}
}


//
//insert a new node with the sent data
//exactly before it.current
//
// \ if the iterator is not from this list
//   std::invalid_arg is thrown
//
template <typename T>
void LinkedList<T>::insertBefore(ListIterator<T>& it, const T& data)
{
	if (it.owner != this)
		throw std::invalid_argument("Invalid iterator passed!");

	//insert before it
	insertBefore(it.current, data);
}

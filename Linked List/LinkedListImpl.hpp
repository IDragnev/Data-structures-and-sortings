
//---------------------------------------------------------------------------------------
//
//GETTERS 
//


template <typename T>
inline bool LinkedList<T>::isEmpty()const
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
inline void LinkedList<T>::checkIsEmtpy()const
{
	if (isEmpty())
		throw std::logic_error("List is empty!");
}


template <typename T>
inline int LinkedList<T>::getCount()const
{
	return count;
}


//
//returns the value which the specified node holds
//
//if the list is empty an exception is thrown
//
//searchByIndex throws an exception if the position is invalid 
//
template <typename T>
const T& LinkedList<T>::getAt(int position)const
{
	checkIsEmtpy();

	return searchByIndex(position)->data;
}


//
//returns the value that the head node holds
//
//if the list is empty an exception is thrown
//
template <typename T>
const T& LinkedList<T>::getHead()const
{
	checkIsEmtpy();

	return head->data;
}



//
//returns the value that the tail node holds
//
//if the list is empty an exception is thrown
//
template <typename T>
const T& LinkedList<T>::getTail()const
{
	checkIsEmtpy();

	return tail->data;
}

//-------------------------------------------------------------------------------------------
//
//SET
//


//
//sets the value of the head node with the passed value
//
//if the list is empty, an exception is thrown
//
template <typename T>
void LinkedList<T>::setHead(const T& value)
{
	checkIsEmtpy();

	head->data = value;
}



//
//sets the value of the tail node with the passed value
//
//if the list is empty, an exception is thrown
//
template <typename T>
void LinkedList<T>::setTail(const T& value)
{
	checkIsEmtpy();

	tail->data = value;
}


//
//sets the value of the specified node
//
//if the list is empty, an exception is thrown
//
//searchByIndex throws an exception if the position is invalid 
//
template <typename T>
void LinkedList<T>::setAt(int position, const T& value)
{
	checkIsEmtpy();

	searchByIndex(position)->data = value;
}



//-------------------------------------------------------------------------------------------
//
//UTILITY
//

template <typename T>
Node<T>* LinkedList<T>::searchByIndex(int index)const
{
	if (index < 0 || index >= count)
		throw std::invalid_argument("Index out of range!");

	//get the first node
	Node<T>* current = this->head;

	//move forward in the list
	for (int i = 0; i < index; ++i)
		current = current->next;

	return current;
}


//
//else move forward in the chain while possible
//and return the address of the last node
//
template <typename T>
Node<T>* LinkedList<T>::findEndOfChain(Node<T>* firstNode)
{
	assert(firstNode);

	Node<T>* current = firstNode;

	//while the is an actual successor
	//move forward in the chain
	while (current->next)
		current = current->next;

	return current;
}


//
//free each node in the chain
//
//if the sent address is NULL, return
//
template <typename T>
void LinkedList<T>::clearChain(const Node<T>* firstNode)
{
	if (!firstNode) return;

	const Node<T>* currentNode = firstNode;
	const Node<T>* oldNode = firstNode;

	//while there is an actual successor
	while (currentNode)
	{
		//save current's address
		oldNode = current;

		//move forward in the chain
		current = current->next;
		
		//free old
		delete oldNode;
	}
}



//
//call clearChain with the head node 
//and set members as 0
//
template <typename T>
void LinkedList<T>::clear()
{
	clearChain(head);

	head = NULL;
	tail = NULL;
	count = 0;
}




//
//clone the chain by the address of its first node
//
template <typename T>
Node<T>* LinkedList<T>::cloneChain(const Node<T>* firstNode)
{
	Node<T>* newChain = NULL;
	assert(firstNode);

	try
	{
		//the start of the new chain
		newChain = new Node<T>(firstNode->data);

		//pointer to the node we will copy next (initially points to the second node of the passed chain)
		const Node<T>* readFrom = firstNode->next;

		//pointer to the node to which we will connect the next node
		Node<T>* connectTo = newChain;

		//while there is an actual node to copy
		while (readFrom)
		{
			//append to chain
			connectTo->next = new Node<T>(readFrom->data);

			//move to current end of chain
			connectTo = connectTo->next;

			//move to the next node to be copied
			readFrom = readFrom->next;
		}

		return newChain;
	} //in case of bad allocation
	catch (std::bad_alloc& ex)
	{		
		clearChain(newChain);

		throw;
	}
}


//
//returns the node before the passed one 
//
//if the passed node is NULL, NULL is returned
//
template <typename T>
Node<T>* LinkedList<T>::findNodeBefore(const Node<T>* node)const
{
	//start from head
	Node<T>* current = head;

	//while there is an actual node and its sucessor is not the one 
	//we are searching for, move forward in the list
	while (current && current->next != node)
	{
		current = current->next;
	}

	//if the list was empty, NULL is returned
	//if the passed node is not in the list,
	//the end of list is reached, where desiredNode points to NULL
	return current;
}





//------------------------------------------------------------------------------------
//
//CTORS
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
//delete the list's chain of nodes,
//initialize members back to 0
//and append other's chain of nodes to this
//
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
	if (this != &other)
	{
		clear();
		append(other);
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



//-------------------------------------------------------------------------------------
//
//INSERTION AND REMOVAL
//


//
//add a node with passed value 
//as head node
//
template <typename T>
void LinkedList<T>::addAsHead(const T& value)
{
	//make a new node and set its successor 
	//to be the current head node
	Node<T>* newHead = new Node<T>(value, this->head);

	//if the list is emtpy, set tail
	if (isEmpty())
		this->tail = newHead;

	//update head
	this->head = newHead;

	//update count
	++count;
}


//
//add a node with the passed value
//as the new tail
//
template <typename T>
void LinkedList<T>::addAsTail(const T& value)
{
	Node<T>* newTail = new Node<T>(value);

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
//remove the head node
//
template <typename T>
void LinkedList<T>::removeHead()
{
	//if not empty
	if ( ! isEmpty() )
	{
		assert(head != NULL);

		//keep the address of the old head node
		Node<T>* oldHead = head;

		//move to the next node in the list
		head = head->next;

		//if this was the only node in the list
		if(head == NULL)
		{
			//update tail to be NULL too
			tail = NULL;
		}

		//free old head
		delete oldHead;

		//update count 
		--count;
	}
}



//
//remove the node in the specified position
//
//exception is thrown if the index is invalid
//
template <typename T>
void LinkedList<T>::removeAt(int index)
{
	if (index == 0)
	{
		return removeHead();
	}
	else
	//if the index is not 0, 
	//there should be at least 2 nodes in the list
	{
		//find the node before the one we want to delete
		//(exception is thrown if the index is invalid)
		Node<T>* nodeBeforeIndex = searchByIndex(index - 1);

		//the node we want to delete
		Node<T>* nodeAtIndex = nodeBeforeIndex->next;

		//if the node we are about to delete is the last 
		//in the list, update tail
		if (index == count - 1)
		{
			tail = nodeBeforeIndex;
		}

		//update the successor of the previous node
		nodeBeforeIndex->next = nodeAtIndex->next;

		//free node
		delete nodeAtIndex;

		//update count
		--count;
	}

}

//
//remove the tail node
//
template <typename T>
void LinkedList<T>::removeTail()
{
	if ( ! isEmpty() )
	{
		return removeAt(count - 1);
	}
}



//
//insert a new node with the passed value 
//after the node in the specified position
//
template <typename T>
void LinkedList<T>::insertAfter(int index, const T& value)
{
	//throws an exception if the index is invalid
	Node<T>* nodeAtIndex = searchByIndex(index);

	//the node we are about to insert
	Node<T>* newNode = new Node<T>(value, nodeAtIndex->next);

	//update the successor of the previous node
	nodeAtIndex->next = newNode;

	//if we are inserting after the tail node
	if (nodeAtIndex == tail)
	{
		tail = newNode;
	}

	//update count
	++count;
}




//
//inserts a node after the node in the
//specified position with the passed value
//
template <typename T>
void LinkedList<T>::insertBefore(int index, const T& value)
{
	//if the specified node is the head node
	//call insert as head
	if (index == 0)
	{
		return addAsHead(value);
	}
	else //insert after the node before the specified one
	{
		return insertAfter(index - 1, value);
	}
}




//
//append other list's chain of nodes
//to this
//
template <typename T>
void LinkedList<T>::appendList(const LinkedList<T>& other)
{
	//if other is empty, leave
	if (other.IsEmpty())
		return;

	//clone other list's chain of nodes
	Node<T>* newChain = cloneChain(other.head);

	//if the list is empty, attach the chain to the head pointer
	if (isEmpty())
	{
		this->head = newChain;
	}
	else //else attach it to the tail node
	{
		this->tail->next = newChain;
	}

	//update tail
	this->tail = findEndOfChain(newChain);

	//increase count
	this->count += other.count;
}
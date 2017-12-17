
//-------------------------------------------------------------------------------------------
//
//UTILITY
//

//
//clone the chain by the address of its first node
//
// \ if endOfChain points to a valid pointer
//   it is set to point to the address of the
//   last node in the cloned chain
//
template <typename T>
Node<T>* FLQueue<T>::cloneChain(const Node<T>* firstNode, Node<T>** endOfChain)
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

		if (endOfChain)
			*endOfChain = connectTo;

		return newChain;
	} //in case of bad allocation
	catch (std::bad_alloc& ex)
	{
		clearChain(newChain);

		throw;
	}
}



//
//free each node in the chain
//
//if the sent address is NULL the function does nothing
//
template <typename T>
void FLQueue<T>::clearChain(const Node<T>* firstNode)
{
	if (firstNode)
	{
		const Node<T>* current = firstNode;
		const Node<T>* oldNode = firstNode;

		//while there is an actual node to delete
		while (current)
		{
			//save current's address
			oldNode = current;

			//move forward in the chain
			current = current->next;

			//free old
			delete oldNode;
		}
	}
}



//-------------------------------------------------------------------------------------------
//
//CTORS
//


//
//Queue is empty when constructed
//
template <typename T>
FLQueue<T>::FLQueue()
	:
	head(NULL),
	tail(NULL)
{
	;
}



//
//reconstruct other's chain of nodes
//
//if other is empty, just leave 
//(members stay NULL)
//
template <typename T>
FLQueue<T>::FLQueue(const FLQueue<T>& other)
	:
	head(NULL),
	tail(NULL)
{
	//if other is not empty, reconstruct its chain
	if (!other.isEmpty())
	{
		//a pointer to save the end of the new chain
		Node<T>* endOfChain = NULL;

		//clone other list's chain of nodes
		Node<T>* newChain = cloneChain(other.head, &endOfChain);

		//attach the cloned chain
		this->head = newChain;
		
		assert(endOfChain);

		//set tail
		this->tail = endOfChain;
	}
}


//
//clear the chain of nodes
//
template <typename T>
FLQueue<T>::~FLQueue()
{
	clearChain(head);
}



template <typename T>
FLQueue<T>& FLQueue<T>::operator=(const FLQueue<T>& other)
{
	if (this != &other)
	{
		//reconstruct other's chain in temp
		FLQueue<T> temp(other);

		//swap chains
		std::swap(this->head, temp.head);
		std::swap(this->tail, temp.tail);
	}

	return *this;
}



//-------------------------------------------------------------------------------------------
//
//OTHER
//


//
//the queue is empty when the head points to NULL
//
template <typename T>
bool FLQueue<T>::isEmpty()const
{
	return head == NULL;
}


//
//add it to the end of the chain
//
template <typename T>
void FLQueue<T>::enqueue(const T& data)
{
	Node<T>* newNode = new Node<T>(data);
	
	//if the queue is not empty,
	//attach it to the tail node
	if (!isEmpty())
	{
		tail->next = newNode;
	}
	else // add it as a head node
	{
		head = newNode;
	}

	//update tail
	tail = newNode;
}


//
//remove the head node 
//(it is the one that has been in the queue the longest)
//and return its data
//
// \ if the queue is empty
//   std::logic_error is thrown
//
template <typename T>
T FLQueue<T>::dequeue()
{
	if (isEmpty())
		throw std::logic_error("Queue is empty!");

	//keep the address of the old head node
	Node<T>* oldHead = head;

	//move head to the next node in the chain
	head = head->next;

	//if this was the only node in the chain
	if (head == NULL)
	{
		//update tail to be NULL too
		tail = NULL;
	}

	//keep its data
	T data(oldHead->data);

	//free old head
	delete oldHead;

	return data;
}



//
//access the first object in the queue
//
// \ if the queue is empty
//   std::logic_error is thrown
//
template <typename T>
T FLQueue<T>::peek()const
{
	if (isEmpty())
		throw std::logic_error("Queue is empty!");

	return head->data;
}

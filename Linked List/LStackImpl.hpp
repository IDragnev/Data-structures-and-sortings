
//
//the stack is empty if the top is NULL
//
template <typename T>
bool LStack<T>::isEmpty()const
{
	return top == NULL;
}


template <typename T>
T LStack<T>::pop()
{
	//get the value of the current top
	T temp = peek();

	//save old top
	Node<T>* oldTop = top;

	//move top forward
	top = top->next;

	//free old top
	delete oldTop;

	return temp;
}


template <typename T>
void LStack<T>::push(const T& value)
{
	//make the new node
	Node<T>* newTop = new Node<T>(value, top);

	//set as top
	top = newTop;
}


template <typename T>
const T& LStack<T>::peek()const
{
	if (isEmpty())
		throw std::underflow_error("Stack is empty!");

	return top->data;
}


//-----------------------------------------------------------------------------
//
//CTORS
//


//
//set top as NULL
//
template <typename T>
LStack<T>::LStack()
	:
	top(NULL)
{
	;
}


template <typename T>
LStack<T>::LStack(const LStack<T>& other)
	:
	top(NULL)
{
	copyFrom(other);
}


template <typename T>
LStack<T>& LStack<T>::operator=(const LStack<T>& other)
{
	if (this != &other)
	{
		copyFrom(other);
	}

	return *this;
}

//
//free the chain of nodes
//
template <typename T>
LStack<T>::~LStack()
{
	clearChain(top);
}



//-----------------------------------------------------------------------------
//
//UTILITY
//



//
//clone a chain by its first node
//
//if bad allocation occurs, the chain is cleared
//and exception is rethrown
//
template <typename T>
Node<T>* LStack<T>::cloneChain(const Node<T>* firstNode)
{
	assert(firstNode);
	Node<T>* newChain = NULL;

	try
	{
		//pointer to the start of the new chain
		newChain = new Node<T>(firstNode->data);

		//pointer to the node we will copy next (initially points to the second node of the sent chain)
		const Node<T>* readFrom = firstNode->next;

		//pointer to the node to which we will attach the next node
		Node<T>* attachTo = newChain;

		//while there is an actual node to copy from
		while (readFrom)
		{
			//attach new node
			attachTo->next = new Node<T>(readFrom->data);

			//move to current end of chain
			attachTo = attachTo->next;

			//move to the next node to be copied
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
//clear a chain of nodes
//by the address of its first node
//
template <typename T>
void LStack<T>::clearChain(const Node<T>* firstNode)
{
	if (firstNode)
	{
		const Node<T>* current = firstNode;
		const Node<T>* oldNode = firstNode;

		//while there is an actual node to delete
		while (current)
		{
			//save the address of the current node
			oldNode = current;

			//move current forward
			current = current->next;

			//free old
			delete oldNode;
		}
	}
}


template <typename T>
void LStack<T>::clear()
{
	clearChain(top);

	top = NULL;
}


//
//if other is empty
//empty the stack and leave
//
//else clear current chain 
//and reconstruct other's chain
//
template <typename T>
void LStack<T>::copyFrom(const LStack<T>& other)
{
	if (other.isEmpty())
	{
		clear();
	}
	else
	{
		//clone other's chain
		Node<T>* newChain = cloneChain(other.top);

		//clear current chain
		clear();

		//update chain
		top = newChain;
	}
}
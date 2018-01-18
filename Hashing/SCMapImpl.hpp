
template <typename Item, typename Key, typename HashFun>
template <typename T, typename K>
SCMap<Item,Key,HashFun>::Node<T, K>::Node(const T& it, const K& key, Node<T, K>* next)
	:
	item(it),
	key(key),
	next(next)
{
	;
}



template <typename Item, typename Key, typename HashFun>
int SCMap<Item, Key, HashFun>::getCount()const
{
	return count;
}


template <typename Item,typename Key, typename HashFun>
bool SCMap<Item, Key, HashFun>::isEmpty()const
{
	return count == 0;
}




//
//clear a chain of nodes
//
// \ if the sent pointer is nullptr
//   the function does nothing
//
template <typename Item, typename Key, typename HashFun>
void SCMap<Item, Key, HashFun>::clearChain(Node<Item, Key>* first)
{
	//if non-empty
	if (first)
	{
		Node<Item, Key>* old = first;

		//while there is a node to delete
		while (first)
		{
			//save its address
			old = first;

			//move forward in the chain
			first = first->next;

			//delete it
			delete old;
		}
	}
}



//
//clone a chain of nodes
//
// \ the function might throw std::bad_alloc
//
template <typename Item, typename Key, typename HashFun>
SCMap<Item, Key, HashFun>::Node<Item, Key>* SCMap<Item, Key, HashFun>::cloneChain(const Node<Item, Key>* first)
{
	Node<Item, Key>* newChain = nullptr;
	assert(first);

	try
	{
		//the new chain
		newChain = new Node<Item, Key>(first->item, first->key);

		//the node we will copy next (initially points to the second node of the sent chain)
		const Node<Item, Key>* readFrom = first->next;

		//the node to which we will attach the coppied node (initially points to the first node of the new chain)
		Node<Item, Key>* attachTo = newChain;

		//while there is a node to copy
		while (readFrom)
		{
			assert(attachTo && attachTo->next == nullptr);
			attachTo->next = new Node<Item, Key>(readFrom->item, readFrom->key);

			//move forward in the original chain
			readFrom = readFrom->next;

			//move to the new end of the result chain
			attachTo = attachTo->next;
		}

		return newChain;
	}
	catch (std::bad_alloc&)
	{
		clearChain(newChain);

		throw;
	}
}


 
//
//insert an item with its key in the appropriate list
//
template <typename Item, typename Key, typename HashFun>
void SCMap<Item, Key, HashFun>::insert(const Item& item, const Key& key)
{
	int hash = hashFunction(key) % size;

	chains[hash] = new Node<Item, Key>(item, key, chains[hash]);

	++count;
}



//
//remove an item by a sent key
//
// \if no match is found, the function does nothing
//
template <typename Item, typename Key, typename HashFun>
void SCMap<Item, Key, HashFun>::remove(const Key& key)
{
	int hash = hashFunction(key) % size;

	//find the corresponding list
	Node<Item, Key>* list = chains[hash];

	Node<Item, Key>* prev = list;

	//while in the list and on a node with a diff. key
	while (list && list->key != key)
	{
		//save the one before it
		prev = list;

		//move to the next node
		list = list->next;
	}

	//if a match was found
	if (list)
	{
		//if it is the head node of the list
		if (list = chains[hash])                                   ///TO DO
		{
			chains[hash] = chains[hash]->next;
		}
		else
		{
			//unchain it
			prev->next = list->next;
		}

		//and delete the node
		delete list;

		//update count
		--count;
	}
}
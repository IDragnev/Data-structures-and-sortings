
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


template <typename Item, typename Key, typename HashFun>
void SCMap<Item, Key, HashFun>::setSize(int Size)
{
	if (Size > 0)
	{
		size = Size
	}
	else
		throw std::invalid_argument("Size must be positive!");	
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
		if (list == chains[hash])                                  
		{
			chains[hash] = list->next;
		}
		else 
		{
			assert(prev->next == list);
			//unchain it
			prev->next = list->next;
		}

		//and delete the node
		delete list;

		//update count
		--count;
	}
}




//
//get an item by a sent key
//
// \ if no match is found, nullptr is returned
//
template <typename Item, typename Key, typename HashFun>
Item* SCMap<Item, Key, HashFun>::search(const Key& key)
{
	Node<Item, Key>* current = chains[hashFunction(key) % size];

	//while in the list and on a node with a diff. key
	while (current && current->key != key)
	{
		//move to the next node
		current = current->next;
	}

	return current;
}



template <typename Item, typename Key, typename HashFun>
void SCMap<Item, Key, HashFun>::clear()
{
	//if not empty
	if (chains)
	{
		//clear the lists
		for (int i = 0; i < size; ++i)
			clearChain(chains[i]);

		//and free the array of pointers
		delete[] chains;
	}
}




//
//set count to 0 and
//alloc. size empty lists
//
template <typename Item, typename Key, typename HashFun>
SCMap<Item, Key, HashFun>::SCMap(int size)
	:
	count(0),
	chains(nullptr)
{
	setSize(size);

	chains = new Node<Item, Key>*[size] {nullptr};
}



template <typename Item, typename Key, typename HashFun>
SCMap<Item, Key, HashFun>::~SCMap()
{
	clear();
}



template <typename Item, typename Key, typename HashFun>
SCMap<Item, Key, HashFun>::SCMap(const SCMap& other)
	:
	chains(nullptr),
	count(other.count)
{
	setSize(other.size);

	try
	{
		chains = new Node<Item, Key>*[size] {nullptr};

		for (int i = 0; i < size; ++i)
			chains[i] = cloneChain(other.chains[i]);
	}
	catch (std::bad_alloc&)
	{
		clear();
		throw;
	}
}



template <typename Item, typename Key, typename HashFun>
SCMap<Item,Key,HashFun>& SCMap<Item, Key, HashFun>::operator=(const SCMap& other)
{
	if (this != &other)
	{
		//copy-construct other in temp
		SCMap temp(other);

		//swap data with temp and leave temp destroy old data
		std::swap(this->chains, temp.chains);
		std::swap(this->count, temp.count);
		std::swap(this->size, temp.size);
	}

	return *this;
}
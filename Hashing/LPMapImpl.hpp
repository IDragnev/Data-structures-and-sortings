
template <typename HashFun>
void LPMap<HashFun>::setSize(int size)
{
	if (size > 0)
		this->size = size;
	else
		throw std::invalid_argument("Size must be positive!");
}


template <typename HashFun>
bool LPMap<HashFun>::isEmpty()const
{
	return count == 0;
}


template <typename HashFun>
int LPMap<HashFun>::getCount()const
{
	return count;
}


//
//the table is full when there is exactly
//one empty position left
//
template <typename HashFun>
bool LPMap<HashFun>::isFull()const
{
	return count + 1 == size;
}



//
//alloc. with 4/3* the sent size ( size + 1/3*size)
//in order to leave the table potentially 
// 2/3 full after all insertions 
//
template <typename HashFun>
LPMap<HashFun>::LPMap(int expectedSize)
	:
	items(nullptr),
	count(0)
{
	setSize((4 * expectedSize) / 3);

	items = new Item[size];
}



//
//since nulls can be anywhere
//copy the whole array
//
template <typename HashFun>
LPMap<HashFun>::LPMap(const LPMap<HashFun>& other)
	:
	items(nullptr),
	count(other.count)
{
	setSize(other.size);

	//all are null by default
	items = new Item[size];

	for (int i = 0; i < size; ++i)
		items[i] = other.items[i];
}



//
//reconstruct other in temp, then
//swap data with temp and leave temp destroy old data
//
template <typename HashFun>
LPMap<HashFun>& LPMap<HashFun>::operator=(const LPMap<HashFun>& other)
{
	if (this != &other)
	{
		LPMap<HashFun> temp(other);

		std::swap(this->items, temp.items);
		std::swap(this->size, temp.size);
		std::swap(this->count, temp.count);
	}

	return *this;
}



template <typename HashFun>
LPMap<HashFun>::~LPMap()
{
	delete[] items;
}



//
//if not full, find the first empty position starting 
//from the hash and insert it 
//
template <typename HashFun>
void LPMap<HashFun>::insert(const Item& item)
{
	if (!isFull())
	{
		int hash = hashFunction(item.getKey()) % size;

		//find a null position
		while (!items[hash].isNull())
			hash = (hash + 1) % size;

		items[hash] = item;
		++count;
	}
}



template <typename HashFun>
Item LPMap<HashFun>::search(char key)const
{
	//starting from the hash
	int hash = hashFunction(key) % size;

	//until a null position is reached
	while (!items[hash].isNull())
	{
		//if the cur. item's key is the one we are searching for
		if (items[hash].getKey() == key)
			return items[hash];

		hash = (hash + 1) % size;
	}

	//return a null item
	return Item();
}



//
//null the specified item and rehash
//the items after it which are in the same cluster
//
template <typename HashFun>
void LPMap<HashFun>::remove(char key)
{
	int hash = hashFunction(key) % size;

	//until either a null item or the specified item is reached
	while (!items[hash].isNull() && items[hash].getKey() != key)
		hash = (hash + 1) % size;

	//if no such item was found, just leave
	if (items[hash].isNull()) return;

	//null it and update count
	items[hash].makeNull();
	--count;

	//go to the next item
	hash = (hash + 1) % size;

	//until an empty spot is reached
	for (; !items[hash].isNull(); hash = (hash + 1) % size)
	{
		//save current item
		Item temp(items[hash]);

		//null it and decrement count
		items[hash].makeNull();
		--count;
		
		//reinsert
		insert(temp);
	}
}
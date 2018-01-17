

template <typename Item, typename Key, typename HashFun>
Hash<Item, Key, HashFun>::Hash(int size)
	:
	size(size),
	count(0)
{
	;
}


template <typename Item, typename Key, typename HashFun>
int Hash<Item, Key, HashFun>::getCount()const
{
	return count;
}

template <typename Item, typename Key, typename HashFun>
bool Hash<Item, Key, HashFun>::isEmpty()const
{
	return count == 0;
}

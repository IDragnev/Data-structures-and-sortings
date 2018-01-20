

template <typename Key>
int HashFunction<Key>::operator(const Key& key)
{
	return calculateHash(key);
}
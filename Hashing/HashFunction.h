#ifndef __HASH_FUN_BASE_H_INCLUDED__
#define __HASH_FUN_BASE_H_INCLUDED__

template <typename Key>
class HashFunction
{
public:
	HashFunction() = default;
	HashFunction(const HashFunction<Key>&) = default;
	virtual ~HashFunction() = default;

	HashFunction<Key>& operator=(const HashFunction<Key>&) = default;

public:
	int operator()(const Key& key)const;

protected:
	virtual int calculateHash(const Key& key)const = 0;
};


template <typename Key>
int HashFunction<Key>::operator()(const Key& key)const
{
	return calculateHash(key);
}

#endif //__HASH_FUN_BASE_H_INCLUDED__
#ifndef __HASH_ADT_BASE_H_INCLUDED__
#define __HASH_ADT_BASE_H_INCLUDED__

#include "HashFunction.h"

template <typename Item, typename Key, typename HashFun>
class Hash
{
public:
	Hash(int size);
	Hash(const Hash<Item, Key, HashFun>&) = default;
	virtual ~Hash() = default;

	Hash<Item, Key, HashFun>& operator=(const Hash<Item, Key, HashFun>&) = default;
	
	int getCount()const;
	bool isEmpty()const;

	virtual void insert(const Item&, const Key&) = 0;
	virtual void remove(const Key&) = 0;
	virtual Item& search(const Key&) = 0;
	virtual const Item& search(const Key&)const = 0;

protected:
	int count;
	int size;
	HashFun function;
};

#include "HashImpl.hpp"
#endif //__HASH_ADT_BASE_H_INCLUDED__
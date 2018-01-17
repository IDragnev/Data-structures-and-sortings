#ifndef __HASH_SIMPLE_ADT_BASE_H_INCLUDED__
#define __HASH_SIMPLE_ADT_BASE_H_INCLUDED__

#include "HashFunction.h"

template <typename T>
class Hash
{
public:
	Hash(HashFunction<T>* function);
	Hash(const Hash<T>&) = default;
	virtual ~Hash() = default;

	Hash<T>& operator=(const Hash<T>&) = default;

	virtual void insert(const T&) = 0;
	virtual void remove(const T&) = 0;
	virtual bool search(const T&) = 0;

private:
	HashFunction<T>* function;
};

#include "HashImpl.hpp"
#endif //__HASH_SIMPLE_ADT_BASE_H_INCLUDED__
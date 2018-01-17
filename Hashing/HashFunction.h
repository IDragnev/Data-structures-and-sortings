#ifndef __HASH_FUN_BASE_H_INCLUDED__
#define __HASH_FUN_BASE_H_INCLUDED__

template <typename T>
class HashFunction
{
public:
	HashFunction() = default;
	HashFunction(const HashFunction<T>&) = default;
	virtual ~HashFunction() = default;

	HashFunction<T>& operator=(const HashFunction<T>&) = default;

	virtual int calculateHash(const T& key) = 0;
};


#endif //__HASH_FUN_BASE_H_INCLUDED__
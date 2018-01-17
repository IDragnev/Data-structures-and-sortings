#ifndef __MODULO_HASH_FUN_H_INCLUDED__
#define __MODULO_HASH_FUN_H_INCLUDED__

#include "HashFunction.h"

template <typename T>
class ModuloHashFunction : public HashFunction<T>
{
public:
	ModuloHashFunction(int modulo);
	ModuloHashFunction(const ModuloHashFunction<T>&) = default;
	virtual ~ModuloHashFunction()override = default;

	ModuloHashFunction<T>& operator=(const ModuloHashFunction<T>&) = default;

	virtual int calculateHash(const T& key)override;

private:
	int modulo;
};

#include "ModuloHashFunctionImpl.hpp"
#endif //__MODULO_HASH_FUN_H_INCLUDED__
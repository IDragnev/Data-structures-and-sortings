#ifndef __MODULO_HASH_FUN_H_INCLUDED__
#define __MODULO_HASH_FUN_H_INCLUDED__

#include "HashFunction.h"

template <typename T>
class ModuloHashFunction : public HashFunction<T>
{
public:
	ModuloHashFunction(int modulo = 9);
	ModuloHashFunction(const ModuloHashFunction<T>&) = default;
	virtual ~ModuloHashFunction()override = default;

	ModuloHashFunction<T>& operator=(const ModuloHashFunction<T>&) = default;

protected:
	virtual int calculateHash(const T& key)const override;

private:
	int modulo;
};

#include "ModuloHashFunctionImpl.hpp"
#endif //__MODULO_HASH_FUN_H_INCLUDED__
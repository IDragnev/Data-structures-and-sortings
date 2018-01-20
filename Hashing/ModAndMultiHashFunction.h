#ifndef __MOD_AND_MULT_HASH_FUNCTION_H_INCLUDED__
#define __MOD_AND_MULT_HASH_FUNCTION_H_INCLUDED__

#include "HashFunction.h"

template <typename T>
class ModAndMultiHashFunction : public HashFunction<T>
{
public:
	ModAndMultiHashFunction(int mod = 9, int multi = 3);
	ModAndMultiHashFunction(const ModAndMultiHashFunction<T>&) = default;
	virtual ~ModAndMultiHashFunction()override = default;

	ModAndMultiHashFunction<T>& operator=(const ModAndMultiHashFunction<T>&) = default;

protected:
	virtual int calculateHash(const T& key)const override;

private:
	int modulo;
	int multiplier;
};

#include "ModAndMultiHashFunctionImpl.hpp"
#endif //__MOD_AND_MULT_HASH_FUNCTION_H_INCLUDED__
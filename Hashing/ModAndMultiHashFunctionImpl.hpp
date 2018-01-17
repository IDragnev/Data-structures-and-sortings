


template <typename T>
ModAndMultiHashFunction<T>::ModAndMultiHashFunction(int mod, int multi)
	:
	modulo(mod),
	multiplier(multi)
{
	;
}


template <>
int ModAndMultiHashFunction<int>::calculateHash(const int& key)
{
	return (key % modulo) * multiplier;
}
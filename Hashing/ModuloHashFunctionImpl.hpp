

template <typename T>
ModuloHashFunction<T>::ModuloHashFunction(int modulo)
	:
	modulo(modulo)
{
	;
}


template <>
int ModuloHashFunction<int>::calculateHash(const int& key)
{
	return key & modulo;
}

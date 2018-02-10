


template <typename T>
inline uniquePtr<T>::uniquePtr(T* ptr)
	:
	ptr(ptr)
{
	;
}



//
// move constructor 
// 
// transfers ownership of a managed resource into the current object
//
template <typename T>
inline uniquePtr<T>::uniquePtr(uniquePtr&& source)
	:
	ptr(source.ptr)
{
	source.ptr = nullptr;
}



//
// move assignment operator
//
// since uniquePtr is a move-only type
// operator= is taking by value, this way
// using the move constructor to initialize source parameter
// from an rvalue argument
//
// resources are swapped and source destroys the old memory
//
template <typename T>
uniquePtr<T>& uniquePtr<T>::operator=(uniquePtr<T> source)
{
	std::swap(this->ptr, source.ptr);

	return *this;
}



template <typename T>
inline uniquePtr<T>::~uniquePtr()
{
	delete ptr;
}



template <typename T>
inline T* uniquePtr<T>::operator->()
{
	return ptr;
}


template <typename T>
inline T& uniquePtr<T>::operator*()
{
	return *ptr;
}


template <typename T>
inline uniquePtr<T>::operator bool()const
{
	return ptr;
}


template <typename T>
inline bool uniquePtr<T>::operator!()const
{
	return !ptr;
}
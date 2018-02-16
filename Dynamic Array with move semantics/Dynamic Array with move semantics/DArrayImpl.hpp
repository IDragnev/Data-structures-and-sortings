
//-------------------------------------------------------------------------------------------------------------
//
//GET AND SET
//


template <typename T>
inline int DArray<T>::getCount()const
{
	return count;
}


template <typename T>
inline int DArray<T>::getSize()const
{
	return size;
}


template <typename T>
inline bool DArray<T>::isEmpty()const
{
	return count == 0;
}



template <typename T>
inline T* DArray<T>::data()
{
	return data;
}


template <typename T>
inline const T* DArray<T>::data()const
{
	return data;
}



template <typename T>
void DArray<T>::setCount(int newCount)
{
	if (newCount < 0 || newCount > size)
		throw std::invalid_argument("Count must be between 0 and size");

	count = newCount;
}


template <typename T>
void DArray<T>::setSize(int newSize)
{
	if (newSize < 0)
		throw std::invalid_argument("Size cannot be negative");

	size = newSize;
}


//----------------------------------------------------------------------------------------
//
// UTILITY
//



template <typename T>
inline void DArray<T>::directInit(T* nData, int nCount, int nSize)
{
	data = nData;
	count = nCount;
	size = nSize;
}


template <typename T>
inline void DArray<T>::null()
{
	directInit(nullptr, 0, 0);
}


template <typename T>
inline void DArray<T>::destroy()
{
	delete[] data;
}


//
//free memory and null members
//
template <typename T>
inline void DArray<T>::clear()
{
	destroy();
	null();
}


//
// if other is not empty, copy its data
// else clear current content
//
template <typename T>
void DArray<T>::copy(const DArray<T>& other)
{
	if (!other.isEmpty())
	{
		T* buffer = new T[other.size];

		for (int i = 0; i < other.count; ++i)
			buffer[i] = other.data[i];

		destroy();

		directInit(buffer, other.count, other.size);
	}
	else //empty
	{
		clear();
	}
}



//
//resize with the sent size
//
// \ if the array is null-empty, then count will be 0 
//   and the null pointer will not be touched
//
template <typename T>
void DArray<T>::resize(int newSize)
{
	T* newData = new T[newSize];

	//if newSize is smaller than count, it is the new count
	int newCount = (count <= newSize) ? count : newSize;

	//copy needed objects
	for (int i = 0; i < newCount; ++i)
		newData[i] = data[i];

	destroy();

	directInit(newData, newCount, newSize);
}




//
//resize if full
//
template <typename T>
inline void DArray<T>::checkSpace()
{
	if (count == size)
		resize((2 * size) > 0 ? (2 * size) : 8;);
}




//
//shift objects in [start, .. , end] one position to the left
//
template <typename T>
inline void DArray<T>::shiftLeft(int start, int end)
{
	assert(start > 0);

	while (start < end)
	{
		data[start - 1] = data[start];
		++start;
	}
}



//
//shift objects in [start, .. , end] one position to the right
//
//the function assumes that count < size (checkSpace() will already be called)
//
template <typename T>
inline void DArray<T>::shiftRight(int start, int end)
{
	//end can be at most the last 'valid' object
	assert(end < count);

	while (end > start)
	{
		data[end + 1] = data[end];
		--end;
	}
}





//---------------------------------------------------------------------------------
//
//OTHER
//


template <typename T>
inline void DArray<T>::empty()
{
	count = 0;
}



//
//resize with the sent size
//
//if the sent size is not greater
//than current size, the function does nothing
//
template <typename T>
inline void DArray<T>::ensureSize(int newSize)
{
	if (newSize > size)
		resize(newSize);
}


//
//shrink the array to the sent size
//
// \ newSize must be at least 0 and fewer than current size
//
template <typename T>
inline void DArray<T>::shrink(int newSize)
{
	if (newSize < 0 || newSize >= size)
		throw std::invalid_argument("Invalid size sent");

	if (newSize == 0)
		clear();
	else
		resize(newSize);
}





//---------------------------------------------------------------------------------------------
//
//SPECIAL MEMBERS
//


//
//null-empty by default
//
template <typename T>
DArray<T>::DArray()
	:
	data(nullptr),
	count(0),
	size(0)
{
	;
}



template <typename T>
DArray<T>::DArray(int size, int count)
	:
	data(nullptr)
{
	setSize(size);
	setCount(count);

	if (size > 0)
		data = new T[size];
}



//
//move constructor
//
//steal source's data and then null it
//
template <typename T>
DArray<T>::DArray(DArray<T>&& source)
	:
	data(source.data),
	count(source.count),
	size(source.size)
{
	source.null();
}



template <typename T>
DArray<T>::DArray(const DArray<T>& other)
	:
	data(nullptr)
{
	copy(other);
}



//
// copy assignment
//
// copy() frees old memory (if any)
//
template <typename T>
DArray<T>& DArray<T>::operator=(const DArray<T>& other)
{
	if (this != &other)
	{
		copy(other);
	}

	return *this;
}



//
// move assignment
//
// free old data, 'steal' source's data and then null it
//
template <typename T>
DArray<T>& DArray<T>::operator=(DArray<T>&& source)
{
	if (this != &other)
	{
		destroy();
		directInit(source.data, source.count, source.size);
		source.null();
	}

	return *this;
}




template <typename T>
DArray<T>::~DArray()
{
	destroy();
}
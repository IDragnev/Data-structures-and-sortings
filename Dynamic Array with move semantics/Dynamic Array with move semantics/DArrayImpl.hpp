
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
inline T* DArray<T>::getData()
{
	return data;
}


template <typename T>
inline const T* DArray<T>::getData()const
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
inline void DArray<T>::directInit(T* newData, int newCount, int newSize)
{
	data = newData;
	count = newCount;
	size = newSize;
}


template <typename T>
inline void DArray<T>::nullMembers()
{
	directInit(nullptr, 0, 0);
}


template <typename T>
inline void DArray<T>::destroyData()
{
	delete[] data;
}



template <typename T>
inline void DArray<T>::destroyAndNullAll()
{
	destroyData();
	nullMembers();
}



template <typename T>
void DArray<T>::copyFrom(const DArray<T>& other)
{
	if (!other.isEmpty())
	{
		T* buffer = new T[other.size];

		for (int i = 0; i < other.count; ++i)
			buffer[i] = other.data[i];

		destroyData();

		directInit(buffer, other.count, other.size);
	}
	else 
	{
		destroyAndNullAll();
	}
}



//
// (!) if data == nullptr, then count will be 0 
//   and the null pointer will not be touched
//
template <typename T>
void DArray<T>::resize(int newSize)
{
	T* newData = new T[newSize];

	int newCount = (count <= newSize) ? count : newSize;

	for (int i = 0; i < newCount; ++i)
		newData[i] = data[i];

	destroyData();

	directInit(newData, newCount, newSize);
}


template <typename T>
inline void DArray<T>::resizeIfNeeded()
{
	if (count == size)
		resize((2 * size) > 0 ? (2 * size) : 8);
}



//
//shift objects in [start, .. , end] one position to the left
//
template <typename T>
inline void DArray<T>::shiftLeft(int start, int end)
{
	assert(start > 0);

	while (start <= end)
	{
		data[start - 1] = data[start];
		++start;
	}
}



//
//shift objects in [start, .. , end] one position to the right
//
// (!) the function assumes that count < size (resizeIfNeeded() will have already been called)
//
template <typename T>
inline void DArray<T>::shiftRight(int start, int end)
{
	assert(end < count);

	while (end >= start)
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



template <typename T>
inline void DArray<T>::ensureSize(int newSize)
{
	if (newSize > size)
		resize(newSize);
}



template <typename T>
inline void DArray<T>::shrink(int newSize)
{
	if (newSize < 0 || newSize >= size)
		throw std::invalid_argument("Invalid size sent");

	if (newSize == 0)
		destroyAndNullAll();
	else
		resize(newSize);
}





//---------------------------------------------------------------------------------------------
//
//SPECIAL MEMBERS
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
DArray<T>::DArray(int Size, int Count)
	:
	data(nullptr)
{
	setSize(Size);
	setCount(Count);

	if (size > 0)
		data = new T[size];
}



//
//move constructor
//
template <typename T>
DArray<T>::DArray(DArray<T>&& source)
	:
	data(source.data),
	count(source.count),
	size(source.size)
{
	source.nullMembers();
}



template <typename T>
DArray<T>::DArray(const DArray<T>& other)
	:
	data(nullptr)
{
	copyFrom(other);
}



//
//copy assignment
//
// (!) copyFrom() frees old memory (if any)
//
template <typename T>
DArray<T>& DArray<T>::operator=(const DArray<T>& other)
{
	if (this != &other)
	{
		copyFrom(other);
	}

	return *this;
}



//
//move assignment
//
template <typename T>
DArray<T>& DArray<T>::operator=(DArray<T>&& source)
{
	if (this != &source)
	{
		destroyData();
		directInit(source.data, source.count, source.size);
		source.nullMembers();
	}

	return *this;
}




template <typename T>
DArray<T>::~DArray()
{
	destroyData();
}



//---------------------------------------------------------------------------------------------------------------------------------
//
// ADDING AND REMOVAL
//


//
//adding an lvalue
//
template <typename T>
void DArray<T>::add(const T& item)
{
	resizeIfNeeded();

	data[count++] = item;
}


//
//adding an rvalue
//
template <typename T>
void DArray<T>::add(T&& item)
{
	resizeIfNeeded();

	data[count++] = std::move(item);
} 



template <typename T>
void DArray<T>::addAt(int position, const T& item)
{
	if (position < 0 || position >= count)
		throw std::out_of_range("Index out of range");

	resizeIfNeeded();

	//empty the position
	shiftRight(position, count - 1);

	data[position] = item;
	++count;
}



template <typename T>
void DArray<T>::addAt(int position, T&& item)
{
	if (position < 0 || position >= count)
		throw std::out_of_range("Index out of range");

	resizeIfNeeded();

	//empty the position
	shiftRight(position, count - 1);

	data[position] = std::move(item);
	++count;
}



template <typename T>
void DArray<T>::remove(int position)
{
	if (position < 0 || position >= count)
		throw std::out_of_range("Index out of range");

	//shift objects after it one pos. to the left
	shiftLeft(position + 1, count - 1);

	--count;
}



template <typename T>
int DArray<T>::find(const T& val)const
{
	for (int i = 0; i < count; ++i)
	{
		if (data[i] == val)
			return i;
	}

	return -1;
}



template <typename T>
T& DArray<T>::operator[](int index)
{
	if (index < 0 || index >= count)
		throw std::out_of_range("Index out of range");

	return data[index];
}



template <typename T>
const T& DArray<T>::operator[](int index)const
{
	if (index < 0 || index >= count)
		throw std::out_of_range("Index out of range");

	return data[index];
}


template <typename T>
void DArray<T>::append(const DArray<T>& other)
{
	for (int i = 0; i < other.count; ++i)
		add(other[i]);
}


template <typename T>
void DArray<T>::append(DArray<T>&& other)
{
	for (int i = 0; i < other.count; ++i)
		add(std::move(other[i]));

	other.nullMembers();
}
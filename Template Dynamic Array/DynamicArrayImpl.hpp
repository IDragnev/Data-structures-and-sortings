
//----------------------------------------------------------------------------------
//
//GET AND SET
//


template <typename T>
bool DynamicArray<T>::isEmpty()const
{
	return count == 0;
}

template <typename T>
T* DynamicArray<T>::getData()
{
	return data;
}

template <typename T>
const T* DynamicArray<T>::getData()const
{
	return data;
}


template <typename T>
int DynamicArray<T>::getCount()const
{
	return count;
}


template <typename T>
int DynamicArray<T>::getSize()const
{
	return size;
}


template <typename T>
void DynamicArray<T>::setSize(int newSize)
{
	if (newSize <= 0)
		throw std::invalid_argument("Size must be positive!");

	size = newSize;
}



template <typename T>
void DynamicArray<T>::setCount(int newCount)
{
	if (newCount < 0 || newCount > size)
		throw std::invalid_argument("Count must be between 0 and size!");

	count = newCount;
}



template <typename T>
T& DynamicArray<T>::getAt(int position)
{
	if (position < 0 || position >= count)
		throw std::out_of_range("Index out of range!");

	return data[position];
}



template <typename T>
const T& DynamicArray<T>::getAt(int position)const
{
	if (position < 0 || position >= count)
		throw std::out_of_range("Index out of range!");

	return data[position];
}


//----------------------------------------------------------------------------------
//
//UTILITY
//


//find the nearest power of two (bigger than 'number')
template <typename T>
int DynamicArray<T>::findNearestPowTwo(int number)
{
	int result = 2;

	while (result <= number)
		result *= 2;

	return result;
}



template <typename T>
void DynamicArray<T>::clear()
{
	delete[] data;
	data = NULL;
}



template <typename T>
void DynamicArray<T>::copyFrom(const DynamicArray<T>& other)
{
	//allocate a buffer of other's size (filled with default objects)
	T* temp = new T[other.size];

	//copy other's objects
	for (int i = 0; i < other.count; ++i)
		temp[i] = other.data[i];

	//free memory
	clear();

	//update array,count and size
	data = temp;
	setSize(other.size);
	setCount(other.count);
}



template <typename T>
void DynamicArray<T>::resize(int newSize)
{
	//allocate a new array
	T* newData = new T[newSize];

	//if newSize is smaller than count, it is the new count
	int newCount = (count <= newSize) ? count : newSize;

	//copy needed objects
	for (int i = 0; i < newCount; ++i)
		newData[i] = data[i];
	
	//free old data
	clear();

	//update array,count and size
	data = newData;
	setCount(newCount);
	setSize(newSize);
}


//move each object from (beg + 1) to end
//one position to the left 
//beg is the first position in which we move an object (should be the 'empty' position)
//end is the last object we move one position to the left
template <typename T>
void DynamicArray<T>::shiftLeft(int beg, int end)
{
	while (beg < end)
	{
		data[beg] = data[beg + 1];
		beg++;
	}
}


//move each object from (end - 1) to beg
//one position to the right
//end is the first position in which we move an object (should be the 'empty' position)
//beg if the last object we move one position to the right
template <typename T>
void DynamicArray<T>::shiftRight(int beg, int end)
{
	while (end > beg)
	{
		data[end] = data[end - 1];
		end--;
	}
}


//----------------------------------------------------------------------------------
//
//CTORS
//

template <typename T>
void DynamicArray<T>::makeEmpty()
{
	//resize it to hold only one object
	resize(1);
	assert(count == 1);
	//decrement count to zero
	--count;
}

//set count and size 
//and allocate an array of default objects with this size
template <typename T>
DynamicArray<T>::DynamicArray(int size, int count)
	:
	data(NULL)
{
	setSize(size);
	setCount(count);
	data = new T[size];
}


template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
	:
	data(NULL)
{
	copyFrom(other);
	assert(count == other.count && size == other.size);
}


template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other)
{
	if (this != &other)
	{
		copyFrom(other);
	}

	return *this;
}



template <typename T>
DynamicArray<T>::~DynamicArray()
{
	clear();
}



//----------------------------------------------------------------------------------
//
//OTHER
//


template <typename T>
T& DynamicArray<T>::operator[](int position)
{
	return getAt(position);
}


template <typename T>
const T& DynamicArray<T>::operator[](int position)const
{
	return getAt(position);
}


template <typename T>
void DynamicArray<T>::checkSpace()
{
	if (count == size)
		resize(findNearestPowTwo(size));
}


template <typename T>
void DynamicArray<T>::add(const T& object)
{
	checkSpace();

	data[count++] = object;
}


template <typename T>
void DynamicArray<T>::addAt(const T& object, int position)
{
	if (position < 0 || position >= count)
		throw std::out_of_range("Index out of range!");

	checkSpace();

	//make space
	shiftRight(position, count);
	//insert it
	data[position] = object;
	//increase count
	++count;
}



template <typename T>
void DynamicArray<T>::remove(int position)
{
	if (position < 0 || position >= count)
		throw std::out_of_range("Index out of range!");

	//shift the objects after it one pos. to the left 
	//and decrease count
	shiftLeft(position, count);
	--count;
}




template <typename T>
DynamicArray<T>& DynamicArray<T>::operator+=(const T& object)
{
	add(object);

	return *this;
}



template <typename T>
DynamicArray<T>& DynamicArray<T>::operator+=(const DynamicArray<T>& other)
{
	for (int i = 0; i < other.count; ++i)
		add(other.getAt(i));

	return *this;
}



template <typename T>
DynamicArray<T> operator+(const DynamicArray<T>& arr1, const DynamicArray<T>& arr2)
{
	DynamicArray<T> temp(arr1);

	temp += arr2;

	return temp;
}



template <typename T>
DynamicArray<T> operator+(const DynamicArray<T>& arr, const T& object)
{
	DynamicArray<T> temp(arr);

	temp += object;

	return temp;
}



template <typename T>
std::ostream& operator<<(std::ostream& out, const DynamicArray<T>& arr)
{
	int count = arr.getCount();

	for (int i = 0; i < count; ++i)
		std::cout << arr[i] << ' ';

	return out;
}



template <typename T>
inline DynamicArray<T> operator+(const T& object, const DynamicArray<T>& arr)
{
	return arr + object;
}
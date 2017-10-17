

template <typename T>
OrderedDynamicArray<T>::OrderedDynamicArray(int size,int count)
	:
	DynamicArray<T>(size,count)
{
	;
}



template <typename T>
void OrderedDynamicArray<T>::add(const T& object)
{
	//resize if needed
	checkSpace();

	//the array
	T* data = getData();

	int i = 0;
	//move forward in the array
	while (i < getCount() && data[i] < object)
		++i;
	//make space for the new object
	if (getCount() != 0)
		shiftRight(i, getCount());
	//insert it
	data[i] = object;
	//increase count
	setCount(getCount() + 1);
}



template <typename T>
OrderedDynamicArray<T> operator+(const OrderedDynamicArray<T>& arr1, const OrderedDynamicArray<T>& arr2)
{
	OrderedDynamicArray<T> temp(arr1);

	temp += arr2;

	return temp;
}



template <typename T>
OrderedDynamicArray<T> operator+(const OrderedDynamicArray<T>& arr, const T& object)
{
	OrderedDynamicArray<T> temp(arr);

	temp += object;

	return temp;
}


template <typename T>
inline OrderedDynamicArray<T> operator+(const T& object, const OrderedDynamicArray<T>& arr)
{
	return arr + object;
}



template <typename T>
int OrderedDynamicArray<T>::find(const T& value)const
{
	//initial ends
	int left = 0;
	int right = getCount() - 1;

	const T* data = getData();

	while (left <= right)
	{
		int middle = (left + right) / 2;

		if (data[middle] == value)
		{
			return middle;
		}
		else if (data[middle] > value)
		{
			right = middle - 1;
		}
		else /*if (data[middle] < value)*/
		{
			left = middle + 1;
		}
	}

	return -1;
}
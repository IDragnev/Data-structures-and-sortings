

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
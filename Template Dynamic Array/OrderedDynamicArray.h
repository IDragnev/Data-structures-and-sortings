#ifndef __ORDERED_DYN_ARR_H__
#define __ORDERED_DYN_ARR_H__

#include "DynamicArray.h"


template <typename T>
class OrderedDynamicArray : public DynamicArray<T>
{
public:
	OrderedDynamicArray(int size = 16, int count = 0);
	OrderedDynamicArray(const OrderedDynamicArray<T>&) = default;
	virtual ~OrderedDynamicArray()override = default;

	OrderedDynamicArray<T>& operator=(const OrderedDynamicArray<T>&) = default;

	virtual int find(const T&)const override;                //search by value (binary search)
	virtual void add(const T&)override;                      //add an element to the array (insertion sort)

private:
	void addAt(const T&, int);                               //add the element at the exact position DISALLOWED
};


template <typename T>
OrderedDynamicArray<T> operator+(const OrderedDynamicArray<T>&, const OrderedDynamicArray<T>&);  //sum two arrays

template <typename T>
OrderedDynamicArray<T> operator+(const OrderedDynamicArray<T>&, const T&);

template <typename T>
OrderedDynamicArray<T> operator+(const T&, const OrderedDynamicArray<T>&);

#include "OrderedDynamicArrayImpl.hpp"

#endif //__ORDERED_DYN_ARR_H__
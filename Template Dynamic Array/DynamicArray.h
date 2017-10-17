#ifndef __TEMPL_DYN_ARR_H_INCLUDED__
#define __TEMPL_DYN_ARR_H_INCLUDED__

#include <iostream>
#include <stdexcept>
#include <assert.h>


template <typename T>
class DynamicArray
{
public:
	explicit DynamicArray(int size = 16, int count = 0);   //filled with default objects when constructed
	DynamicArray(const DynamicArray<T>&);    
	virtual ~DynamicArray();

	DynamicArray<T>& operator=(const DynamicArray<T>&);

	virtual void add(const T&);                            //add an element to the array (added as last)
	virtual void remove(int position);                     //remove an element by its position in the array (shifting used)
	virtual int find(const T&)const;                       //search by value (-1 if not found)

	void addAt(const T&, int);                             //add the element at the exact position (shifting used)

	int getSize()const;                                    //get the size of the array
	int getCount()const;                                   //get the count of the elements in the array
	bool isEmpty()const;                                   //is the array empty

	T& getAt(int position);                                //get an element by its position in the array
	const T& getAt(int position)const;                     //get an element by its position in the array (for reading only)

	void makeEmpty();                                      //make the array empty
	void ensureSize(int size);                             //resize with the sent size

public:
	T& operator[](int position);                           //get an element by its position in the array
	const T& operator[](int position)const;                //get an element by its position in the array (for reading only)
	 
	DynamicArray<T>& operator+=(const T&);                 //add an element to the array
	DynamicArray<T>& operator+=(const DynamicArray<T>&);   //add a whole other array (add all its elements to the array)

private:
	int size;                                              //the size of the array
	int count;                                             //the count of the elements in the array
	T* data;                                               //the actual array of elements

protected:
	void setSize(int);
	void setCount(int);
	
	void checkSpace();                                     //resize if needed

	void shiftLeft(int beg, int end);                      //shift objects left
	void shiftRight(int beg, int end);                     //shift objects right

	T* getData();                                          //get the array for subclasses
	const T* getData()const;                               //get the array for reading

private:
	void copyFrom(const DynamicArray<T>&);                 //copy from another array (reconstruct)
	void resize(int);                                     
	void clear();                                          //clear the array of elements
	int findNearestPowTwo(int num);                        //find the nearest power of 2 which is bigger than num (8->16, 54->64..)
};


template <typename T>
DynamicArray<T> operator+(const DynamicArray<T>&, const DynamicArray<T>&);  //sum two arrays

template <typename T>
DynamicArray<T> operator+(const DynamicArray<T>&, const T&);       

template <typename T>
DynamicArray<T> operator+(const T&, const DynamicArray<T>&);

template <typename T>
std::ostream& operator<<(std::ostream& out, const DynamicArray<T>&);        //print an array

#include "DynamicArrayImpl.hpp"


#endif //__TEMPL_DYN_ARR_H_INCLUDED__
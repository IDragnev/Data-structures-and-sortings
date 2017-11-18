#ifndef __TEMPL_DYN_ARR_H_INCLUDED__
#define __TEMPL_DYN_ARR_H_INCLUDED__

#include <iostream>
#include <stdexcept>
#include <assert.h>


template <typename T>
class DynamicArray
{
public:
	explicit DynamicArray(int size = 16, int count = 0);   
	DynamicArray(const DynamicArray<T>&);    
	virtual ~DynamicArray();

	DynamicArray<T>& operator=(const DynamicArray<T>&);

	virtual void add(const T&);                          
	virtual void remove(int position);                     
	virtual int find(const T&)const;                     

	void addAt(int, const T&);                             

	int getSize()const;                                  
	int getCount()const;                                 
	bool isEmpty()const;                                   

	T& getAt(int position);                                
	const T& getAt(int position)const;                    

	void makeEmpty();                                    
	void ensureSize(int size);                            

public:
	T& operator[](int position);                         
	const T& operator[](int position)const;                
	 
	DynamicArray<T>& operator+=(const T&);                 
	DynamicArray<T>& operator+=(const DynamicArray<T>&);   

private:
	int size;                                            
	int count;                                            
	T* data;                                               

protected:
	void setSize(int);
	void setCount(int);
	
	void checkSpace();                                    

	void shiftLeft(int beg, int end);                    
	void shiftRight(int beg, int end);                    

	T* getData();                                        
	const T* getData()const;                              

private:
	void copyFrom(const DynamicArray<T>&);                 
	void resize(int);                                     
	void clear();                                        
	int findNearestPowTwo(int num);                    
};


template <typename T>
DynamicArray<T> operator+(const DynamicArray<T>&, const DynamicArray<T>&);  

template <typename T>
DynamicArray<T> operator+(const DynamicArray<T>&, const T&);       

template <typename T>
DynamicArray<T> operator+(const T&, const DynamicArray<T>&);

template <typename T>
std::ostream& operator<<(std::ostream& out, const DynamicArray<T>&);       

#include "DynamicArrayImpl.hpp"


#endif //__TEMPL_DYN_ARR_H_INCLUDED__
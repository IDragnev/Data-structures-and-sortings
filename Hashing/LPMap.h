#ifndef __LP_MAP_H_INCLUDED__
#define __LP_MAP_H_INCLUDED__

#include "Item.h"
#include <stdexcept>

template <typename HashFun>
class LPMap
{
public:
	LPMap(int size);
	LPMap(const LPMap<HashFun>&); 
	~LPMap();

	LPMap<HashFun>& operator=(const LPMap<HashFun>&);

	int getCount()const;
	bool isEmpty()const;
	bool isFull()const;

	void insert(const Item&);
	void remove(char c);
	Item search(char c)const;

private:
	Item* items;
	int size;
	int count;
	HashFun hashFunction;
	
private:
	void setSize(int);
};

#include "LPMapImpl.hpp"
#endif //__LP_MAP_H_INCLUDED__
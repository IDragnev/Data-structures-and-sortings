#include <iostream>
#include <assert.h>

#include "LPMap.h"

class HashFun
{
public:
	int operator()(char c)const
	{
		return c;
	}
};


int main()
{
	LPMap<HashFun> map(40);
	
	Item item;
	//fill the table with 25 items
	for (int i = 65; i < 91; ++i)
	{
		item.setKey(i);
		map.insert(item);
	}

	int count = map.getCount();
	assert(count == 26);

	//remove each of the items
	for (int i = 65; i < 91; ++i)
	{
		map.remove(i);
		--count;
		assert(map.getCount() == count);
	}

	return 0;
}
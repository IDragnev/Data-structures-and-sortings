#include <iostream>
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
	LPMap <HashFun> map(15);

	Item item('1');

	for (int i = 0; i < 8; ++i)
	{
		map.insert(item);
		item.setKey(i + 48);
	}

	char i = '0';
	for (int j = 0; j < 8; ++i, ++j)
	{
		item = map.search(i);
		std::cout << "Searching for " << i << " .." << std::endl;
		std::cout << "Found: " << item.getKey() << std::endl;
	}

	return 0;
}
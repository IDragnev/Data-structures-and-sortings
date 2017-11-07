#include <iostream>
#include "LinkedList.h"
#include "ListIterator.h"

int main()
{
	LinkedList<int> list;

	list.addAsHead(1);
	list.addAsTail(2);

	ListIterator<int> &it = list.getHead();
	
	list.insertBefore(it, 10000);

	++it;

	for (int i = 0; i < 3; ++i)
	{
		list.insertBefore(it, 99 - i);
	}

	assert(list.getCount() == 6);

	it = list.getHead();

	while (it)
	{
		std::cout << *it << std::endl;
		++it;
	}

	return 0;
}
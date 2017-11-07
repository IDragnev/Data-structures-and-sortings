#include <iostream>
#include "LinkedList.h"
#include "ListIterator.h"

int main()
{
	LinkedList<int> list;

	list.addAsHead(1);
	list.addAsTail(2);

	ListIterator<int> &it = list.getHead();

	for (int i = 0; i < 3; ++i)
	{
		list.insertAfter(it, 99);
	}

	while (it)
	{
		std::cout << *it << std::endl;
		++it;
	}

	return 0;
}
#include <iostream>
#include "LinkedList.h"
#include "ListIterator.h"

int main()
{
	LinkedList<int> list;

	list.addAsHead(1);
	list.addAsTail(2);
	list.addAsTail(3);

	ListIterator<int> &it = list.getTail();
	
	list.removeBefore(it);

	it = list.getHead();

	while (it)
	{
		std::cout << *it << std::endl;
		++it;
	}
	return 0;
}
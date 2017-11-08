#include <iostream>
#include "LinkedList.h"
#include "ListIterator.h"

int main()
{
	LinkedList<int> list;

	list.addAsHead(1);
	list.addAsTail(2);
	list.addAsTail(3);

	ListIterator<int> &it = list.getHead();
	ListIterator<int> &rev = list.getTail();

	list.removeAt(rev);

	rev = list.getTail();

	while (it)
	{
		std::cout << *it << std::endl;
		++it;
	}

	std::cout << std::endl;

	while (rev)
	{
		std::cout << *rev << std::endl;
		--rev;
	}
	return 0;
}
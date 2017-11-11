#include <iostream>
#include "LinkedList.h"
#include "ListIterator.h"

int main()
{
	LinkedList<int> list;

	for (int i = 0; i < 10; ++i)
		list.addAsHead(1);

	LinkedList<int> list2;

	list2.addAsHead(100);
	list2.addAsHead(1212);

	LinkedList<int> list3(list);

	list = list2;

	return 0;
}
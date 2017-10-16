#include <iostream>
#include <time.h>

#include "LinkedList.h"


///
/// Fills an array with all consecutive integers between Start and End
///
void FillList(LinkedList<int> &List, int Start, int End)
{
	for (int i = Start; i <= End; i++)
		List.addAsTail(i);
}


void Test()
{
	// Decide how many element to use for the tests
	size_t ElementsCount = 0;

	std::cout << "\nHow many elements to test with?\n: ";

	std::cin >> ElementsCount;



	// Create a linked list to test with
	LinkedList<int> newList;



	// These will be used to measure execution time
	time_t start, end;


	//
	// TEST 1: Fill the list with elements
	//
	std::cout << "Filling " << ElementsCount << " element(s)...\n";

	start = time(NULL);

	FillList(newList, 0, ElementsCount - 1);

	end = time(NULL);

	std::cout << "   Execution took " << (end - start) << " sec.\n";


	//
	// TEST 2: Walk list via indexing
	//
	std::cout << "Walking the list via index...\n";

	start = time(NULL);

	int foo;

	for (int i = 0; i < ElementsCount; i++)
	{
		foo = newList.getAt(i);
	}

	end = time(NULL);

	std::cout << "   Execution took " << (end - start) << " sec.\n";


	//
	// TEST 3: Walk list via iterator
	//
	std::cout << "Walking the list via iterator...\n";

	start = time(NULL);

	// try to walk the list via iterator
	for (ListIterator<int> iterator = newList.getIterator();
	        !iterator.isDone();
	     iterator.next())
	{
		foo = iterator.getCurrent();
	}

	end = time(NULL);

	std::cout << "   Execution took " << (end - start) << " sec.\n";

}


int main()
{
	try
	{
		LinkedList<int> list;

		for (int i = 0; i < 10; ++i)
			list.addAsHead(i + 1);

		ListIterator<int> &iter = list.getIterator();

		std::cout << "\nFirst list: \n";
		for (; !iter.isDone(); iter.next())
		{
			std::cout << iter.getCurrent() << ' ';
		}
		std::cout << std::endl;

		std::cout << "\nList2 = list :\n";
		LinkedList<int> list2;
		list2 = list;

		ListIterator<int>& iter2 = list2.getIterator();

		for (; !iter2.isDone(); iter2.next())
		{
			std::cout << iter2.getCurrent() << ' ';
		}
		std::cout << std::endl;

		
	}
	catch (std::exception& ex)
	{
		std::cout << "Error! " << ex.what() << std::endl;
	}

return 0;
}
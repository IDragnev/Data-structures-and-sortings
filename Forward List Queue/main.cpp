#include <iostream>
#include "FLQueue.h"


int main()
{
	try
	{
		FLQueue<int> queue;

		for (int i = 0; i < 10; ++i)
		{
			std::cout << "\nEnqueing " << i;
			queue.enqueue(i);
		}

		std::cout << std::endl;

		while (!queue.isEmpty())
			std::cout << "\nDequeing " << queue.dequeue();
		

		std::cout << std::endl;
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	return 0;
}
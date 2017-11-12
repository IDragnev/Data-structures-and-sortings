#include <iostream>
#include <time.h>

#include "ForwardList.h"


int main()
{
	try
	{
		ForwardList<int> list;

		for (int i = 0; i < 10; ++i)
			list.addAsHead(i + 1);

		ForwardList<int> list2(list);
		
	}
	catch (std::exception& ex)
	{
		std::cout << "Error! " << ex.what() << std::endl;
	}

return 0;
}
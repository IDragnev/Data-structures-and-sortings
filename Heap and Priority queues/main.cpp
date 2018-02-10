#include <iostream>
#include <fstream>
#include "Event.h"
#include "Heap.h"


bool loadFile(Heap<Event>& heap, std::istream& file)
{
	char descr[100];
	short hour;

	heap.data = new Event[10];
	heap.size = 10;
	heap.count = 0;

	Event event;
	while (!file.eof())
	{
		file.getline(descr, 100, ';');
		file.ignore(); // ' '

		file >> hour;
		file.ignore(); //'\n'

		event.setHour(hour);
		event.setDescription(descr);

		insert(heap, event);
	}

	return !file.fail();
}

int main()
{
	std::ifstream file("File.txt", std::ios::in);
	if (!file.is_open())
	{
		std::cerr << "ERORR! Could not open File.txt" << std::endl;
		return 1;
	}

	Heap<Event> queue;
	loadFile(queue, file);

	while (!isEmpty(queue))
		std::cout << extractMax(queue) << std::endl;
	
	destroyHeap(queue);
}


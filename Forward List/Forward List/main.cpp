#include <iostream>
#include <time.h>

#include "ForwardList.h"
#include "../../Reusable classes/String/String/String.h"



//
//reverse a linked list
//
template <typename T>
void reverseList(Node<T>* &first)
{
	//if less than two, do nothing
	if (!first || !first->next) return;

	//starting from the second node in the list
	Node<T>* previous = first;
	Node<T>* current = first->next;

	//while in the list
	while (current)
	{
		//save the address of the next
		Node<T>* next = current->next;

		//reverse link
		current->next = previous;

		//move previous and current forward
		previous = current;
		current = next;
	}

	first->next = nullptr;
	first = previous;
}


//
//swap a node with its successor
//
template <typename T>
void swapWithNext(Node<T>* &node)
{
	//if empty or no successor, do nothing
	if (!node || !node->next) return;

	Node<T>* sucessor = node->next;

	//unlink node with successor
	node->next = successor->next;

	//put successor before node
	successor->next = node;

	//set node point to the new beginning
	node = successor;
}




int main()
{
	try
	{
		ForwardList<String> list;

		String str("some val");

		for (int i = 0; i < 10; ++i)
		{
			list.addAsHead(std::move(str));
			str = "some val";
		}

		ForwardList<String> list2;
		list2.addAsHead("some value");

		list2 = list;		
		
	}
	catch (std::exception& ex)
	{
		std::cout << "Error! " << ex.what() << std::endl;
	}

return 0;
}
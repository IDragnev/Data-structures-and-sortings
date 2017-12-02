#include "../../Linked List/Node.h"

//
//merge sort the sent list
//
// the function splits the list in two separate lists 
// which are sorted recursively and then 
// are merged together
//
template <typename T>
Node<T>* mergesort(Node<T>* list, bool(*compareFn)(const T&, const T&))
{
	//if less than 2
	if (list == NULL || list->next == NULL) return list;

	//save the beginning of the list
	Node<T>* leftChain = list;

	//the rabbit (starts from the second node)
	Node<T>* rightChain = list->next;

	//until right goes out of the chain
	while (rightChain && rightChain->next)
	{
		//move one node forward in the list (the turtle)
		list = list->next;

		//move right two nodes forwrad in the list
		rightChain = rightChain->next->next;
	}

	//now list will be approximately at the middle of the chain
	//so make rightChain start from its successor
	rightChain = list->next;

	//unchain left and right chain
	list->next = NULL;

	//mergeSort left and right chains recursively
	//and then merge them toghether
	return merge(mergesort(leftChain, compareFn), mergesort(rightChain, compareFn), compareFn);
}


//
//merge two lists and return the result chain
//
//no copying is used
//
template <typename T>
Node<T>* merge(Node<T>* leftChain, Node<T>* rightChain, bool(*compareFn)(const T&, const T&))
{
	//if one of the chains is empty, return the other
	if (!leftChain || !rightChain) return leftChain ? leftChain : rightChain;

	//result points to the smaller element of the chains
	Node<T>* result = compareFn(leftChain->data, rightChain->data) ? leftChain : rightChain;

	//the node to which we will append
	Node<T>* last = result;

	//progress the chain from which was appended
	if (leftChain == result)
		leftChain = leftChain->next;
	else
		rightChain = rightChain->next;

	//while none of the chains is empty
	while (leftChain && rightChain)
	{
		//choose the smaller element of the two chains
		//and attach it to the sorted chain, progressing in the 
		//corresponing chain ('removing' it from there)
		if (compareFn(rightChain->data, leftChain->data))
		{
			last->next = rightChain;
			last = rightChain;
			rightChain = rightChain->next;
		}
		else
		{
			last->next = leftChain;
			last = leftChain;
			leftChain = leftChain->next;
		}
	}

	//when the loop ends because one of the chains is empty
	//attach the whole other chain to the sorted chain
	last->next = (rightChain) ? rightChain : leftChain;

	//return the address of the sorted chain
	return result;
}


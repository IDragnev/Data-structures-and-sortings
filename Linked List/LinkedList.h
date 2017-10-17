#ifndef __SINGLY_LINKED_LIST_H_INCLUDED__
#define __SINGLY_LINKED_LIST_H_INCLUDED__

#include "Node.h"
#include "ListIterator.h"
#include <assert.h>

template <typename T>
class LinkedList
{
public:
	LinkedList();                                      //list is empty when constructed
	LinkedList(const LinkedList<T>&);
	~LinkedList();

	LinkedList<T>& operator=(const LinkedList<T>&);

	int getCount()const;                               //get the count of the nodes in the list
	bool isEmpty()const;                               //is the list empty

	const T& getAt(int)const;                          //get the value of the node in this position
	const T& getHead()const;                           //get the value of the head
	const T& getTail()const;                           //get the value of the tail

	void appendList(const LinkedList<T>&);             //append the passed list's nodes (reconstructed) to this

	ListIterator<T> getIterator()const;                //get a new ListIterator

public:
	void setHead(const T&);                            //set the value of the head
	void setTail(const T&);                            //set the value of the tail

	void addAsHead(const T&);                          //add a node as a head with the passed value
	void addAsTail(const T&);                          //add a node as a tail with the passed value

	void removeHead();                                 //remove the head node
	void removeTail();                                 //remove the tail node

	void setAt(int, const T&);                         //set the value of the specified node
	void removeAt(int);                                //remove the specified node

	void insertAfter(int, const T&);                   //insert a node after the specified node (with the passed value)
	void insertBefore(int, const T&);                  //insert a node before the specified node (with the passed value)

private:
	int count;                                         //the count of the nodes in the list
	Node<T>* head;                                     //pointer to the first node in the list
	Node<T>* tail;                                     //pointer to the last node in the list

private:
	Node<T>* searchByIndex(int index)const;            //find a node by an index
	Node<T>* findNodeBefore(const Node<T>* node)const; //find the node before the passed node

	void clear();                                      //clear the list
	void checkIsEmtpy()const;                          //will be called to check if the list is emtpy before doing an operation

	void validateIndex(int)const;                      //throws an exception if the index is invalid
private:
	static Node<T>* findEndOfChain(Node<T>* firstNode);  //find the end of a chain of nodes by its first node
	static Node<T>* cloneChain(const Node<T>* firstNode);//clone a whole chain of nodes by its first node
	static void clearChain(const Node<T>* firstNode);    //clear a whole chain of nodes by its first node
};

#include "LinkedListImpl.hpp"

#endif //__SINGLY_LINKED_LIST_H_INCLUDED__
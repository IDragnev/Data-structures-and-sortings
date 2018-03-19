#ifndef __SINGLY_LINKED_LIST_H_INCLUDED__
#define __SINGLY_LINKED_LIST_H_INCLUDED__

#include "Node.h"
#include "SinglyLinkedListIterator.h"
#include <utility>
#include <assert.h>
#include <stdexcept>

template <typename T>
class SinglyLinkedList
{
public:
	SinglyLinkedList();
	SinglyLinkedList(SinglyLinkedList<T>&&);
	SinglyLinkedList(const SinglyLinkedList<T>&);
	~SinglyLinkedList();

	SinglyLinkedList<T>& operator=(SinglyLinkedList<T>&&);
	SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>&);

	int getCount()const;                             
	bool isEmpty()const;                              

	SinglyLinkedListIterator<T> getHead();                         
	SinglyLinkedListIterator<T> getTail();

	void appendList(SinglyLinkedList<T>&&);
	void appendList(const SinglyLinkedList<T>&);          

	void removeAll();

public:
	void setHead(const T&);                           
	void setTail(const T&);                          

	void addAsHead(const T&);                         
	void addAsTail(const T&);                         

	void removeHead();                                
	void removeTail();                          

	void removeAt(SinglyLinkedListIterator<T>& it); 
	void removeBefore(SinglyLinkedListIterator<T>& it);
	void removeAfter(SinglyLinkedListIterator<T>& it);

	void insertAfter(SinglyLinkedListIterator<T>& it, const T&);          
	void insertBefore(SinglyLinkedListIterator<T>& it, const T&);      

private:
	int count;                                         
	Node<T>* head;                                  
	Node<T>* tail;                                    

private:
	void checkIsEmtpy()const;    
	void nullMembers();

	Node<T>* findNodeBefore(const Node<T>* node)const; 

	void removeAt(Node<T>* node);
	void insertAfter(Node<T>* node, const T&);
	void insertBefore(Node<T>* node, const T&);

	void appendChain(Node<T>* first, Node<T>* last, int count);

	void swapContentsWith(SinglyLinkedList<T>);

private:
	static Node<T>* cloneChain(const Node<T>* firstNode, Node<T>** lastNode = nullptr);
	static void clearChain(const Node<T>* firstNode);  
};

#include "SinglyLinkedListImpl.hpp"
#endif //__SINGLY_LINKED_LIST_H_INCLUDED__
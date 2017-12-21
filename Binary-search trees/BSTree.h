#ifndef __BIN_SEARCH_TREE_H_INCLUDED__
#define __BIN_SEARCH_TREE_H_INCLUDED__

#include "BSTreeNode.h"

template <typename T>
class BSTree
{
public:
	template <typename T>
	class BSTIterator
	{
	private:
		BSTIterator(BSTreeNode<T>* start, const BSTree<T>* owner);

	private:
		BSTreeNode<T>* current;
		const BSTree<T>* owner;
	};

public:
	BSTree();
	BSTree(const BSTree<T>&);
	~BSTree();

	BSTree<T>& operator=(const BSTree&);

public:
	bool isEmpty()const;
	void removeAll();

	BSTIterator<T> search(const T& key);
	BSTIterator<T> getMinimum();
	BSTIterator<T> getMaximum();

	void add(const T& key);

	void removeAt(BSTIterator<T>& it);
	void removeAfter(BSTIterator<T>& it);
	void removeBefore(BSTIterator<T>& it);
	
private:
	static BSTreeNode<T>* search(BSTreeNode<T>* root, const T& key);
	static BSTreeNode<T>* min(BSTreeNode<T>* root);
	static BSTreeNode<T>* max(BSTreeNode<T>* root);

	static BSTreeNode<T>* successor(BSTreeNode<T>* node);
	static BSTreeNode<T>* predecessor(BSTreeNode<T>* node);

	static void insert(BSTreeNode<T>* root, BSTreeNode<T>* leaf);

	void remove(BSTreeNode<T>* node);
	void transplant(BSTreeNode<T>* oldChild, BSTreeNode<T>* newChild);

	static void clear(BSTreeNode<T>* root);

	template <typename Function>
	static BSTreeNode<T>* copy(const BSTreeNode<T>* root, const Function& copyFun);
	
	template <typename Function>
	static void processPre(BSTreeNode<T>* root, const Function& fun);
	template <typename Function>
	static void processIn(BSTreeNode<T>* root, const Function& fun);
	template <typename Function>
	static void processPost(BSTreeNode<T>* root, const Function& fun);

private:
	BSTreeNode<T>* root;
};

#endif //__BIN_SEARCH_TREE_H_INCLUDED__

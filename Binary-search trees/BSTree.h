#ifndef __BIN_SEARCH_TREE_FUNS_H_INCLUDED__
#define __BIN_SEARCH_TREE_FUNS_H_INCLUDED__

#include "BSTreeNode.h"
#include <assert.h>

namespace BinarySearchTree
{
	template <typename T>
	BSTreeNode<T>* searchTree(BSTreeNode<T>* root, const T& key);
	template <typename T>
	BSTreeNode<T>* treeMin(BSTreeNode<T>* root);
	template <typename T>
	BSTreeNode<T>* treeMax(BSTreeNode<T>* root);

	template <typename T>
	BSTreeNode<T>* getSuccessor(BSTreeNode<T>* node);
	template <typename T>
	BSTreeNode<T>* getPredecessor(BSTreeNode<T>* node);

	template <typename T>
	void insert(BSTreeNode<T>* &root, BSTreeNode<T>* leaf);
	template <typename T>
	void remove(BSTreeNode<T>* &root, BSTreeNode<T>* node);
	template <typename T>
	void transplantSubtree(BSTreeNode<T>* &root, BSTreeNode<T>* oldChild, BSTreeNode<T>* newChild);

	template <typename T>
	void clearTree(BSTreeNode<T>* &root);
	template <typename T, typename Function>
	BSTreeNode<T>* copyTree(const BSTreeNode<T>* root, const Function& copyFun);

	template <typename T, typename Function>
	void processPreorder(BSTreeNode<T>* root, const Function& fun);
	template <typename T, typename Function>
	void processInorder(BSTreeNode<T>* root, const Function& fun);
	template <typename T, typename Function>
	void processPostorder(BSTreeNode<T>* root, const Function& fun);
}

#endif //__BIN_SEARCH_TREE_FUNS_H_INCLUDED__

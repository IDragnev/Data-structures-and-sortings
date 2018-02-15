#ifndef __REC_BST_H_INCLUDED__
#define __REC_BST_H_INCLUDED__

#include <assert.h>
#include "../Stack/Dynamic stack/DynamicStack.h"
#include "../Forward List Queue/FLQueue.h"

namespace RecBST
{
	template <typename T>
	struct BSTNode
	{
		BSTNode(const T& key, BSTNode<T>* left = nullptr, BSTNode<T>* right = nullptr);

		BSTNode<T>* left;
		BSTNode<T>* right;
		T key;
	};

	template <typename T>
	BSTNode<T>* search(BSTNode<T>* root, const T& key);

	template <typename T>
	BSTNode<T>* iterativeSearch(BSTNode<T>* root, const T& key);

	template <typename T>
	void insert(BSTNode<T>* &root, const T& key);


	template <typename T>
	void remove(BSTNode<T>* &root, const T& key);
	
	template <typename T>
	void removeRoot(BSTNode<T>* &root);

	template <typename T>
	BSTNode<T>* spliceMinOut(BSTNode<T>* &root);


	template <typename T>
	BSTNode<T>* getMax(BSTNode<T>* root);

	template <typename T>
	BSTNode<T>* getMin(BSTNode<T>* root);


	template <typename T>
	void destroyTree(BSTNode<T>* root);

	template <typename T>
	BSTNode<T>* copyTree(BSTNode<T>* root);

	template <typename T, typename Processor>
	BSTNode<T>* mapTree(BSTNode<T>* root, const Processor&);

	template <typename T>
	void printTree(BSTNode<T>* root);

	//
	//traversals
	//
	template <typename T, typename Processor>
	void traverseInorder(BSTNode<T>* root, const Processor&);

	template <typename T, typename Processor>
	void traversePreorder(BSTNode<T>* root, const Processor&);

	template <typename T, typename Processor>
	void traversePostorder(BSTNode<T>* root, const Processor&);

	template <typename T, typename Processor>
	void traverseLevelOrder(BSTNode<T>* root, const Processor&);

	template <typename T, typename Processor>
	void iterativeInorder(BSTNode<T>* root, const Processor&);

	template <typename T, typename Processor>
	void iterativePreorder(BSTNode<T>* root, const Processor&);

	template <typename T, typename Processor>
	void iterativePostorder(BSTNode<T>* root, const Processor&);


	//
	//other
	//
	template <typename T>
	int countNodes(BSTNode<T>* root);

	template <typename T>
	int height(BSTNode<T>* root);

	template <typename T>
	BSTNode<T>* buildBalancedTree(const DynamicArray<T>& sorted, int beg, int end);
}

#include "RecBSTImpl.hpp"
#endif //__REC_BST_H_INCLUDED__
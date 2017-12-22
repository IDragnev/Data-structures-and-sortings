#ifndef __BSTREE_NODE_H_INCLUDED__
#define __BSTREE_NODE_H_INCLUDED__

#include <iostream>

namespace BinarySearchTree
{
	template <typename T>
	class BSTreeNode
	{
	private:
		BSTreeNode(const T& data, BSTreeNode<T>* left = NULL, BSTreeNode<T>* right = NULL, BSTreeNode<T>* parent = NULL);
		BSTreeNode(const BSTreeNode<T>&) = default;
		~BSTreeNode() = default;

		BSTreeNode<T>& operator=(const BSTreeNode<T>&) = default;

	private:
		BSTreeNode<T>* left;
		BSTreeNode<T>* right;
		BSTreeNode<T>* parent;
		T data;
	};

#include "BSTreeNodeImpl.hpp"

}

#endif //__BSTREE_NODE_H_INCLUDED__
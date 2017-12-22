#include "BSTree.h"

/*
The BSTree is implemented with the larger or equal keys of a node
being to its right.
*/

namespace BinarySearchTree
{
	//
	//search a BSTree for a key
	//
	template <typename T>
	BSTreeNode<T>* searchTree(BSTreeNode<T>* root, const T& key)
	{
		//while in the tree and key is not found
		while (root && root->data != key)
		{
			//choose appropriate branch
			if (root->data < key)
				root = root->left;
			else
				root = root->right;
		}

		return root;
	}


	//
	//search a tree for its min. element
	//
	// \if the tree is empty, NULL is returned
	//
	template <typename T>
	BSTreeNode<T>* treeMin(BSTreeNode<T>* root)
	{
		if (root)
		{
			//go to the leftmost node
			while (root->left)
				root = root->left;
		}

		return root;
	}


	//
	//search a tree for its max. element
	//
	//\if the tree is empty, NULL is returned
	template <typename T>
	BSTreeNode<T>* treeMax(BSTreeNode<T>* root)
	{
		if (root)
		{
			//go to the rightmost node
			while (root->right)
				root = root->right;
		}

		return root;
	}



	//
	//find the successor of a node (determined by an inorder tree walk: left root right)
	//
	template <typename T>
	BSTreeNode<T>* getSuccessor(BSTreeNode<T>* node)
	{
		//if its right subtree is non-empty, its successor is the min. of its right subtree
		//(last processed a root and, now going to process its right subtree)
		if (node->right)
			return treeMin(node->right);
		//else its successor is its lowest ancestor whose left child is also his ancestor (a node is an ancestor of itself)
		//(last processed a left subtree, now we are returning to process its parent)
		else
		{
			//starting from its parent
			BSTreeNode<T>* ancestor = node->parent;

			//moving up the tree, find the first ancestor to whom the current node is a left child
			while (ancestor && node == ancestor->right)
			{
				node = ancestor;
				ancestor = ancestor->parent;
			}

			return ancestor;
		}	
	}

	
	//
	//find the predecessor of a node (determined by an inorder tree walk: left root right)
	//
	template <typename T>
	BSTreeNode<T>* getPredecessor(BSTreeNode<T>* node)
	{
		//if its left subtree is non-empty, its predecessor is the max. of its left subtree
		//(we will process a root, which means we have processed its left subtree first -> the one processed before it has been the rightmost of its left subtree)
		if (node->left)
			return treeMax(node->left);
		//else its predecessor is its lowest ancestor whose right child is also an ancestor of current
		//(will process a root with no left subtree, meaning the last processed has been a root, and after processing it we have gone to process its right subtree)
		else
		{
			//starting from its parent
			BSTreeNode<T>* ancestor = node->parent;

			//moving up the tree, find the lowest anc. to which current is a right child
			while (ancestor && node == ancestor->left)
			{
				node = ancestor;
				ancestor = ancestor->parent;
			}

			return ancestor;
		}
	}

}
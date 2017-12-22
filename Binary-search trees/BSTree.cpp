#include "BSTree.h"
#include "../Template Dynamic Array/DynamicStack.h"


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


	//
	//insert a leaf node to a tree
	//
	template <typename T>
	void insert(BSTreeNode<T>* &root, BSTreeNode<T>* leaf)
	{
		BSTreeNode<T>* parent = NULL;
		BSTreeNode<T>* current = root;

		//until the empty (NULL) position is reached
		while (current)
		{
			//save the last non-NULL as its parent
			parent = current;
			
			//choose the appropriate branch to proceed down the tree
			if (leaf->data < current->data)
				current = current->left;
			else
				current = current->right;
		}

		//set its parent
		leaf->parent = parent;

		//if the tree was empty, it is the new root
		if (parent == NULL)
			root = leaf;
		else if (leaf->data < parent->data)
			parent->left = leaf;
		else
			parent->right = leaf;
	}


	//
	//change a tree's subtree with another tree
	//
	//the function does nothing on old and newSubtree's children
	//
	template <typename T>
	void transplantSubtree(BSTreeNode<T>* &tree, BSTreeNode<T>* oldSubtree, BSTreeNode<T>* newSubtree)
	{
		//if the old subtree was the actual tree
		//the new subtree 'becomes' the tree
		if (oldSubtree->parent == NULL)
			tree = newSubtree;
		//else if oldSubtree was a left child of its parent
		else if (oldSubtree->parent->left == oldSubtree)
			oldSubtree->parent->left = newSubtree;
		else
			oldSubtree->parent->right = newSubtree;

		//if the new subtree is not empty, update its parent
		if (newSubtree)
			newSubtree->parent = oldSubtree->parent;
	}


	//
	//remove a node from a tree
	//
	template <typename T>
	void remove(BSTreeNode<T>* &tree, BSTreeNode<T>* node)
	{
		//if node has no left child
		if (node->left == NULL)
		{
			//elevate node's right child in its place (could be NULL)
			transplantSubtree(tree, node, node->right);
		}
		//else if it has a left child but no right one
		else if (node->right == NULL)
		{
			//elevate node's left child in its place
			transplantSubtree(tree, node, node->left);
		}
		else //node has both left and right child
		{
			//its successor is the min. of its right subtree (as min. successor has no left child)
			BSTreeNode<T>* successor = treeMin(node->right);
			assert(successor && successor->left == NULL);

			//if its successor is not its right child, their right subtrees must be updated
			if (successor->parent != node)
			{
				//put successor's right child in successor's place (elevate successor's right subtree)
				transplantSubtree(tree, successor, successor->right);
				//change successors right subtree with node's subtree
				successor->right = node->right;
				successor->right->parent = successor;
			}

			//elevate successor to node's place
			transplantSubtree(tree, node, successor);
			//and attach node's left subtree to successor
			successor->left = node->left;
			successor->left->parent = successor;
		}
	}


	//
	//preorder iterative tree traversal
	//
	template <typename T, typename Function>
	void processPreorder(BSTreeNode<T>* root, const Function& process)
	{
		//if empty, return
		if (!root) return;

		DynamicStack<BSTreeNode<T>*> stack;

		//push the tree on the stack
		stack.push(root);

		while (!stack.isEmpty())
		{
			//process the root
			process(root = stack.pop());

			//push its right subtree on the stack
			if (root->right)
				stack.push(root->right);

			//push its left subtree on the stack
			if (root->left)
				stack.push(root->left);
		}
	}


	//
	//inorder iterative tree traversal
	//
	template <typename T, typename Function>
	void processInorder(BSTreeNode<T>* root, const Function& process)
	{
		DynamicStack<BSTreeNode<T>*> stack;

		BSTreeNode<T>* current = root;

		//while there is a parent to come back to
		//or currently at a non-NULL TreeNode
		while (!stack.isEmpty() || current)
		{
			//if on a TreeNode
			if (current)
			{
				//push it on the stack and go to its left child
				stack.push(current);

				current = current->left;
			}
			else  //if NULL was reached, return to its parent, process it and go to the parent's right child
			{
				current = stack.pop();

				process(current);

				current = current->right;
			}
		}
	}



	//
	//postorder iterative tree traversal
	//
	template <typename T, typename Function>
	void processPostorder(BSTreeNode<T>* root, const Function& process)
	{
		if (!root) return;

		DynamicStack<BSTreeNode<T>*> stack;
		stack.push(root);

		//the last traversed node
		BSTreeNode<T>* prev = NULL;

		while (!stack.isEmpty())
		{
			BSTreeNode<T>* curr = stack.peek();

			//if moving down the tree
			if (!prev || prev->left == curr || prev->right == curr)
			{
				//try to push left or right child
				if (curr->left)
					stack.push(curr->left);
				else if (curr->right)
					stack.push(curr->right);

				//if there were no children, the leaf stays on top of the stack
			}
			//else if moving up from left
			else if (curr->left == prev)
			{
				//try to push right child
				if (curr->right)
					stack.push(curr->right);
			}
			else  //if moving up from right (both subtrees were traversed)
			{
				//process the 'root' and remove it from the stack
				process(stack.pop());
			}

			//mark current as traversed
			prev = curr;
		}
	}


	template <typename T>
	void clearTree(BSTreeNode<T>* &root)
	{
		processPostorder(root, [](BSTreeNode<T>* node) { delete node; });
		root = NULL;
	}
	

	//
	//reconstruct a tree
	//
	template <typename T>
	BSTreeNode<T>* copyTree(const BSTreeNode<T>* root)
	{
		//if empty, return NULL, else reconstruct
		return (!root) ? NULL : new BSTreeNode<T>(root->data, copyTree(root->left), copyTree(root->right));
	}


}
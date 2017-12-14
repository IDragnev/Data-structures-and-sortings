#include "../Linked List/LStack.h"
#include "../Template Dynamic Array/DynamicStack.h"


template <typename Key>
struct TreeNode
{
	TreeNode(const Key& key, TreeNode* left = NULL, TreeNode* right = NULL)
		:
		key(key),
		left(left),
		right(right)
	{
		;
	}

	TreeNode* left;
	TreeNode* right;
	Key data;
};


//
//preorder iterative tree traversal
//
template <typename T>
void traversePreorder(TreeNode<T>* root, void(*process)(TreeNode<T>*))
{
	if (!root) return;

	DynamicStack<TreeNode<T>*> stack;

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
template <typename T>
void inorderTraversal(TreeNode<T>* root, void(*process)(TreeNode<T>*))
{
	DynamicStack<TreeNode<T>*> stack;

	TreeNode<T>* current = root;

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
template <typename T>
void postOrderIterative(TreeNode<T> *root, void(*process)(TreeNode<T>*))
{
	if (!root) return;

	DynamicStack<TreeNode<T>*> stack;
	stack.push(root);

	TreeNode<T>* prev = NULL;

	while (!stack.isEmpty())
	{
		TreeNode<T>* curr = stack.peek();

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
			process(curr);
			stack.pop();
		}

		//mark current as traversed
		prev = curr;
	}
}
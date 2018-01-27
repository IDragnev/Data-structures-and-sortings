
namespace RecBST
{

	template <typename T>
	BSTNode<T>::BSTNode(const T& key, BSTNode<T>* left, BSTNode<T>* right)
		:
		left(left),
		right(right),
		key(key)
	{
		;
	}


	template <typename T>
	BSTNode<T>* search(BSTNode<T>* root, const T& key)
	{
		//if empty or match
		if (!root || root->key == key) 
			return root;
		else if (key < root->key)
			search(root->left, key);
		else
			search(root->right, key);
	}


	template <typename T>
	BSTNode<T>* iterativeSearch(BSTNode<T>* root, const T& key)
	{
		//while in the tree and not the one we are searching for 
		while (root && root->key != key)
		{
			//choose appropriate branch
			if (key < root->key)
				root = root->left;
			else
				root = root->right;
		}

		//stopped either because root is null (miss)
		//or because root->key == key (hit)
		return root;
	}



	template <typename T>
	BSTNode<T>* getMax(BSTNode<T>* root)
	{
		//if not empty
		if (root)
		{
			//follow right links
			while (root->right)
			{
				root = root->right;
			}
		}

		return root;
	}


	template <typename T>
	BSTNode<T>* getMin(BSTNode<T>* root)
	{
		//if not empty
		if (root)
		{
			//follow left links
			while (root->left)
			{
				root = root->left;
			}
		}

		return root;
	}


	template <typename T>
	void insert(BSTNode<T>* &root, const T& key)
	{
		if (!root)
			root = new BSTNode<T>(key);
		else if (key < root->key)
			insert(root->left, key);
		else
			insert(root->right, key);
	}




	template <typename T>
	void remove(BSTNode<T>* &root, const T& key)
	{
		//if empty, do nothing
		if (!root) return;

		if (key < root->key)
			remove(root->left, key);
		else if (root->key < key)
			remove(root->right, key);
		else //key == root->key
			removeRoot(root);	
	}


	template <typename T>
	void removeRoot(BSTNode<T>* &root)
	{
		if (!root) return;

		BSTNode<T>* toDel = root;

		//if no left child, elevate right child
		if (!root->left)
			root = root->right;
		//if only left, elevate left child
		else if (!root->right)
			root = root->left;
		else //has both a left and a right child
		{
			//put its successor in its place
			root = spliceMinOut(root->right);

			//transfer old child's subtrees
			root->left = toDel->left;
			root->right = toDel->right;
		}

		delete toDel;
	}


	template <typename T>
	BSTNode<T>* spliceMinOut(BSTNode<T>* &root)
	{
		assert(root);

		//if not on minimum, follow left link
		if (root->left)
			return spliceMinOut(root->left);
		else 
		{
			BSTNode<T>* min = root;
			
			//elevate right subtree
			root = root->right;

			//return the spliced min
			return min;
		}
	}


	template <typename T, typename Processor>
	void traverseInorder(BSTNode<T>* root, const Processor& process)
	{
		//if a leaf, do nothing
		if (!root) return;

		traverseInorder(root->left, process);
		process(root);
		traverseInorder(root->right, process);
	}


	template <typename T, typename Processor>
	void traversePreorder(BSTNode<T>* root, const Processor& process)
	{
		//if a leaf, do nothing
		if (!root) return;

		process(root);
		traversePreorder(root->left, process);
		traversePreorder(root->right, process);
	}


	template <typename T, typename Processor>
	void traversePostorder(BSTNode<T>* root, const Processor& process)
	{
		//if a leaf, do nothing
		if (!root) return;

		traversePostorder(root->left, process);
		traversePostorder(root->right, process);
		process(root);
	}


	template <typename T, typename Processor>
	BSTNode<T>* mapTree(BSTNode<T>* root, const Processor& process)
	{
		if (!root) return nullptr;

		BSTNode<T>* result = new BSTNode<T>(process(root->key));
		result->left = mapTree(root->left, process);
		result->right = mapTree(root->right, process);

		return result;
	}


	template <typename T>
	BSTNode<T>* copyTree(BSTNode<T>* root)
	{
		return mapTree(root, [](const T& key)->const T& { return key; })
	}

	template <typename T>
	void destroyTree(BSTNode<T>* root)
	{
		traversePostorder(root, [](BSTNode<T>* node) { delete node; });
	}

	template <typename T>
	void printTree(BSTNode<T>* root)
	{
		traverseInorder(root, [](const BSTNode<T>* node) { std::cout << node->key << ' '; });
	}


	template <typename T, typename Processor>
	void iterativePreorder(BSTNode<T>* root, const Processor& process)
	{
		if (!root) return;

		DynamicStack<BSTNode<T>*> stack;

		//push the root on the stack
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


	template <typename T, typename Processor>
	void iterativeInorder(BSTNode<T>* root, const Processor& process)
	{
		if (!root) return;

		DynamicStack<BSTNode<T>*> stack;

		//while there is a parent to come back to
		//or currently on a root
		while (!stack.isEmpty() || root)
		{
			//if on a root
			if (root)
			{
				//push it on the stack
				stack.push(root);

				//and 'visit' its left child
				root = root->left;
			}
			else //if null was reached
			{
				//go back to its parent
				root = stack.pop();

				process(root);

				//'visit' its right child
				root = root->right;
			}
		}
	}


	template <typename T, typename Processor>
	void iterativePostorder(BSTNode<T>* root, const Processor& process)
	{
		if (!root) return;

		DynamicStack<BSTNode<T>*> stack;
		stack.push(root);

		BSTNode<T>* prev = nullptr;

		while (!stack.isEmpty())
		{
			BSTNode<T>* curr = stack.peek();

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


	template <typename T>
	int countNodes(BSTNode<T>* root)
	{
		if (!root) return 0;

		return 1 + countNodes(root->left) + countNodes(root->right);
	}


	template <typename T>
	int height(BSTNode<T>* root)
	{
		if (!root) return -1;

		int hLeft = height(root->left);
		int hRight = height(root->right);

		return (hLeft > hRight) ? (hLeft + 1) : (hRight + 1);
	}


	template <typename T, typename Processor>
	void traverseLevelOrder(BSTNode<T>* root, const Processor& process)
	{
		FLQueue<BSTNode<T>*> queue;

		queue.enqueue(root);

		while (!queue.isEmpty())
		{
			root = queue.dequeue();

			process(root);

			if (root->left)
				queue.enqueue(root->left);
			if (root->right)
				queue.enqueue(root->right);
		}
	}


	template <typename T>
	BSTNode<T>* buildBalancedTree(const DynamicArray<T>& arr, int beg, int end)
	{
		if (beg > end)
			return nullptr;

		int middle = (beg + end) / 2;

		BSTNode<T>* result = new BSTNode<T>(arr[middle]);
		result->left = buildBalancedTree(arr, beg, middle - 1);
		result->right = buildBalancedTree(arr, middle + 1, end);

		return result;
	}
}
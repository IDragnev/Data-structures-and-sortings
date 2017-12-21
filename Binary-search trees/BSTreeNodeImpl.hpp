


template <typename T>
BSTreeNode<T>::BSTreeNode(const T& data, BSTreeNode<T>* left, BSTreeNode<T>* right, BSTreeNode<T>* parent)
	:
	left(left),
	right(right),
	parent(parent),
	data(data)
{
	;
}

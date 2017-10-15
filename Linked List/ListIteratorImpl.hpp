

//
//initializes both start and current
//to point to the passed starting node
//
template <typename Key>
ListIterator<Key>::ListIterator(Node<Key>* startNode)
	:
	start(startNode),
	current(startNode)
{
	;
}



//
//the traversal is done if current points to NULL
//
template <typename Key>
bool ListIterator<Key>::isDone()const
{
	return current == NULL;
}



//
//returns iterator to beginning
//
template <typename Key>
void ListIterator<Key>::first()
{
	current = start;
}



//
//move iterator to the next node in the list
//
//if the traversal has already finished, the function does nothing
//
template <typename Key>
void ListIterator<Key>::next()
{
	//if not done
	if (current)
	{
		//move forward
		current = current->next;
	}
}




//
//get the value of the current node
//
//if the traversal has already finished, throw an exception
//
template <typename Key>
const Key& ListIterator<Key>::getCurrent()const
{
	if (isDone())
		throw std::logic_error("Iterator out of bounds!");

	return current->data;
}



//
//set the value of the current node
//
//if the traversal has already finished, throw an exception
//
template <typename Key>
void ListIterator<Key>::setCurrent(const Key& value)
{
	if (isDone())
		throw std::logic_error("Iterator out of bounds!");

	current->data = value;
}




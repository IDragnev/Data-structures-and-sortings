#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include "RecBST.h"

using namespace RecBST;

void describeTree(BSTNode<int>* tree)
{
	printTree(tree);
	std::cout << "\nMinimum: "         << getMin(tree)->key << std::endl;
	std::cout << "Maximum: "           << getMax(tree)->key << std::endl;
	std::cout << "Height: "            << height(tree)      << std::endl;
	std::cout << "Number of nodes: "   << countNodes(tree)  << std::endl;
}


void searchRandom(BSTNode<int>* tree)
{
	int hits = 0;
	int misses = 0;
	int searches;
	int biggest;

	std::cout << "\nHow many searches to make: ";
	std::cin >> searches;
	if (searches > 0)
	{
		std::cout << "Up to which number: ";
		std::cin >> biggest;

		++biggest;

		BSTNode<int>* res = nullptr;

		for (int i = 0; i < searches; ++i)
		{
			int val = rand() % biggest;

			//std::cout << "\nSeaching for " << val << " ...  ";
			res = search(tree, val);

			if (res)
				++hits;
			else
				++misses;
		}

		std::cout << "\nHITS: " << hits << std::endl;
		std::cout << "MISSES: " << misses << std::endl;
	}
}


void insertRandom(BSTNode<int>* tree)
{
	int inserts;
	int biggest;
	
	std::cout << "\nHow many inserts to make: ";
	std::cin >> inserts;

	if (inserts > 0)
	{
		std::cout << "Up to which number: ";
		std::cin >> biggest;

		for (int i = 0; i < inserts; ++i)
		{
			int val = rand() % biggest;
			std::cout << "\nInserting " << val << " .." << std::endl;
			insert(tree, val);
		}
	}
}


void removeRandom(BSTNode<int>* &tree)
{
	int removals;
	std::cout << "\nHow many removals to make: ";
	std::cin >> removals;

	if (removals > 0)
	{
		int biggest;
		std::cout << "Up to which number: ";
		std::cin >> biggest;
		++biggest;

		for (int i = 0; i < removals; ++i)
		{
			int val = rand() % biggest;
			std::cout << "\nRemoving " << val << std::endl;
			remove(tree, val);
		}
	}
}


int main()
{
	srand(time(nullptr));

	int size; 
	std::cout << "How many elements to fill: ";
	std::cin >> size;

	if (size > 0)
	{
		DynamicArray<int> arr(size);

		for (int i = 0; i < size; ++i)
			arr.add(i);

		BSTNode<int>* tree = buildBalancedTree(arr, 0, arr.getCount() - 1);

		describeTree(tree);

		searchRandom(tree);
		insertRandom(tree);
		describeTree(tree);

		removeRandom(tree);
		describeTree(tree);

		destroyTree(tree);
	}

	return 0;
}
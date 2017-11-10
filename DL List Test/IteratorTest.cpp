#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Doubly Linked List with Iterator/LinkedList.h"
#include "../Doubly Linked List with Iterator/ListIterator.h"
#include "../Doubly Linked List with Iterator/Node.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DLListTest
{		
	TEST_CLASS(IteratorTest)
	{
	public:
		
		TEST_METHOD(NodeTest)
		{
			Node<int> node(1);

			Assert::IsFalse(node.hasSuccessor(), L"Node has successor even when default constructed");
			Assert::IsFalse(node.hasPredecessor(), L"Node has predecessor even when default constructed");

			Node<int> node2(2, &node);

			Assert::IsFalse(node2.hasSuccessor(), L"Node has successor even after constructing it without such");
			Assert::IsTrue(node2.hasPredecessor(), L"Node has no predecessor even after constructing it with such");

			Node<int> node3(3, NULL, &node2);
			Assert::IsTrue(node3.hasSuccessor(), L"Node has no successor even after constructing it with such");
			Assert::IsFalse(node3.hasPredecessor(), L"Node has predecessor even after constructing it without such");


			Node<int> node4(4, &node2, &node3);
			Assert::IsTrue(node4.hasSuccessor(), L"Node has no successor even after constructing it with such");
			Assert::IsTrue(node4.hasPredecessor(), L"Node has no predecessor even after constructing it with such");
		}


		TEST_METHOD(EmptyListIteratorBoundariesTest)
		{
			LinkedList<int> list;

			ListIterator<int> &itHead = list.getHead();
			ListIterator<int> &itTail = list.getTail();

			Assert::IsTrue(!itHead, L"Iterator is not \'NULL\' when made from an empty list");
			Assert::IsTrue(!itTail, L"Iterator is not \'NULL\' when made from an empty list");
		}

		TEST_METHOD(IteratorBoundariesTest)
		{
			LinkedList<int> list;

			for (int i = 0; i < 5; ++i)
				list.addAsHead(i);

			ListIterator<int> &it = list.getHead();

			int count = 0;
			for (; it; ++it, ++count);
			Assert::IsTrue(count == 5, L"Iterator is not moving forward in the list properly");

			ListIterator<int> &it2 = list.getTail();

			int count2 = 0;
			for (; it2; --it2, ++count2);
			Assert::IsTrue(count2 == 5, L"Iterator is not moving backwards in the list properly");
		}

		TEST_METHOD(IteratorDerrefTest)
		{
			LinkedList<int> list;

			for (int i = 0; i < 5; ++i)
				list.addAsTail(i);

			ListIterator<int> &it = list.getHead();

			for (int i = 0; it; ++it, ++i)
			{
				Assert::AreEqual(*it, i, L"Operator* of iterator is not working properly");
			}
		}
	};
}
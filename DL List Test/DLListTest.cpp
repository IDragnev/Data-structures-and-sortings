#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Doubly Linked List with Iterator/LinkedList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DLListTest
{
	TEST_CLASS(DLListTest)
	{
		TEST_METHOD(EmptyListTest)
		{
			//empty list
			LinkedList<int> list;

			Assert::IsTrue(list.getCount() == 0, L"List is not empty when constructed");
			Assert::IsTrue(list.isEmpty(), L"IsEmpty returns false after construction");

			//adding head
			list.addAsHead(1);

			//should not be empty
			Assert::IsFalse(list.isEmpty(), L"IsEmpty retuns true after inserting as head");
			Assert::IsTrue(list.getCount() == 1, L"Count is not 1 after inserting head");

			//check if the head value is correct
			ListIterator<int> &it = list.getHead();
			Assert::AreEqual(*it, 1, L"Head is not set properly");

			//remove head
			list.removeHead();
			//should be empty
			Assert::IsTrue(list.getCount() == 0, L"List is not empty when removing head as only node");
			Assert::IsTrue(list.isEmpty(), L"IsEmpty returns false after removing head as only node");

			//add tail and remove head (which is tail)
			list.addAsTail(1);
			list.removeHead();
			//should be empty
			Assert::IsTrue(list.getCount() == 0, L"List is not empty when removing head as only node");
			Assert::IsTrue(list.isEmpty(), L"IsEmpty returns false after removing head as only node");
		}

		TEST_METHOD(AddingTailTest)
		{
			LinkedList<int> list;

			list.addAsTail(1);

			//check count and isEmpty
			Assert::IsFalse(list.isEmpty(), L"IsEmpty retuns true after inserting as tail");
			Assert::IsTrue(list.getCount() == 1, L"Count is not 1 after inserting tail");

			//tail and head should be 1
			ListIterator<int> &it = list.getTail();
			Assert::AreEqual(*it, 1, L"Tail is not set properly");

			ListIterator<int> &it2 = list.getHead();
			Assert::AreEqual(*it, 1, L"Tail is not set properly");

			list.removeHead();

			//push tail -> 0,1,2,3,4,5,6,7,8,9
			for (int i = 0; i < 10; ++i)
			{
				list.addAsTail(i);
				Assert::IsTrue(list.getCount() == i + 1, L"Count is not set properly when adding as tail");
			}

			// start from the head
			ListIterator<int> &head = list.getHead();

			for (int i = 0; head; ++head, ++i)
				Assert::IsTrue(*head == i, L"Adding as tail is not working properly");
		}

		TEST_METHOD(AddingHeadTest)
		{
			LinkedList<int> list;

			list.addAsHead(1);

			//check count and isEmpty
			Assert::IsFalse(list.isEmpty(), L"IsEmpty retuns true after inserting as head");
			Assert::IsTrue(list.getCount() == 1, L"Count is not 1 after inserting head");

			//tail and head should be 1
			ListIterator<int> &it = list.getTail();
			Assert::AreEqual(*it, 1, L"Head is not set properly");

			ListIterator<int> &it2 = list.getHead();
			Assert::AreEqual(*it2, 1, L"Head is not set properly");

			list.removeHead();

			//push head -> 9,8,7,6,5,4,3,2,1,0
			for (int i = 0; i < 10; ++i)
			{
				list.addAsHead(i);
				Assert::IsTrue(list.getCount() == i + 1, L"Count is not set properly when adding as head");
			}

			// start from the tail
			ListIterator<int> &rev = list.getTail();

			for (int i = 0; rev; --rev, ++i)
				Assert::IsTrue(*rev == i, L"Adding as head is not working properly");
		}


		TEST_METHOD(SettingTailTest)
		{
			LinkedList<int> list;

			list.addAsTail(1);

			//should update tail which is head also
			list.setTail(2);

			Assert::IsTrue(list.getCount() == 1, L"Setting tail changes count");

			//tail and head should be 2
			ListIterator<int> &it = list.getTail();
			Assert::AreEqual(*it, 2, L"Tail is not set properly");

			ListIterator<int> &it2 = list.getHead();
			Assert::AreEqual(*it2, 2, L"Tail is not set properly");
		}

		TEST_METHOD(SettingHeadTest)
		{
			LinkedList<int> list;

			list.addAsHead(1);

			//should update tail which is head also
			list.setHead(2);

			Assert::IsTrue(list.getCount() == 1, L"Setting head changes count");

			//tail and head should be 2
			ListIterator<int> &it = list.getTail();
			Assert::AreEqual(*it, 2, L"Head is not set properly");

			ListIterator<int> &it2 = list.getHead();
			Assert::AreEqual(*it2, 2, L"Head is not set properly");
		}


		TEST_METHOD(AppendingToListSimple)
		{
			LinkedList<int> list;

			//fill it
			for (int i = 0; i < 10; ++i)
				list.addAsTail(i);

			ListIterator<int> &list1Tail = list.getTail();

			int count = list.getCount();

			LinkedList<int> list2;

			//append an empty list
			list.appendList(list2);

			//count should not be changed
			Assert::IsTrue(list.getCount() == count, L"Appending an empty list is not working properly");

			//fill list 2
			for (int i = 0; i < 5; ++i)
				list2.addAsTail(i);

			//append a non-empty list
			list.appendList(list2);
			
			//count should be summed
			Assert::IsTrue(list.getCount() == (count + list2.getCount()), L"Appending a non-empty list changes count incorrectly");
		}


		TEST_METHOD(AppendingToList)
		{
			LinkedList<int> list;

			LinkedList<int> list2;
			for (int i = 0; i < 10; ++i)
				list2.addAsTail(i);

			//append list2 to the empty list
			list.appendList(list2);

			ListIterator<int> &it = list.getHead();

			//should have reconstructed them all
			for (int i = 0; it; ++it, ++i)
			{
				Assert::AreEqual(i, *it, L"Appending to non-empty list is not working properly");
			}

			//set it to tail
			it = list.getTail();

			//now append again to the non-empty list
			list.appendList(list2);


			//move to the first appended node
			++it;
			Assert::IsFalse(!it, L"Appending to non-empty list is not working properly");

			//should have reconstructed them all
			for (int i = 0; it; ++it, ++i)
			{
				Assert::AreEqual(i, *it, L"Appending to list is not working properly");
			}
		}

		TEST_METHOD(RemovingHeadAndTailTest)
		{
			LinkedList<int> list;

			for (int i = 0; i < 10; ++i)
				list.addAsHead(i);

			for (int i = 10; i > 0; --i)
			{
				Assert::IsTrue(list.getCount() == i, L"Removing head does not manage count properly");
				list.removeHead();
			}

			LinkedList<int> list2;
			for (int i = 0; i < 10; ++i)
				list.addAsTail(i);

			for (int i = 10; i > 0; --i)
			{
				Assert::IsTrue(list.getCount() == i, L"Removing tail does not manage count properly");
				list.removeTail();
			}
		}
	};
}
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../Forward List/ForwardList.h"

namespace ForwardListTest
{
	TEST_CLASS(ForwardListTest)
	{
	public:
		TEST_METHOD(EmptyForwardListTest)
		{
			//empty list
			ForwardList<int> list;

			Assert::IsTrue(list.getCount() == 0, L"List is not empty when constructed");
			Assert::IsTrue(list.isEmpty(), L"IsEmpty returns false after construction");

			//adding head
			list.addAsHead(1);

			//should not be empty
			Assert::IsFalse(list.isEmpty(), L"IsEmpty retuns true after inserting as head");
			Assert::IsTrue(list.getCount() == 1, L"Count is not 1 after inserting head");

			//check if the head value is correct
			ForwardListIterator<int> &it = list.getHead();
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

			list.addAsHead(1);
			list.addAsHead(2);
			list.removeAll();
			Assert::IsTrue(list.getCount() == 0, L"List is not empty after calling removeAll");
			Assert::IsTrue(list.isEmpty(), L"List is not empty after calling removeAll");
		}
		
		TEST_METHOD(FLAddingTailTest)
		{
			ForwardList<int> list;

			list.addAsTail(1);

			//check count and isEmpty
			Assert::IsFalse(list.isEmpty(), L"IsEmpty retuns true after inserting as tail");
			Assert::IsTrue(list.getCount() == 1, L"Count is not 1 after inserting tail");

			//tail and head should be 1
			ForwardListIterator<int> &it = list.getTail();
			Assert::AreEqual(*it, 1, L"Tail is not set properly");

			ForwardListIterator<int> &it2 = list.getHead();
			Assert::AreEqual(*it, 1, L"Tail is not set properly");

			list.removeHead();

			//push tail -> 0,1,2,3,4,5,6,7,8,9
			for (int i = 0; i < 10; ++i)
			{
				list.addAsTail(i);
				Assert::IsTrue(list.getCount() == i + 1, L"Count is not set properly when adding as tail");
			}

			// start from the head
			ForwardListIterator<int> &head = list.getHead();

			for (int i = 0; head; ++head, ++i)
				Assert::IsTrue(*head == i, L"Adding as tail is not working properly");
		}

		TEST_METHOD(FLAddingHeadTest)
		{
			ForwardList<int> list;

			list.addAsHead(1);

			//check count and isEmpty
			Assert::IsFalse(list.isEmpty(), L"IsEmpty retuns true after inserting as head");
			Assert::IsTrue(list.getCount() == 1, L"Count is not 1 after inserting head");

			//tail and head should be 1
			ForwardListIterator<int> &it = list.getTail();
			Assert::AreEqual(*it, 1, L"Head is not set properly");

			ForwardListIterator<int> &it2 = list.getHead();
			Assert::AreEqual(*it2, 1, L"Head is not set properly");

			list.removeHead();

			//push head -> 9,8,7,6,5,4,3,2,1,0
			for (int i = 0; i < 10; ++i)
			{
				list.addAsHead(i);
				Assert::IsTrue(list.getCount() == i + 1, L"Count is not set properly when adding as head");
			}

			// start from the head
			ForwardListIterator<int> &iter = list.getHead();

			for (int i = 9; iter; ++iter, --i)
				Assert::AreEqual(*iter, i, L"Adding as head is not working properly");
		}

		TEST_METHOD(FLSettingTailTest)
		{
			ForwardList<int> list;

			list.addAsTail(1);

			//should update tail which is head also
			list.setTail(2);

			Assert::IsTrue(list.getCount() == 1, L"Setting tail changes count");

			//tail and head should be 2
			ForwardListIterator<int> &it = list.getTail();
			Assert::AreEqual(*it, 2, L"Tail is not set properly");

			ForwardListIterator<int> &it2 = list.getHead();
			Assert::AreEqual(*it2, 2, L"Tail is not set properly");
		}

		TEST_METHOD(FLSettingHeadTest)
		{
			ForwardList<int> list;

			list.addAsHead(1);

			//should update tail which is head also
			list.setHead(2);

			Assert::IsTrue(list.getCount() == 1, L"Setting head changes count");

			//tail and head should be 2
			ForwardListIterator<int> &it = list.getTail();
			Assert::AreEqual(*it, 2, L"Head is not set properly");

			ForwardListIterator<int> &it2 = list.getHead();
			Assert::AreEqual(*it2, 2, L"Head is not set properly");
		}


		TEST_METHOD(FLAppendingToListSimple)
		{
			ForwardList<int> list;

			//fill it
			for (int i = 0; i < 10; ++i)
				list.addAsTail(i);

			ForwardListIterator<int> &list1Tail = list.getTail();

			int count = list.getCount();

			ForwardList<int> list2;

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

		TEST_METHOD(FLAppendingToList)
		{
			ForwardList<int> list;

			ForwardList<int> list2;
			for (int i = 0; i < 10; ++i)
				list2.addAsTail(i);

			//append list2 to the empty list
			list.appendList(list2);

			ForwardListIterator<int> &it = list.getHead();
			ForwardListIterator<int> &itSrc = list2.getHead();

			//should have reconstructed them all
			for (; it && itSrc; ++it, ++itSrc)
				Assert::AreEqual(*itSrc, *it, L"Appending to non-empty list is not working properly");
			
			//should have ended simultaneously
			Assert::IsTrue(!it == !itSrc, L"Appending to non-empty list is not working properly");

			//set it to tail
			it = list.getTail();

			//now append again to the non-empty list
			list.appendList(list2);

			//move to the first appended node
			++it;
			Assert::IsFalse(!it, L"Appending to non-empty list is not working properly");

			//return source iterator to beginning
			itSrc = list2.getHead();

			//should have reconstructed them all
			for (; it && itSrc; ++it, ++itSrc)
				Assert::AreEqual(*itSrc, *it, L"Appending to list is not working properly");
			
			//should have ended simultaneously
			Assert::IsTrue(!it == !itSrc, L"Appending to list is not working properly");
		}


		TEST_METHOD(FLRemovingHeadAndTailTest)
		{
			ForwardList<int> list;

			//fill list with addHead
			for (int i = 0; i < 10; ++i)
				list.addAsHead(i);

			//removing head should decrement count
			for (int i = 10; i > 0; --i)
			{
				Assert::IsTrue(list.getCount() == i, L"Removing head does not manage count properly");
				list.removeHead();
			}

			ForwardList<int> list2;
			//fill list with addTail
			for (int i = 0; i < 10; ++i)
				list.addAsTail(i);

			//removing tail should decrement count
			for (int i = 10; i > 0; --i)
			{
				Assert::IsTrue(list.getCount() == i, L"Removing tail does not manage count properly");
				list.removeTail();
			}
		}


		TEST_METHOD(FLInsertionAfterIteratorTest)
		{

			ForwardList<int> list;

			//null iterator
			ForwardListIterator<int> &head = list.getHead();

			//should insert it as tail
			list.insertAfter(head, 2);

			head = list.getHead();
			Assert::IsTrue(*head == 2, L"Insertion after NULL iterator is not adding as tail");

			//empty list
			list.removeAll();

			//add as head
			list.addAsHead(1);

			head = list.getHead();

			//insert after the head
			list.insertAfter(head, 3);

			//move to the new node
			++head;
			Assert::IsTrue(head, L"Insertion after iterator does not update its successor");
			Assert::IsTrue(*head == 3, L"Insertion after iterator does not construct with the value passed");

			//empty again
			list.removeAll();

			list.addAsHead(1);
			list.addAsTail(3);

			//insert between 1 and 3
			head = list.getHead();

			list.insertAfter(head, 2);

			//should have added between them 
			for (int i = 0; i < 3; ++i)
			{
				Assert::IsTrue(*head == i + 1, L"Inserting between two nodes is not working properly");
				++head;
			}

			//now the traversal has finished
			Assert::IsFalse(head);
			
			//should add as tail when adding after NULL iterator
			list.insertAfter(head, 100);

			ForwardListIterator<int> &tail = list.getTail();
			Assert::AreEqual(*tail, 100, L"Inserting after NULL iterator is not adding as tail");
		}


		TEST_METHOD(FLInsertionBeforeIteratorTest)
		{

			ForwardList<int> list;

			//null iterator
			ForwardListIterator<int> &head = list.getHead();

			//should insert it as head
			list.insertBefore(head, 2);

			head = list.getHead();
			Assert::IsTrue(*head == 2, L"Insertion before NULL iterator is not adding as head");

			//empty list
			list.removeAll();

			list.addAsHead(1);
			head = list.getHead();

			//insert before the head node
			list.insertBefore(head, 3);

			//there should be a new head
			head = list.getHead();
			Assert::IsTrue(head, L"Insertion before iterator does not update its predecessor");
			Assert::IsTrue(*head == 3, L"Insertion before iterator does not construct with the value passed");

			list.removeAll();

			list.addAsHead(1);
			list.addAsTail(3);

			//insert between 1 and 3
			ForwardListIterator<int> &tail = list.getTail();

			list.insertBefore(tail, 2);

			head = list.getHead();

			//should be 1,2,3
			for (int i = 0; i < 3; ++i)
			{
				Assert::IsTrue(*head == i + 1, L"Inserting between two nodes is not working properly");
				++head;
			}

			//should be finished
			Assert::IsFalse(head);


			//should add as head when adding before NULL iterator
			list.insertBefore(head, 100);

			head = list.getHead();
			Assert::AreEqual(*head, 100, L"Inserting before NULL iterator is not adding as head");
		}

	};
}
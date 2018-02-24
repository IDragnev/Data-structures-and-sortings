#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../Forward List/ForwardList.h"

namespace ForwardListTest
{
	void fillListAddingTail(ForwardList<int>& list, int count)
	{
		for (int i = 0; i < count; ++i)
			list.addAsTail(i);
	}

	void fillListAddingHead(ForwardList<int>& list, int count)
	{
		for (int i = 0; i < count; ++i)
			list.addAsHead(i);
	}

	TEST_CLASS(ForwardListTest)
	{
	public:
		TEST_METHOD(EmptyListTest)
		{
			ForwardList<int> list;

			Assert::IsTrue(list.getCount() == 0, L"List is not empty when constructed");
			Assert::IsTrue(list.isEmpty(), L"IsEmpty returns false after construction");

			//iterators should be null
			ForwardListIterator<int> iterator = list.getHead();
			Assert::IsFalse(iterator);

			iterator = list.getTail();
			Assert::IsFalse(iterator);

			list.removeAll();
			Assert::IsTrue(list.getCount() == 0, L"List is not empty after calling removeAll");
			Assert::IsTrue(list.isEmpty(), L"List is not empty after calling removeAll");
		}
		
		TEST_METHOD(AddingTailTest)
		{
			ForwardList<int> list;

			list.addAsTail(1);

			//check count and isEmpty
			Assert::IsFalse(list.isEmpty(), L"IsEmpty retuns true after inserting as tail");
			Assert::IsTrue(list.getCount() == 1, L"Count is not 1 after inserting tail");

			//tail and head should be 1
			ForwardListIterator<int> iterator = list.getTail();
			Assert::AreEqual(*iterator, 1, L"Tail is not set properly");

			iterator = list.getHead();
			Assert::AreEqual(*iterator, 1, L"Tail is not set properly");

			list.removeHead();

			//push tail -> 0,1,2,3,4,5,6,7,8,9
			for (int i = 0; i < 10; ++i)
			{
				list.addAsTail(i);
				Assert::IsTrue(list.getCount() == i + 1, L"Count is not set properly when adding as tail");
			}

			// start from the head
			iterator = list.getHead();

			for (int i = 0; iterator; ++iterator, ++i)
				Assert::IsTrue(*iterator == i, L"Adding as tail is not working properly");
		}

		TEST_METHOD(AddingHeadTest)
		{
			ForwardList<int> list;

			list.addAsHead(1);

			//check count and isEmpty
			Assert::IsFalse(list.isEmpty(), L"IsEmpty retuns true after inserting as head");
			Assert::IsTrue(list.getCount() == 1, L"Count is not 1 after inserting head");

			//tail and head should be 1
			ForwardListIterator<int> iterator = list.getTail();
			Assert::AreEqual(*iterator, 1, L"Head is not set properly");

			iterator = list.getHead();
			Assert::AreEqual(*iterator, 1, L"Head is not set properly");

			list.removeHead();

			//push head -> 9,8,7,6,5,4,3,2,1,0
			for (int i = 0; i < 10; ++i)
			{
				list.addAsHead(i);
				Assert::IsTrue(list.getCount() == i + 1, L"Count is not set properly when adding as head");
			}

			// start from the head
			iterator = list.getHead();

			for (int i = 9; iterator; ++iterator, --i)
				Assert::AreEqual(*iterator, i, L"Adding as head is not working properly");
		}

		TEST_METHOD(SettingTailTest)
		{
			ForwardList<int> list;

			list.addAsTail(1);

			//should update tail (which is head also)
			list.setTail(2);

			Assert::IsTrue(list.getCount() == 1, L"Setting tail changes count");

			//tail and head should be 2
			ForwardListIterator<int> iterator = list.getTail();
			Assert::AreEqual(*iterator, 2, L"Tail is not set properly");

			iterator = list.getHead();
			Assert::AreEqual(*iterator, 2, L"Tail is not set properly");
		}

		TEST_METHOD(SettingHeadTest)
		{
			ForwardList<int> list;

			list.addAsHead(1);

			//should update tail which is head also
			list.setHead(2);

			Assert::IsTrue(list.getCount() == 1, L"Setting head changes count");

			//tail and head should be 2
			ForwardListIterator<int> iterator = list.getTail();
			Assert::AreEqual(*iterator, 2, L"Head is not set properly");

			iterator = list.getHead();
			Assert::AreEqual(*iterator, 2, L"Head is not set properly");
		}


		TEST_METHOD(AppendingToListCountTest)
		{
			ForwardList<int> list;

			fillListAddingTail(list,10);

			int count = list.getCount();

			ForwardList<int> list2;

			//append an empty list
			list.appendList(list2);

			//count should not be changed
			Assert::IsTrue(list.getCount() == count, L"Appending an empty list is not working properly");

			//fill list 2
			fillListAddingTail(list2, 5);

			//append a non-empty list
			list.appendList(list2);

			//count should be summed
			Assert::IsTrue(list.getCount() == (count + list2.getCount()), L"Appending a non-empty list changes count incorrectly");
		}
		
		TEST_METHOD(AppendingToListReconstruction)
		{
			ForwardList<int> list;

			ForwardList<int> list2;
			fillListAddingTail(list2, 10);

			//append list2 to the empty list
			list.appendList(list2);

			ForwardListIterator<int> iterator = list.getHead();
			ForwardListIterator<int> sourceIterator = list2.getHead();

			//should have reconstructed them all
			for (; iterator && sourceIterator; ++iterator, ++sourceIterator)
				Assert::AreEqual(*sourceIterator, *iterator, L"Appending to non-empty list is not working properly");
			
			//should have ended simultaneously
			Assert::IsTrue(!iterator == !sourceIterator, L"Appending to non-empty list is not working properly");

			//set iterator1 to tail
			iterator = list.getTail();

			//now append again to the non-empty list
			list.appendList(list2);

			//move to the first appended node to list1
			++iterator;
			Assert::IsFalse(!iterator, L"Appending to non-empty list is not working properly");

			//return source iterator to beginning
			sourceIterator = list2.getHead();

			//should have reconstructed them all
			for (; iterator && sourceIterator; ++iterator, ++sourceIterator)
				Assert::AreEqual(*sourceIterator, *iterator, L"Appending to list is not working properly");
			
			//should have ended simultaneously
			Assert::IsTrue(!iterator == !sourceIterator, L"Appending to list is not working properly");
		}


		TEST_METHOD(RemovingHeadAndTailTest)
		{
			ForwardList<int> list;

			// list = { 9,8,7,6,5,4,3,2,1,0 }
			fillListAddingHead(list, 10);

			ForwardListIterator<int> iterator = list.getHead();

			for (int i = 10; i > 0; --i)
			{
				Assert::IsTrue(*iterator == i - 1, L"Removing head does not manage head properly");
				Assert::IsTrue(list.getCount() == i, L"Removing head does not manage count properly");

				++iterator;
				list.removeHead();
			}

			list.removeAll();
			
			// list = { 0,1,2,3,4,5,6,7,8,9 }
			fillListAddingTail(list, 10);

			iterator = list.getTail();

			for (int i = 10; i > 0; --i)
			{
				Assert::IsTrue(*iterator == i - 1, L"Removing tail does not manage tail properly");
				Assert::IsTrue(list.getCount() == i, L"Removing tail does not manage count properly");

				list.removeTail();
				iterator = list.getTail();
			}
		}


		TEST_METHOD(InsertionAfterIteratorTest)
		{

			ForwardList<int> list;

			//null iterator
			ForwardListIterator<int> head = list.getHead();

			//should insert it as tail
			list.insertAfter(head, 2);

			head = list.getHead();
			Assert::IsTrue(*head == 2, L"Insertion after null iterator is not adding as tail");

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
			for (int i = 1; i < 4; ++i)
			{
				Assert::IsTrue(*head == i, L"Inserting between two nodes is not working properly");
				++head;
			}

			//now the traversal has finished
			Assert::IsFalse(head);
			
			//should add as tail when adding after NULL iterator
			list.insertAfter(head, 100);

			head = list.getTail();
			Assert::AreEqual(*head, 100, L"Inserting after null iterator is not adding as tail");
		}


		TEST_METHOD(InsertionBeforeIteratorTest)
		{

			ForwardList<int> list;

			//null iterator
			ForwardListIterator<int> head = list.getHead();

			//should insert it as head
			list.insertBefore(head, 2);

			head = list.getHead();
			Assert::IsTrue(*head == 2, L"Insertion before null iterator is not adding as head");

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
			ForwardListIterator<int> tail = list.getTail();

			list.insertBefore(tail, 2);

			head = list.getHead();

			//should be 1,2,3
			for (int i = 1; i < 4; ++i)
			{
				Assert::IsTrue(*head == i, L"Inserting between two nodes is not working properly");
				++head;
			}

			//should be finished
			Assert::IsFalse(head);

			//should add as head when adding before null iterator
			list.insertBefore(head, 100);

			head = list.getHead();
			Assert::AreEqual(*head, 100, L"Inserting before null iterator is not adding as head");
		}

		TEST_METHOD(RemovingAtHeadIteratorTest)
		{
			ForwardList<int> list;

			//null iterator
			ForwardListIterator<int> iterator = list.getHead();

			//removing at null iterator should do nothing
			list.removeAt(iterator);

			Assert::IsTrue(list.getCount() == 0, L"Removing at null iterator from an empty list does not manage count properly");
			Assert::IsTrue(list.isEmpty(), L"Removing at null iterator from an empty list is not working properly");

			// 0,1,2,3,4,5,6,7,8,9
			fillListAddingTail(list, 10);

			iterator = list.getHead();

			//removing at head
			for (int i = 0; i < 10; ++i)
			{
				Assert::IsTrue(*iterator == i, L"Removing at head iterator does not manage head properly");
				Assert::IsTrue(list.getCount() == 10 - i, L"Removing at head iterator does not manage count properly");

				list.removeAt(iterator);

				//shoould have been null-ed
				Assert::IsFalse(iterator, L"Removing at head iterator does not null iterator");

				iterator = list.getHead();
			}

			//list should be empty and iterator - null
			Assert::IsTrue(list.isEmpty());
			Assert::IsTrue(!iterator);
		}


		TEST_METHOD(RemovingAtTailIteratorTest)
		{
			ForwardList<int> list;

			//null iterator
			ForwardListIterator<int> iterator = list.getTail();

			//removing at null iterator should do nothing
			list.removeAt(iterator);

			Assert::IsTrue(list.getCount() == 0, L"Removing at null iterator from an empty list does not manage count properly");
			Assert::IsTrue(list.isEmpty() , L"Removing at null iterator from an empty list is not working properly");

			// 0,1,2,3,4,5,6,7,8,9
			fillListAddingTail(list, 10);

			iterator = list.getTail();

			//removing at tail
			for (int i = 9; i >= 0; --i)
			{
				Assert::IsTrue(*iterator == i, L"Removing at tail iterator does not manage tail properly");
				Assert::IsTrue(list.getCount() == i + 1, L"Removing at tail iterator does not manage count properly");

				list.removeAt(iterator);

				//shoould have been null-ed
				Assert::IsFalse(iterator, L"Removing at iterator does not null iterator");

				iterator = list.getTail();
			}

			//list should be empty and iterator - null
			Assert::IsTrue(list.isEmpty());
			Assert::IsTrue(!iterator);
		}



		TEST_METHOD(RemovingAtMiddleIteratorTest)
		{
			ForwardList<int> list;

			//null iterator
			ForwardListIterator<int> iterator = list.getTail();

			//removing at null iterator should do nothing
			list.removeAt(iterator);

			Assert::IsTrue(list.getCount() == 0, L"Removing at null iterator from an empty list does not manage count properly");
			Assert::IsTrue(list.isEmpty(), L"Removing at null iterator from an empty list is not working properly");

			// 0,1,2,3,4,5,6,7,8,9
			fillListAddingTail(list, 10);

			iterator = list.getHead();

			//go to the second node
			++iterator;

			ForwardListIterator<int> head = list.getHead();

			//removing at middle
			for (int i = 0; i < 10; ++i)
			{
				Assert::IsTrue(*head == 0, L"Removing at middle iterator does not manage predecessor properly");
			
				//if at least two nodes in the list
				if (i < 9)
					Assert::IsTrue(*iterator == i + 1, L"Removing at middle iterator does not manage successor properly");

				Assert::IsTrue(list.getCount() == 10 - i, L"Removing at middle iterator does not manage count properly");

				list.removeAt(iterator);

				//shoould have been null-ed
				Assert::IsFalse(iterator, L"Removing at iterator does not null iterator");

				//go to its successor
				iterator = list.getHead();
				++iterator;
			}

			//the head should be there and iterator should be null
			Assert::IsTrue(list.getCount() == 1);
			Assert::IsTrue(*head == 0);
			Assert::IsTrue(!iterator);
		}
	};
}
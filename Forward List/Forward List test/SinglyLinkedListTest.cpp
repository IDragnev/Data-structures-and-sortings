#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../Forward List/SinglyLinkedList.h"
#include <algorithm>

typedef SinglyLinkedListIterator<int> ListIterator;
typedef SinglyLinkedList<int> List;

namespace ForwardListTest
{
	void fillListAddingTail(List& list, int count)
	{
		for (int i = 0; i < count; ++i)
			list.insertAsTail(i);
	}

	void fillListAddingHead(List& list, int count)
	{
		for (int i = 0; i < count; ++i)
			list.insertAsHead(i);
	}

	bool areEqual(List& lhs, List& rhs)
	{
		if (lhs.getCount() != rhs.getCount())
			return false;
		
		ListIterator lhsIterator = lhs.getHead();
		ListIterator rhsIterator = rhs.getHead();

		for (; lhsIterator; ++lhsIterator, ++rhsIterator)
		{
			if (*lhsIterator != *rhsIterator)
				return false;
		}

		//both should have reached the end
		return !lhsIterator && !rhsIterator;
	}


	TEST_CLASS(ForwardListTest)
	{
	public:
		TEST_METHOD(EmptyListTest)
		{
			List list;

			Assert::IsTrue(list.getCount() == 0, L"List is not empty when constructed");
			Assert::IsTrue(list.isEmpty(), L"IsEmpty returns false after construction");

			ListIterator iterator = list.getHead();
			Assert::IsFalse(iterator);

			iterator = list.getTail();
			Assert::IsFalse(iterator);
		}
		
		TEST_METHOD(InsertTailTest)
		{
			List list;

			list.insertAsTail(1);
			Assert::AreEqual( *(list.getTail()), *(list.getHead()) );

			list.removeHead();

			for (int i = 0; i < 10; ++i)
			{
				list.insertAsTail(i);
				Assert::IsTrue(list.getCount() == i + 1, L"Count is not set properly when inserting as tail");
			}

			ListIterator iterator = list.getHead();

			for (int i = 0; iterator; ++iterator, ++i)
				Assert::IsTrue(*iterator == i, L"Inserting as tail is not working properly");
		}

		TEST_METHOD(InsertHeadTest)
		{
			List list;

			list.insertAsHead(1);
			Assert::AreEqual( *(list.getTail()), *(list.getHead()) );

			list.removeHead();

			const int STOP = 10;
			for (int i = 0; i < STOP; ++i)
			{
				list.insertAsHead(i);
				Assert::IsTrue(list.getCount() == i + 1, L"Count is not set properly when inserting as head");
			}

			ListIterator iterator = list.getHead();

			for (int i = STOP - 1 ; iterator; ++iterator, --i)
				Assert::AreEqual(*iterator, i, L"Adding as head is not working properly");
		}

		TEST_METHOD(AppendingToListCountTest)
		{
			List destination;
			fillListAddingTail(destination, 10);

			const int INITIAL_COUNT = destination.getCount();

			List source;
			destination.appendList(source);

			Assert::IsTrue(destination.getCount() == INITIAL_COUNT, L"Appending an empty list changes count");

			fillListAddingTail(source, 5);
			destination.appendList(source);

			Assert::IsTrue(destination.getCount() == (INITIAL_COUNT + source.getCount()), L"Appending a non-empty list changes count incorrectly");
		}
		
		TEST_METHOD(AppendingToListReconstruction)
		{
			List destination;
			List source;

			fillListAddingTail(source, 10);
			destination.appendList(source);

			Assert::IsTrue(areEqual(destination, source));

			ListIterator destinationTail = destination.getTail();
			destination.appendList(source);

			++destinationTail;
			Assert::IsFalse(!destinationTail, L"The node after tail is null after appending non-empty list");

			ListIterator sourceIterator = source.getHead();

			//TO DO : check equality between destTail and sourceIterator
		}


		TEST_METHOD(RemovingHeadTest)
		{
			const int INESERTED_COUNT = 10;

			List list;
			fillListAddingHead(list, INESERTED_COUNT);

			ListIterator iterator = list.getHead();
			for (int i = INESERTED_COUNT; i > 0; --i)
			{
				Assert::IsTrue(*iterator == i - 1, L"Removing head does not manage head properly");
				Assert::IsTrue(list.getCount() == i, L"Removing head does not manage count properly");

				++iterator;
				list.removeHead();
			}

		}
		
		TEST_METHOD(RemovingTailTest)
		{
			const int INESERTED_COUNT = 10;

			List list;
			fillListAddingTail(list, INESERTED_COUNT);

			ListIterator iterator = list.getTail();
			for (int i = INESERTED_COUNT; i > 0; --i)
			{
				Assert::IsTrue(*iterator == i - 1, L"Removing tail does not manage tail properly");
				Assert::IsTrue(list.getCount() == i, L"Removing tail does not manage count properly");

				list.removeTail();
				iterator = list.getTail();
			}
		}


		TEST_METHOD(InsertionAfterIteratorTest)
		{

			List list;

			//null iterator
			ListIterator head = list.getHead();

			//should insert it as tail
			list.insertAfter(head, 2);

			head = list.getHead();
			Assert::IsTrue(*head == 2, L"Insertion after null iterator is not adding as tail");

			//empty list
			list.empty();

			//add as head
			list.insertAsHead(1);

			head = list.getHead();

			//insert after the head
			list.insertAfter(head, 3);

			//move to the new node
			++head;
			Assert::IsTrue(head, L"Insertion after iterator does not update its successor");
			Assert::IsTrue(*head == 3, L"Insertion after iterator does not construct with the value passed");

			//empty again
			list.empty();

			list.insertAsHead(1);
			list.insertAsTail(3);

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

			List list;

			//null iterator
			ListIterator head = list.getHead();

			//should insert it as head
			list.insertBefore(head, 2);

			head = list.getHead();
			Assert::IsTrue(*head == 2, L"Insertion before null iterator is not adding as head");

			//empty list
			list.empty();

			list.insertAsHead(1);
			head = list.getHead();

			//insert before the head node
			list.insertBefore(head, 3);

			//there should be a new head
			head = list.getHead();
			Assert::IsTrue(head, L"Insertion before iterator does not update its predecessor");
			Assert::IsTrue(*head == 3, L"Insertion before iterator does not construct with the value passed");

			list.empty();

			list.insertAsHead(1);
			list.insertAsTail(3);

			//insert between 1 and 3
			ListIterator tail = list.getTail();

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
			List list;

			//null iterator
			ListIterator iterator = list.getHead();

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
			List list;

			//null iterator
			ListIterator iterator = list.getTail();

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
			List list;

			//null iterator
			ListIterator iterator = list.getTail();

			//removing at null iterator should do nothing
			list.removeAt(iterator);

			Assert::IsTrue(list.getCount() == 0, L"Removing at null iterator from an empty list does not manage count properly");
			Assert::IsTrue(list.isEmpty(), L"Removing at null iterator from an empty list is not working properly");

			// 0,1,2,3,4,5,6,7,8,9
			fillListAddingTail(list, 10);

			iterator = list.getHead();

			//go to the second node
			++iterator;

			ListIterator head = list.getHead();

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


		TEST_METHOD(CopyCtorTest)
		{
			List list;
			
			{
				//from an empty list
				List list2(list);
				Assert::IsTrue(list2.getCount() == 0, L"Copy-construction from an empty list is does not construct an empty list");
				Assert::IsTrue(list2.isEmpty(), L"Copy-construction from an empty list does not construct an empty list");
			}

			//from non empty
			fillListAddingHead(list, 10);

			List list2(list);

			Assert::IsTrue(areEqual(list, list2), L"Copy-construction is not working properly");
		}

		TEST_METHOD(MoveCtorTest)
		{
			List list;

			{
				//from an empty list
				List list2(std::move(list));

				Assert::IsTrue(list2.getCount() == 0, L"Move-construction from an empty list does not construct an empty list");
				Assert::IsTrue(list2.isEmpty(), L"Move-construction from an empty list does not construct an empty list");

				//argument should be left empty
				Assert::IsTrue(list.getCount() == 0, L"Argument is not empty after move-construction");
				Assert::IsTrue(list.isEmpty(), L"Argument is not empty after move-construction");
			}

			//0,1,2,3,4,5,6,7,8,9
			fillListAddingTail(list, 10);

			//from a non-empty
			List list2(std::move(list));

			Assert::IsTrue(list2.getCount() == 10, L"Move-construction from a non-empty list is not managing count properly");
			Assert::IsFalse(list2.isEmpty(), L"Move-construction from a non-empty list constructs an empty list");

			//argument should be left empty
			Assert::IsTrue(list.getCount() == 0, L"Argument is not empty after move-construction");
			Assert::IsTrue(list.isEmpty(), L"Argument is not empty after move-construction");

			ListIterator head = list2.getHead();
			
			for (int i = 0; i < 10; ++i, ++head)
				Assert::IsTrue(*head == i, L"Move-construction is not working properly");
		}

		TEST_METHOD(CopyAssignmentTest)
		{
			List list;
			List list2;

			//from empty to empty
			list = list2;

			//should be empty
			Assert::IsTrue(list.getCount() == 0, L"Copy assignment from an empty list is not leaving lhs empty");
			Assert::IsTrue(list.isEmpty(), L"Copy assignment from an empty list is not leaving lhs empty");

			fillListAddingTail(list2, 10);

			//non-empty to empty
			list = list2;

			Assert::IsTrue(areEqual(list, list2), L"Copy assignment from non-empty to empty is not working properly");

			//append one more to list2
			list2.insertAsTail(11);

			//non-empty to non-empty
			list = list2;

			Assert::IsTrue(areEqual(list, list2), L"Copy assignment from non-empty to non-empty is not working properly");

			//empty list2
			list2.empty();

			//empty to non-empty
			list = list2;

			//should be empty
			Assert::IsTrue(list.getCount() == 0, L"Copy assignment from an empty list is not leaving lhs empty");
			Assert::IsTrue(list.isEmpty(), L"Copy assignment from an empty list is not leaving lhs empty");
		}

		TEST_METHOD(MoveAssignmentTest)
		{
			List list;
			List list2;

			//from empty to empty
			list = std::move(list2);

			//both should be empty
			Assert::IsTrue(list.getCount() == 0, L"Move assignment from an empty list is not leaving lhs empty");
			Assert::IsTrue(list.isEmpty(), L"Move assignment from an empty list is not leaving lhs empty");
			Assert::IsTrue(list2.getCount() == 0, L"Move assignment from an empty list is not leaving rhs empty");
			Assert::IsTrue(list2.isEmpty(), L"Move assignment from an empty list is not leaving rhs empty");

			//0,1,2,3,4,5,6,7,8,9
			fillListAddingTail(list2, 10);

			//non-empty to empty
			list = std::move(list2);

			Assert::IsTrue(list.getCount() == 10, L"Move assignment is not working properly");
			
			ListIterator iterator = list.getHead();

			for (int i = 0; i < 10; ++i, ++iterator)
				Assert::IsTrue(*iterator == i, L"Move assignment is not working properly");

			//argument should be left empty
			Assert::IsTrue(list2.getCount() == 0, L"Move assignment from a non-empty list is not leaving rhs empty");
			Assert::IsTrue(list2.isEmpty(), L"Move assignment from a non-empty list is not leaving rhs empty");

			// 0,1,2,3,4, ... ,19,20
			fillListAddingTail(list2, 20);

			//non-empty to non-empty
			list = std::move(list2);

			iterator = list.getHead();

			for (int i = 0; i < 20; ++i, ++iterator)
				Assert::IsTrue(*iterator == i, L"Move assignment is not working properly");
			
			//argument should be left empty
			Assert::IsTrue(list2.getCount() == 0, L"Move assignment from a non-empty list is not leaving rhs empty");
			Assert::IsTrue(list2.isEmpty(), L"Move assignment from a non-empty list is not leaving rhs empty");


			//empty to non-empty
			list = std::move(list2);

			//both should be empty
			Assert::IsTrue(list.getCount() == 0, L"Move assignment from an empty list is not leaving lhs empty");
			Assert::IsTrue(list.isEmpty(), L"Move assignment from an empty list is not leaving lhs empty");
			Assert::IsTrue(list2.getCount() == 0, L"Move assignment from an empty list is not leaving rhs empty");
			Assert::IsTrue(list2.isEmpty(), L"Move assignment from an empty list is not leaving rhs empty");
		}
	};
}
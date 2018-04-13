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

	bool doIteratorsPointToEqualLists(ListIterator& lhsHead, ListIterator& rhsHead)
	{
		while (lhsHead)
		{
			if (*lhsHead != *rhsHead)
				return false;

			++lhsHead;
			++rhsHead;
		}

		return !lhsHead && !rhsHead;
	}

	bool areEqual(List& lhs, List& rhs)
	{
		return (lhs.getCount() == rhs.getCount()) && doIteratorsPointToEqualLists(lhs.getHead(), rhs.getHead());
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

			Assert::IsTrue( areEqual(destination, source) );

			ListIterator destinationTail = destination.getTail();
			destination.appendList(source);

			++destinationTail;
			Assert::IsFalse(!destinationTail, L"The node after tail is null after appending non-empty list");

			ListIterator sourceHead = source.getHead();

			Assert::IsTrue(doIteratorsPointToEqualLists(destinationTail, sourceHead));
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

		TEST_METHOD(InsertionAfterNullIterator)
		{
			List list;

			for (int i = 0; i < 100; ++i)
			{
				ListIterator iterator = list.getTail();
				//forse null
				++iterator;

				//should insert it as tail
				list.insertAfter(iterator, i);

				ListIterator tail = list.getTail();
				Assert::IsTrue(*tail == i);
			}
		}

		TEST_METHOD(InsertingAfterHeadIterator)
		{
			List list;
			list.insertAsHead(1);

			for (int i = 0; i < 100; ++i)
			{
				ListIterator headIterator = list.getHead();
				list.insertAfter(headIterator, i);

				++headIterator;

				Assert::IsTrue(headIterator, L"Insertion after iterator does not update its successor");
				Assert::IsTrue(*headIterator == i, L"Insertion after iterator does not construct with the value passed");
			}
		}

		TEST_METHOD(InsertingBetweenNodesWithIterator)
		{
			List list;

			list.insertAsHead(1);
			list.insertAsTail(3);

			ListIterator headIterator = list.getHead();
			list.insertAfter(headIterator, 2);

			for (int i = 1; i < 4; ++i)
			{
				Assert::IsTrue(*headIterator == i, L"Inserting between two nodes with iterator is not working properly");
				++headIterator;
			}

			Assert::IsFalse(headIterator);
		}

		TEST_METHOD(InsertingAfterTailIterator)
		{
			List list;
			list.insertAsTail(1);

			for (int i = 0; i < 100; ++i)
			{
				ListIterator tailIterator = list.getTail();
				list.insertAfter(tailIterator, i);

				++tailIterator;

				Assert::IsTrue(tailIterator);
				Assert::IsTrue(*tailIterator == i, L"Insertion after tail iterator does not construct with the value passed");
			}
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
			List source;

			List destinationOne(source);
			Assert::IsTrue(areEqual(source, destinationOne));

			fillListAddingHead(source, 10);

			List destinationTwo(source);
			Assert::IsTrue(areEqual(source, destinationTwo));
		}

		TEST_METHOD(MoveCtorFromEmpty)
		{
			List source;
			List destination(std::move(source));

			Assert::IsTrue(destination.getCount() == 0);
			Assert::IsTrue(destination.isEmpty());

			Assert::IsTrue(source.getCount() == 0);
			Assert::IsTrue(source.isEmpty());
		}

		TEST_METHOD(MoveCtorFromNonEmpty)
		{
			List source;
			fillListAddingTail(source, 10);

			List initialSourceCopy(source);

			List destination(std::move(source));

			Assert::IsTrue( areEqual(destination, initialSourceCopy) );

			Assert::IsTrue(source.getCount() == 0);
			Assert::IsTrue(source.isEmpty());
		}

		TEST_METHOD(CopyAssignmentEmptyToEmpty)
		{
			List lhs;
			List rhs;

			lhs = rhs;

			Assert::IsTrue(areEqual(lhs, rhs));
		}

		TEST_METHOD(CopyAssignmentNonEmptyToEmpty)
		{
			List lhs;
			List rhs;

			fillListAddingTail(rhs, 10);

			lhs = rhs;

			Assert::IsTrue(areEqual(lhs, rhs));
		}

		TEST_METHOD(CopyAssignmentNonEmptyToNonEmpty)
		{
			List lhs;
			List rhs;

			fillListAddingHead(lhs, 20);
			fillListAddingTail(rhs, 30);

			lhs = rhs;

			Assert::IsTrue(areEqual(lhs, rhs));
		}

		TEST_METHOD(CopyAssignmentEmptyToNonEmpty)
		{
			List lhs;
			List rhs;

			fillListAddingHead(lhs, 20);

			lhs = rhs;

			Assert::IsTrue(areEqual(lhs, rhs));
		}
		
		TEST_METHOD(MoveAssignmentEmptyToEmpty)
		{
			List lhs;
			List rhs;

			lhs = std::move(rhs);

			Assert::IsTrue(lhs.getCount() == 0);
			Assert::IsTrue(lhs.isEmpty());
			Assert::IsTrue(rhs.getCount() == 0);
			Assert::IsTrue(rhs.isEmpty());
		}

		TEST_METHOD(MoveAssignmentNonEmptyToEmpty)
		{
			List lhs;
			List rhs;

			fillListAddingHead(rhs, 20);

			List initialRhsCopy(rhs);

			lhs = std::move(rhs);

			Assert::IsTrue(areEqual(lhs, initialRhsCopy));
			Assert::IsTrue(rhs.getCount() == 0);
			Assert::IsTrue(rhs.isEmpty());
		}
		
		TEST_METHOD(MoveAssignmentEmptyToNonEmpty)
		{
			List lhs;
			List rhs;

			fillListAddingHead(lhs, 30);

			lhs = std::move(rhs);

			Assert::IsTrue(lhs.getCount() == 0);
			Assert::IsTrue(lhs.isEmpty());
			Assert::IsTrue(rhs.getCount() == 0);
			Assert::IsTrue(rhs.isEmpty());
		}


		TEST_METHOD(MoveAssignmentNonEmptyToNonEmpty)
		{
			List lhs;
			List rhs;

			fillListAddingHead(lhs, 30);
			fillListAddingTail(rhs, 15);

			List initialRhsCopy(rhs);

			lhs = std::move(rhs);

			Assert::IsTrue(areEqual(lhs, initialRhsCopy));
			Assert::IsTrue(rhs.getCount() == 0);
			Assert::IsTrue(rhs.isEmpty());
		}
	};
}
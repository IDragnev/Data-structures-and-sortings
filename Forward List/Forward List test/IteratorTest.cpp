#include "CppUnitTest.h"

#include "../Forward List/SinglyLinkedList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

typedef SinglyLinkedListIterator<int> ListIterator;
typedef SinglyLinkedList<int> List;

namespace ForwardListTest
{		

	void fillListAddingTail(List& list, int count);
	void fillListAddingHead(List& list, int count);

	TEST_CLASS(IteratorTest)
	{
	public:
		TEST_METHOD(IteratorBoundariesTest)
		{
			List list;

			fillListAddingTail(list, 5);
			
			ListIterator iterator = list.getHead();
			int count = 0;

			for (; iterator; ++iterator)
				++count;

			Assert::IsTrue(count == 5);
		}

		TEST_METHOD(IteratorDerrefTest)
		{
			List list;

			fillListAddingTail(list, 10);

			ListIterator iterator = list.getHead();

			for (int i = 0; iterator; ++iterator, ++i)
				Assert::AreEqual(*iterator, i);
		}

		TEST_METHOD(IteratorEqualtyOperatorsTest)
		{
				List list;
				
				fillListAddingTail(list, 10);

				ListIterator head = list.getHead();
				ListIterator tail = list.getTail();

				Assert::IsFalse(head == tail);
				Assert::IsTrue(head != tail);

				tail = list.getHead();

				Assert::IsTrue(head == tail);
				Assert::IsFalse(head != tail);

				list.empty();

				head = list.getHead();
				tail = list.getTail();

				Assert::IsTrue(head == tail);
				Assert::IsFalse(head != tail);

		}
	};
}
#include "CppUnitTest.h"

#include "../Forward List/ForwardList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ForwardListTest
{		
	void fillListAddingTail(ForwardList<int>& list, int count);
	void fillListAddingHead(ForwardList<int>& list, int count);

	TEST_CLASS(IteratorTest)
	{
	public:

		TEST_METHOD(IteratorBoundariesTest)
		{
			ForwardList<int> list;

			fillListAddingTail(list, 5);
			
			ForwardListIterator<int> it = list.getHead();

			int count = 0;
			for (; it; ++it, ++count);

			Assert::IsTrue(count == 5, L"Iterator is not moving forward in the list properly");
		}

		TEST_METHOD(IteratorDerrefTest)
		{
			ForwardList<int> list;

			fillListAddingTail(list, 10);

			ForwardListIterator<int> it = list.getHead();

			for (int i = 0; it; ++it, ++i)
				Assert::AreEqual(*it, i, L"Operator* of iterator is not working properly");
		}

		TEST_METHOD(IteratorEqualtyOperatorsTest)
		{
				ForwardList<int> list;
				
				fillListAddingTail(list, 10);

				ForwardListIterator<int> head = list.getHead();
				ForwardListIterator<int> tail = list.getTail();

				Assert::IsFalse(head == tail, L"Operator== is not working properly");
				Assert::IsTrue(head != tail, L"Operator!= is not working properly");

				tail = list.getHead();

				Assert::IsTrue(head == tail, L"Operator== is not working properly");
				Assert::IsFalse(head != tail, L"Operator!= is not working properly");

				list.removeAll();

				head = list.getHead();
				tail = list.getTail();

				Assert::IsTrue(head == tail, L"Operator== is not working properly");
				Assert::IsFalse(head != tail, L"Operator!= is not working properly");

		}
	};
}
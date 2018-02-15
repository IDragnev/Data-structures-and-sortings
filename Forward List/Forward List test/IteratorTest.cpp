#include "CppUnitTest.h"

#include "../Forward List/ForwardList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ForwardListtest
{		
	TEST_CLASS(FLIteratorTest)
	{
	public:
		
		TEST_METHOD(FLNodeTest)
		{
			Node<int> node(1);
			Assert::IsFalse(node.hasSuccessor(), L"Node has successor even when default constructed");

			Node<int> node2(33, &node);
			Assert::IsTrue(node2.hasSuccessor(), L"Node has no successor after constructing it with such");
		}

		TEST_METHOD(FLIteratorBoundariesTest)
		{
			ForwardList<int> list;

			for (int i = 0; i < 5; ++i)
				list.addAsHead(i);
			
			ForwardListIterator<int> &it = list.getHead();

			int count = 0;
			for (; it; ++it, ++count);

			Assert::IsTrue(count == 5, L"Iterator is not moving forward in the list properly");
		}

		TEST_METHOD(FLIteratorDerrefTest)
		{
			ForwardList<int> list;

			for (int i = 0; i < 5; ++i)
				list.addAsTail(i);

			ForwardListIterator<int> &it = list.getHead();

			for (int i = 0; it; ++it, ++i)
				Assert::AreEqual(*it, i, L"Operator* of iterator is not working properly");
		}

	};
}
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../Template Dynamic Array/DynamicArray.h"

namespace DynamicArrayTest
{		
	TEST_CLASS(DynamicArrayTest)
	{
		TEST_METHOD(EmptyDynArrayTtest)
		{
			DynamicArray<int> darr;

			Assert::IsTrue(darr.getSize() == 16, L"Default constructor not setting size with 16");
			Assert::IsTrue(darr.getCount() == 0, L"Default constructor not setting count with 0");
			Assert::IsTrue(darr.isEmpty(), L"isEmpty() returns false even though count is 0");

			for (int i = 0; i < 10; ++i)
				Assert::IsFalse(darr.find(i) != -1,L"Find returns a valid index in an empty array");
		}

		TEST_METHOD(AddingAndRemoval)
		{
			DynamicArray<int> darr(16);

			Assert::IsTrue(darr.getSize() == 16, L"Size is not the one which the constructor was passed");
			Assert::IsTrue(darr.getCount() == 0, L"Count is not 0 even though the array is empty");

			for (int i = 1; i < 11; ++i)
			{
				darr.add(i);
				Assert::IsTrue(darr.getSize() == 16, L"Size is changed even thoug no resizing is needed(done)");
				Assert::IsTrue(darr.getCount() == i, L"Count is not set correctly after adding");
				Assert::IsFalse(darr.isEmpty(), L"IsEmpty() returns true after adding elements");
				Assert::IsTrue(darr[i - 1] = i, L"Adding is not working correctly");
			}
		

			int count = darr.getCount();
			for (int i = 1; i < 11; ++i)
			{
				darr.remove(0);
				Assert::IsTrue(darr.getCount() == count - 1, L"Removing does not handle count correctly");
				count--;
			}
			
			Assert::IsTrue(darr.isEmpty(), L"isEmpty() returns false even after removing all the elements");

			darr.add(1);
			Assert::IsTrue(darr.getCount() == 1);

			darr.addAt(0, 0);
			Assert::IsTrue(darr[0] == 0 && darr[1] == 1, L"addAt() is not working correctly");
			Assert::IsTrue(darr.getCount() == 2, L"Count is not handled correctly when using addAt()");


			for (int i = 0; i < 5; ++i)
			{
				darr.addAt(0,i);
				Assert::IsTrue(darr.getAt(0) == i, L"getAt() is not working correctly");
			}
		}


		TEST_METHOD(Other)
		{
			DynamicArray<int> darr(16);

			for (int i = 0; i < 17; ++i)
			{
				darr.add(i);
			}

			Assert::IsTrue(darr.getSize() == 32, L"Resize is not working correctly");


			for (int i = 0; i < 17; ++i)
			{
				Assert::IsTrue(darr.find(i) == i, L"Find is not working correctly");
			}

			darr.makeEmpty();
			Assert::IsTrue(darr.isEmpty(), L"makeEmpty() is not working correctly");
			
			darr.ensureSize(24);
			Assert::IsTrue(darr.getSize() == 24, L"ensureSize is not working correctly");		
		}

		TEST_METHOD(Big4Test)
		{
			DynamicArray<int> darr(16);

			Assert::IsTrue(darr.getSize() == 16, L"Default constructor not setting size with 16");
			Assert::IsTrue(darr.getCount() == 0, L"Default constructor not setting count with 0");
			Assert::IsTrue(darr.isEmpty(), L"isEmpty() returns false even though count is 0");

			for (int i = 0; i < 10; ++i)
				darr += i;

			DynamicArray<int> darr2(darr);
			Assert::IsTrue(darr.getSize() == darr2.getSize(), L"Copy constructor is not copying size correctly");
			Assert::IsTrue(darr.getCount() == darr2.getCount(), L"Copy constructor is not copying count correctly");
			Assert::IsFalse(darr.isEmpty(), L"isEmpty() returns true after copying from non-empty array");

			darr2.remove(3);
			darr2.remove(4);

			darr2 = darr;
			Assert::IsTrue(darr.getSize() == darr2.getSize(), L"operator= is not copying size correctly");
			Assert::IsTrue(darr.getCount() == darr2.getCount(), L"operator= is not copying count correctly");
		}
	};
}
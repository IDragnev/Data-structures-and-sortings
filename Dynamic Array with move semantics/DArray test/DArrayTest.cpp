#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../Dynamic Array with move semantics/DArray.h"

namespace DArraytest
{		
	void fillArray(DArray<int>& arr, int count, int first = 0, int step = 1)
	{
		for (int i = first; i < count; i += step)
			arr.add(i);
	}

	bool areEqual(DArray<int>& darr1, DArray<int>& darr2)
	{
		int count = darr1.getCount();

		if (count != darr2.getCount())
			return false;

		for (int i = 0; i < count; ++i)
		{
			if (darr1[i] != darr2[i])
				return false;
		}

		return true;
	}

	TEST_CLASS(DArrayTest)
	{
	public:
		
		TEST_METHOD(EmptyDArrayTest)
		{
			DArray<int> darr;

			Assert::IsTrue(darr.getSize() == 0, L"Default constructor not setting size with 0");
			Assert::IsTrue(darr.getCount() == 0, L"Default constructor not setting count with 0");
			Assert::IsTrue(darr.isEmpty(), L"isEmpty() returns false even though count is 0");

			for (int i = 0; i < 10; ++i)
				Assert::IsFalse(darr.search(i) != -1, L"Find returns a valid index in an empty array");
		}

		TEST_METHOD(AddingAndRemoval)
		{
			DArray<int> darr(16);

			Assert::IsTrue(darr.getSize() == 16, L"Size is not the one which the constructor was passed");
			Assert::IsTrue(darr.getCount() == 0, L"Count is not 0 even though the array is empty");

			for (int i = 1; i < 11; ++i)
			{
				darr.add(i);
				Assert::IsTrue(darr.getSize() == 16, L"Size is changed even though no resizing is needed(done)");
				Assert::IsTrue(darr.getCount() == i, L"Count is not set correctly after adding");
				Assert::IsFalse(darr.isEmpty(), L"IsEmpty() returns true after adding elements");
				Assert::IsTrue(darr[i - 1] == i, L"Adding is not working correctly");
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
				darr.addAt(0, i);
				Assert::IsTrue(darr[0] == i, L"addAt() is not working correctly");
			}
		}


		TEST_METHOD(Other)
		{
			DArray<int> darr(16);

			fillArray(darr, 17);

			Assert::IsTrue(darr.getSize() == 32, L"Resize is not working correctly");


			for (int i = 0; i < 17; ++i)
				Assert::IsTrue(darr.search(i) == i, L"Find is not working correctly");

			darr.empty();
			Assert::IsTrue(darr.isEmpty(), L"empty() is not working correctly");

			darr.ensureSize(64);
			Assert::IsTrue(darr.getSize() == 64, L"ensureSize is not working correctly");
		}

		TEST_METHOD(SimpleConstructorTest)
		{
			DArray<int> darr(16);

			Assert::IsTrue(darr.getSize() == 16, L"Constructor not setting size with sent value");
			Assert::IsTrue(darr.getCount() == 0);
			Assert::IsTrue(darr.isEmpty(), L"isEmpty() returns false even though count is 0");

			DArray<int> darr2(16, 1);

			Assert::IsTrue(darr2.getSize() == 16, L"Constructor not setting size with sent value");
			Assert::IsTrue(darr2.getCount() == 1, L"Constructor not setting count with sent value");
			Assert::IsFalse(darr2.isEmpty(), L"isEmpty() returns true even though count is 1");
		}


		TEST_METHOD(CopyCtorTest)
		{
			{
				//from a non-empty
				DArray<int> darr(16);

				int i;

				fillArray(darr, 10);

				DArray<int> darr2(darr);

				Assert::IsTrue(darr.getSize() == darr2.getSize(), L"Copy constructor is not copying size correctly");
				Assert::IsTrue(darr.getCount() == darr2.getCount(), L"Copy constructor is not copying count correctly");
				Assert::IsFalse(darr2.isEmpty(), L"isEmpty() returns true after copying from non-empty array");

				Assert::IsTrue(areEqual(darr, darr2), L"Copy-constructed array holds different values");
			}

			//from an empty 
			DArray<int> darr;
			DArray<int> darr2(darr);

			Assert::IsTrue(darr.getSize() == darr2.getSize(), L"Copy constructor is not copying size correctly");
			Assert::IsTrue(darr.getCount() == darr2.getCount(), L"Copy constructor is not copying count correctly");
			Assert::IsTrue(darr2.isEmpty(), L"isEmpty() returns false after copying from an empty array");

			Assert::IsTrue(areEqual(darr, darr2), L"Copy-constructed array holds different values");
		}


		TEST_METHOD(MoveConstructorTest)
		{
			{
				//from an empty
				DArray<int> temp;

				DArray<int> darr(std::move(temp));
				
				//should be null-empty
				Assert::IsTrue(darr.getCount() == 0);
				Assert::IsTrue(darr.getSize() == 0);
				Assert::IsTrue(darr.isEmpty());

				//should be nulled
				Assert::IsTrue(temp.getCount() == 0);
				Assert::IsTrue(temp.getSize() == 0);
				Assert::IsTrue(temp.isEmpty());
			}

			//from a non-empty
			DArray<int> temp(10);

			fillArray(temp, 4);

			DArray<int> darr(std::move(temp));

			Assert::IsTrue(darr.getCount() == 4);
			Assert::IsTrue(darr.getSize() == 10);
			Assert::IsFalse(darr.isEmpty());

			for (int i = 0; i < 4; ++i)
				Assert::IsTrue(darr[i] == i);

			//should be nulled
			Assert::IsTrue(temp.getCount() == 0);
			Assert::IsTrue(temp.getSize() == 0);
			Assert::IsTrue(temp.isEmpty());
		}

		TEST_METHOD(CopyAssignmentTest)
		{
			{
				//empty to empty
				DArray<int> darr;
				DArray<int> darr2;

				darr2 = darr;

				Assert::IsTrue(darr2.getCount() == 0);
				Assert::IsTrue(darr2.getSize() == 0);
				Assert::IsTrue(darr2.isEmpty());
			}

			{
				//empty to non-empty
				DArray<int> darr;
				fillArray(darr, 4);

				DArray<int> darr2;

				darr = darr2;

				Assert::IsTrue(darr.getCount() == 0);
				Assert::IsTrue(darr.getSize() == 0);
				Assert::IsTrue(darr.isEmpty());
			}


			{
				//non-empty to empty
				DArray<int> darr(8);

				fillArray(darr, 4);

				DArray<int> darr2;
				darr2 = darr;

				Assert::IsTrue(darr2.getCount() == darr.getCount());
				Assert::IsTrue(darr2.getSize() == darr.getSize());
				Assert::IsFalse(darr2.isEmpty());

				Assert::IsTrue(areEqual(darr, darr2), L"Copy-assigned array holds different values");
			}


			{
				//non-empty to non-empty
				DArray<int> darr(8);

				fillArray(darr, 4);

				DArray<int> darr2;
				fillArray(darr2, 7, 0, 5);

				darr2 = darr;

				Assert::IsTrue(darr2.getCount() == darr.getCount());
				Assert::IsTrue(darr2.getSize() == darr.getSize());
				Assert::IsFalse(darr2.isEmpty());

				Assert::IsTrue(areEqual(darr, darr2), L"Copy-assigned array holds different values");
			}
		}

		TEST_METHOD(MoveAssignmentTest)
		{
			{
				//empty to empty
				DArray<int> darr;
				DArray<int> darr2;

				darr2 = std::move(darr);

				Assert::IsTrue(darr.getCount() == 0);
				Assert::IsTrue(darr.getSize() == 0);
				Assert::IsTrue(darr.isEmpty());

				Assert::IsTrue(darr2.getCount() == 0);
				Assert::IsTrue(darr2.getSize() == 0);
				Assert::IsTrue(darr2.isEmpty());
			}

			{
				//empty to non-empty
				DArray<int> darr;
				fillArray(darr, 4);

				DArray<int> darr2;

				darr = std::move(darr2);

				Assert::IsTrue(darr.getCount() == 0);
				Assert::IsTrue(darr.getSize() == 0);
				Assert::IsTrue(darr.isEmpty());

				Assert::IsTrue(darr2.getCount() == 0);
				Assert::IsTrue(darr2.getSize() == 0);
				Assert::IsTrue(darr2.isEmpty());
			}


			{
				//non-empty to empty
				DArray<int> darr(8);

				fillArray(darr, 4);

				DArray<int> darr2;
				darr2 = std::move(darr);

				//argument is nulled
				Assert::IsTrue(darr.getCount() == 0);
				Assert::IsTrue(darr.getSize() == 0);
				Assert::IsTrue(darr.isEmpty());

				Assert::IsTrue(darr2.getCount() == 4);
				Assert::IsTrue(darr2.getSize() == 8);
				Assert::IsFalse(darr2.isEmpty());

				for (int i = 0; i < 4; ++i)
					Assert::IsTrue(darr2[i] == i);
			}


			{
				//non-empty to non-empty
				DArray<int> darr(8);

				fillArray(darr, 4);

				DArray<int> darr2;
				fillArray(darr2, 7, 0, 5);

				darr2 = std::move(darr);

				//argument is nulled
				Assert::IsTrue(darr.getCount() == 0);
				Assert::IsTrue(darr.getSize() == 0);
				Assert::IsTrue(darr.isEmpty());

				Assert::IsTrue(darr2.getCount() == 4);
				Assert::IsTrue(darr2.getSize() == 8);
				Assert::IsFalse(darr2.isEmpty());

				for (int i = 0; i < 4; ++i)
					Assert::IsTrue(darr2[i] == i);
			}
		}

		TEST_METHOD(LValueAppend)
		{
			DArray<int> darr(8);

			fillArray(darr, 5);

			DArray<int> darr2(10);

			fillArray(darr2, 10, 5, 1);
	
			darr.append(darr2);

			//arg is left untouched
			Assert::IsTrue(darr2.getCount() == 5);
			Assert::IsTrue(darr2.getSize() == 10);
			Assert::IsFalse(darr2.isEmpty());

			Assert::IsTrue(darr.getCount() == 5 + darr2.getCount());
			for (int i = 0; i < 10; ++i)
				Assert::IsTrue(darr[i] == i);
		}

		TEST_METHOD(RValueAppend)
		{
			DArray<int> darr(8);

			fillArray(darr, 5);

			DArray<int> darr2(10);
			fillArray(darr2, 10, 5, 1);

			darr.append(std::move(darr2));

			//arg is nulled
			Assert::IsTrue(darr2.getCount() == 0);
			Assert::IsTrue(darr2.getSize() == 0);
			Assert::IsTrue(darr2.isEmpty());

			Assert::IsTrue(darr.getCount() == 10);
			for (int i = 0; i < 10; ++i)
				Assert::IsTrue(darr[i] == i);
		}
	};
}
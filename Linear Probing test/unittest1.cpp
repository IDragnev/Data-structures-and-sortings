#include "CppUnitTest.h"
#include "../Hashing/LPMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LinearProbingtest
{		
	class HashFun
	{
	public:
		int operator()(char c)const
		{
			return c;
		}
	};

	void fillMapUppers(LPMap<HashFun>& map)
	{
		Item item;

		//fill the table with 25 items
		for (int i = 65; i < 91; ++i)
		{
			item.setKey(i);
			map.insert(item);
		}
	}


	TEST_CLASS(LinearProbingTest)
	{
	public:
		
		TEST_METHOD(BasicLPMapTest)
		{
			LPMap<HashFun> map(8);

			Assert::IsTrue(map.getCount() == 0, L"Count is not 0 after construction");
			Assert::IsTrue(map.isEmpty(), L"isEmpty() returns false after construction");
			Assert::IsFalse(map.isFull(), L"isFull() returns true after construction");

			LPMap<HashFun> map2(map);

			Assert::IsTrue(map2.getCount() == 0, L"Count is not 0 after construction");
			Assert::IsTrue(map2.isEmpty(), L"isEmpty() returns false after construction");
			Assert::IsFalse(map2.isFull(), L"isFull() returns true after construction");

			map2.insert(Item('1'));
			Assert::IsTrue(map2.getCount() == 1, L"Count is not 1 after one insertion");
			Assert::IsFalse(map2.isEmpty(), L"isEmpty() returns true after one insertion");
			Assert::IsFalse(map2.isFull(), L"isFull() returns true after one insertion (size > 2)");

			//revert to empty state
			map2 = map;
			Assert::IsTrue(map2.getCount() == 0, L"Count is not 0 after construction");
			Assert::IsTrue(map2.isEmpty(), L"isEmpty() returns false after construction");
			Assert::IsFalse(map2.isFull(), L"isFull() returns true after construction");
		}

		TEST_METHOD(LPMapInsertionAndSearchTest)
		{
			LPMap<HashFun> map(50);

			Item item;
			
			//fill the table with 60 items
			for (int i = 1; i < 60; ++i)
			{
				item.setKey(i);
				map.insert(item);
				Assert::IsTrue(map.getCount() == i, L"Insertion does not manage count appropriately");
				Assert::IsFalse(map.isFull(), L"Map is full despite inserting less keys than sent size");
				Assert::IsFalse(map.isEmpty(), L"Map is empty despite the insertions");
			}

			//search all the items
			for (int i = 1; i < 60; ++i)
			{
				item = map.search(i);
				Assert::IsTrue(i == item.getKey(), L"Item is not found after insertion");
			}
		}

		TEST_METHOD(LPMapRemovalTest)
		{
			LPMap<HashFun> map(40);

			Item item;

			fillMapUppers(map);

			int count = map.getCount();
			Assert::IsTrue(count == 26, L"Count is not 26 after 26 insertions");

			//remove each of the items
			for (int i = 65; i < 91; ++i)
			{
				map.remove(i);
				--count;
				Assert::IsTrue(map.getCount() == count, L"Count is not updated after removal");
			}

			for (int i = 65; i < 91; ++i)
			{
				item = map.search(i);
				Assert::IsTrue(item.getKey() == '#', L"Found a key after removing it");
			}
		}

		TEST_METHOD(LPMapCopyMethodsTest)
		{
			LPMap<HashFun> map(40);
			fillMapUppers(map);

			LPMap<HashFun> map2(map);
			Assert::IsTrue(map2.getCount() == map.getCount(), L"Counts are not the same after copy construction");

			Item item;
			//search all the items in the new map
			for (int i = 65; i < 91; ++i)
			{
				item = map2.search(i);
				Assert::IsTrue(i == item.getKey(), L"Copy constructor is not working properly");
			}

			//remove 10 items
			for (int i = 65; i < 75; ++i)
				map2.remove(i);
			
			Assert::IsTrue(map2.getCount() == 16);

			//revert to map1 state
			map2 = map;

			//search all the items again
			for (int i = 65; i < 91; ++i)
			{
				item = map2.search(i);
				Assert::IsTrue(i == item.getKey(), L"Operator= is not working properly");
			}
		}
	};
}
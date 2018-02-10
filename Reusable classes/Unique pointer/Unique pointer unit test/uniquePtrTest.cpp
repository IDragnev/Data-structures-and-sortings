#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../Unique pointer/uniquePtr.h"
#include "../Unique pointer/Shapes.h"

namespace Uniquepointerunittest
{		
	uniquePtr<Shape> makeRectangle(int a, int b)
	{
		return uniquePtr<Shape>(new Rectangle(a, b));
	}

	uniquePtr<Shape> makeTriangle(int a, int b, int c)
	{
		return uniquePtr<Shape>(new Triangle(a, b, c));
	}

	TEST_CLASS(uniquePtrTest)
	{
	public:
		
		TEST_METHOD(DefaultInitialization)
		{
			uniquePtr<Shape> ptr;

			Assert::IsFalse(ptr, L"operator bool returns true after default construction");
			Assert::IsTrue(!ptr, L"operator!() returns false after default construction");
		}

		TEST_METHOD(MoveConstructor)
		{
			uniquePtr<Shape> ptr(makeRectangle(2, 4));

			Assert::IsFalse(!ptr, L"operator!() returns true after move construction");
			Assert::IsTrue(ptr, L"operator bool returns false after move construction");

			Assert::IsTrue(ptr->getParameter() == 6);
			Assert::IsTrue((*ptr).getParameter() == 6);

			uniquePtr<Shape> ptr2(std::move(ptr));

			Assert::IsTrue(!ptr, L"source is not null after move construction");
			Assert::IsFalse(ptr, L"source is not null after move construction");

			Assert::IsTrue(ptr2, L"Destination is null after move construction");
			Assert::IsFalse(!ptr2, L"Destination is null after move construction");

			Assert::IsTrue(ptr2->getParameter() == 6);

			uniquePtr<Shape> dest(uniquePtr<Shape>(nullptr));
			Assert::IsFalse(dest, L"dest is not null after move construction with null object");
			Assert::IsTrue(!dest, L"dest is not null after move construction with null object");
		}

		TEST_METHOD(MoveAssignment)
		{
			uniquePtr<Shape> ptr(makeTriangle(10, 20, 30));

			ptr = makeTriangle(1, 2, 3);

			Assert::IsTrue(ptr, L"ptr is null after move assignment from a non-null object");
			Assert::IsFalse(!ptr, L"ptr is null after move assignment from a non-null object");
			Assert::IsTrue(ptr->getParameter() == 6, L"move assignment is not working properly");
			Assert::IsTrue((*ptr).getParameter() == 6, L"move assignment is not working properly");

			ptr = uniquePtr<Shape>();
			Assert::IsFalse(ptr, L"source is not null after move assignment from a null rvalue");
			Assert::IsTrue(!ptr, L"source is not null after move assignment from a null rvalue");
		}
	};
}
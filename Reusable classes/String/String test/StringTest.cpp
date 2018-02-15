#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../String/String.h"

namespace Stringtest
{		
	TEST_CLASS(StringTest)
	{
	public:
		
		TEST_METHOD(ConstructionTests)
		{
			//default constructor
			String str;
			Assert::IsTrue(str.len() == 0, L"len is not 0 after default construction");
			Assert::IsTrue(strcmp(str, "") == 0, L"operator const char* is not working properly");

			//const char* constructor
			String str2("1234");
			Assert::IsTrue(str2.len() == 4, L"const char* constructor is not working properly");
			Assert::IsTrue(strcmp(str2, "1234") == 0, L"const char* constructor is not working properly");

			//char constructor
			String str3('c');
			Assert::IsTrue(strcmp(str3, "c") == 0, L"char constructor is not working properly");
		}

		TEST_METHOD(CopyConstructorTest)
		{
			//copy construction with a non-empty string
			String str("str1");
			String str2(str);

			Assert::IsTrue(strcmp(str2, "str1") == 0, L"Copy constructor is not working properly");
			Assert::IsTrue(strcmp(str2, str) == 0, L"Copy constructor is not working properly");

			//copy construction with an empty string
			String str3;
			String str4(str3);

			//assert that copy-constructed string is empty too
			Assert::IsTrue(str4.len() == 0, L"Copy constructor is not working properly with an empty argument");
			Assert::IsTrue(strcmp(str3, str4) == 0, L"Copy constructor is not working properly");
		}


		TEST_METHOD(CopyAssignmentTest)
		{
			//copy assignment with an empty string

			{
				//to a non-empty
				String str("non-empty");
				String str2;

				str = str2;

				Assert::IsTrue(str.len() == 0, L"Copy assignment with an empty string is not working properly");
				Assert::IsTrue(strcmp(str, "") == 0, L"Copy assignment with an empty string is not working properly");
				Assert::IsTrue(strcmp(str, str2) == 0, L"Copy assignment with an empty string is not working properly");
			}

			{
				//to an empty
				String str3;
				String str4;

				str3 = str4;

				Assert::IsTrue(str3.len() == 0, L"Copy assignment with an empty string is not working properly");
				Assert::IsTrue(strcmp(str3, "") == 0, L"Copy assignment with an empty string is not working properly");
				Assert::IsTrue(strcmp(str3, str4) == 0, L"Copy assignment with an empty string is not working properly");
			}

			//copy assignment with a non-empty string

			{
				//to a non-empty
				String str5("123");
				String str6("12345");

				str5 = str6;

				Assert::IsTrue(strcmp(str5, "12345") == 0, L"copy assignment with a non-empty string is not working properly");
				Assert::IsTrue(strcmp(str5, str6) == 0, L"copy assignment with a non-empty string is not working properly");
			}

			
			//to an empty
			String str7;
			String str8("12");

			str7 = str8;

			Assert::IsTrue(strcmp(str7, "12") == 0, L"copy assignment with a non-empty string is not working properly");
			Assert::IsTrue(strcmp(str7, str8) == 0, L"copy assignment with a non-empty string is not working properly");
		}


		TEST_METHOD(MoveConstructorTest)
		{
			{
				//from a non-empty prvalue
				String str(String("some value"));
				Assert::IsTrue(strcmp(str, "some value") == 0, L"Move constructor from a non-empty prvalue is not working properly");

				//from an empty prvalue
				String str2(String(nullptr));
				Assert::IsTrue(strcmp(str2, "") == 0, L"Move constructor from an empty prvalue is not working properly");
				Assert::IsTrue(str2.len() == 0, L"Move constructor from an empty prvalue is not working properly");
			}

			{
				//from a non-empty xvalue
				String str("str");
				String str2(std::move(str));

				//argument should be left emtpy
				Assert::IsTrue(strcmp(str2, "str") == 0, L"Move constructor from a non-empty xvalue is not working properly");
				Assert::IsTrue(str.len() == 0, L"Move constructor is not managing its argument properly");
				Assert::IsTrue(strcmp(str, "") == 0, L"Move constructor is not managing its argument properly");
			}

			//from an empty xvalue
			String str;
			String str2(std::move(str));

			//argument and str2 should be empty
			Assert::IsTrue(strcmp(str2, "") == 0, L"Move constructor from an empty xvalue is not working properly");
			Assert::IsTrue(str2.len() == 0, L"Move constructor from an empty xvalue is not working properly");
			Assert::IsTrue(str.len() == 0, L"Move constructor is not managing its argument properly");
			Assert::IsTrue(strcmp(str, "") == 0, L"Move constructor is not managing its argument properly");
		}


		TEST_METHOD(MoveAssignmentTest)
		{
			
			String str("some val");

			//from a non-empty prvalue
			str = String("1234");

			Assert::IsTrue(strcmp(str, "1234") == 0, L"Move assignment from a non-empty prvalue is not working properly");

			//from an empty prvalue
			str = String(nullptr);

			Assert::IsTrue(strcmp(str, "") == 0, L"Move assignment from an empty prvalue is not working properly");
			Assert::IsTrue(str.len() == 0, L"Move assignment from an empty prvalue is not working properly");


			//from a non-empty xvalue
			String str2("some val");

			str = std::move(str2);

			//str2 must be left empty
			Assert::IsTrue(strcmp(str, "some val") == 0, L"Move assignment from a non-empty xvalue is not working properly");
			Assert::IsTrue(strcmp(str2, "") == 0, L"Move assignment does not \'null\' its argument");
			Assert::IsTrue(str2.len() == 0, L"Move assignment does not \'null\' its argument");

			//from an empty xvalue
			str = std::move(str2);

			Assert::IsTrue(strcmp(str, "") == 0, L"Move assignment from an empty xvalue is not working properly");
			Assert::IsTrue(str.len() == 0, L"Move assignment from an empty xvalue is not working properly");
		}

		TEST_METHOD(AppendingStringTest)
		{
			//to an emtpy string...
			String str;

			//appending an empty (null) string
			str += String(nullptr);
			Assert::IsTrue(strcmp(str, "") == 0, L"appending to an empty string fails");
			
			//appending an empty string
			str += "";
			Assert::IsTrue(strcmp(str, "") == 0, L"appending to an empty string fails");

			//appending a non-empty string
			str += "1234";
			Assert::IsTrue(strcmp(str, "1234") == 0, L"appending to an empty string fails");


			//to a non-empty string...

			//appending an empty (null) string
			str += String(nullptr);
			Assert::IsTrue(strcmp(str, "1234") == 0, L"appending to a non-emtpy string fails");

			//appending an empty string
			str += "";
			Assert::IsTrue(strcmp(str, "1234") == 0, L"appending to a non-emtpy string fails");

			//appending a non-empty string
			str += "5678";
			Assert::IsTrue(strcmp(str, "12345678") == 0, L"appending to a non-emtpy string fails");
		}

		TEST_METHOD(AppendingCharTest)
		{
			//to an emtpy string
			String str;

			str += 'c';
			Assert::IsTrue(strcmp(str, "c") == 0, L"appending a char to an empty string fails");

			//to a non-empty string
			str += 'd';
			Assert::IsTrue(strcmp(str, "cd") == 0, L"appending a char to an non-empty string fails");
		}
	};
}
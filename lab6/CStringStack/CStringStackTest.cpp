#include "stdafx.h"
#include "CStringStack.h"

using namespace std;

bool StackEquality(CStringStack strStackOne, CStringStack strStackTwo)
{
	if (strStackOne.Size() != strStackTwo.Size())
	{
		return false;
	}

	string valOne, valTwo;
	while (strStackOne.Size() != 0)
	{
		valOne = strStackOne.Top();
		valTwo = strStackTwo.Top();
		strStackOne.Pop();
		strStackTwo.Pop();
		if (valOne != valTwo)
		{
			return false;
		}
	}
	return true;
}

TEST_CASE("CStringStack constructors")
{
	cout << "CStringStack constructors\n";

	cout << "--empty stack\n";
	{
		CStringStack strStackOne;
		REQUIRE(strStackOne.Size() == 0);

		CStringStack strStackTwo({});
		REQUIRE(strStackTwo.Size() == 0);

		CStringStack strStackThree(strStackTwo);
		REQUIRE(strStackThree.Size() == 0);

		CStringStack strStackFour(CStringStack({}));
		REQUIRE(strStackFour.Size() == 0);
	}

	cout << "--initial list\n";
	{
		CStringStack strStack({"a", "b", "c"});
		REQUIRE(strStack.Size() == 3);
		REQUIRE(strStack.Top() == "c");
		strStack.Pop();
		REQUIRE(strStack.Top() == "b");
		REQUIRE(strStack.Size() == 2);
		strStack.Pop();
		REQUIRE(strStack.Top() == "a");
		REQUIRE(strStack.Size() == 1);
		strStack.Pop();
		REQUIRE(strStack.Size() == 0);
	}

	cout << "--copy constructor\n";
	{
		CStringStack strStackOne({ "a", "b", "c" });
		CStringStack strStackTwo(strStackOne);
		REQUIRE(StackEquality(strStackOne, strStackTwo));
	}

	cout << "--move constructor\n";
	{
		CStringStack strStack(CStringStack({"a", "b", "c"}));
		REQUIRE(StackEquality(strStack, CStringStack({ "a", "b", "c" })));
	}
}

TEST_CASE("operator =")
{
	cout << "operator =\n";
	
	cout << "--copy operator\n";
	{
		CStringStack strStackOne({ "a", "b", "c" });
		CStringStack strStackTwo({ "ba", "bb", "cc", "ac" });
		CStringStack strStackThree({"ba"});


		strStackOne = strStackTwo;
		REQUIRE(StackEquality(strStackOne, strStackTwo));

		strStackOne = strStackThree;
		REQUIRE(StackEquality(strStackOne, strStackThree));

		strStackOne = CStringStack();
		REQUIRE(StackEquality(strStackOne, CStringStack()));
	}

	cout << "--move operator\n";
	{
		CStringStack strStack({ "a", "b", "c" });

		strStack = CStringStack({ "ba", "bb", "cc", "ac" });
		REQUIRE(StackEquality(strStack, CStringStack({ "ba", "bb", "cc", "ac" })));

		strStack = CStringStack({});
		REQUIRE(StackEquality(strStack, CStringStack({})));
	}
}

TEST_CASE("methods Push, Top, Pop")
{
	cout << "methods Push, Top, Pop\n";
	
	cout << "--without exceptions\n";
	{
		CStringStack strStack({ "a", "b", "c" });
		strStack.Push("abc");
		REQUIRE(strStack.Top() == "abc");
		REQUIRE(strStack.Size() == 4);
		strStack.Pop();
		REQUIRE(strStack.Top() == "c");
		REQUIRE(strStack.Size() == 3);
	}
	
	cout << "--with exceptions\n";
	{
		CStringStack strStack = {};
		try
		{
			auto value = strStack.Top();
			REQUIRE("a" == "b");
		}
		catch (std::underflow_error e)
		{
			REQUIRE(e.what() == string("Stack is empty. Top is not available"));
		}

		try
		{
			strStack.Pop();
			REQUIRE("a" == "b");
		}
		catch (std::underflow_error e)
		{
			REQUIRE(e.what() == string("Stack is empty. Pop is not available"));
		}
	}
}

TEST_CASE("method Clear")
{
	cout << "method Clear\n";

	CStringStack strStack({ "a", "b", "c" });
	strStack.Clear();
	REQUIRE(StackEquality(strStack, CStringStack()));
	strStack.Clear();
	REQUIRE(StackEquality(strStack, CStringStack()));
}

TEST_CASE("method Size")
{
	cout << "method Size\n";

	CStringStack strStack({ "a", "b", "c" });
	REQUIRE(strStack.Size() == 3);
	strStack.Push("a");
	REQUIRE(strStack.Size() == 4);
	strStack.Push("a");
	REQUIRE(strStack.Size() == 5);
	strStack.Clear();
	REQUIRE(strStack.Size() == 0);
}
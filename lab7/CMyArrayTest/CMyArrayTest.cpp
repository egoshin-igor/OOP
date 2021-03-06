#include "stdafx.h"
#include "../CMyArray/CMyArray.h"
#include <sstream>

using namespace std;

template <typename T>
string GetStringFromArr(CMyArray<T>& arr);

TEST_CASE("Constrcuctors test")
{
	cout << "Constructors\n";

	CMyArray<int> intArr{ 1, 2, 3, 4 };
	cout << "--initial list\n";
	{
		REQUIRE(GetStringFromArr(intArr) == string("1 2 3 4"));
		REQUIRE(intArr.Size() == 4);
	}

	cout << "--initial with other arr\n";
	{
		CMyArray<int> intArrTwo(intArr);
		REQUIRE(GetStringFromArr(intArrTwo) == string("1 2 3 4"));
		REQUIRE(intArrTwo.Size() == 4);
	}

	cout << "--empty arr\n";
	{
		CMyArray<int> intArrTwo;
		REQUIRE(GetStringFromArr(intArrTwo) == string(""));
		REQUIRE(intArrTwo.Size() == 0);
	}
}

TEST_CASE("compare operators")
{
	cout << "compare operators\n";
	{
		CMyArray<int> intArr{ 1, 2, 3, 4 };
		CMyArray<int> intArrTwo{ 1, 2, 3 };

		cout << "--operator !=\n";
		REQUIRE(intArr != intArrTwo);
		intArrTwo.PushBack(4);

		cout << "--operator ==\n";
		REQUIRE(intArr == intArrTwo);
	}
}

TEST_CASE("operator []")
{
	cout << "operator []\n";
	{
		CMyArray<int> intArr{ 1, 2, 3, 4 };

		cout << "--reading\\writing\n";
		{
			intArr[2] = 1;
			REQUIRE(intArr[2] == 1);
		}

		cout << "--errors\n";
		{
			try
			{
				intArr[-1] = 1;
				REQUIRE(intArr[1] == 8);
			}
			catch (invalid_argument e)
			{
				REQUIRE(string("index is out of range") == e.what());
			}

			try
			{
				intArr[4] = 1;
				REQUIRE(intArr[1] == 8);
			}
			catch (invalid_argument e)
			{
				REQUIRE(string("index is out of range") == e.what());
			}
		}
	}
}

TEST_CASE("method resize")
{
	cout << "method resize\n";
	{
		CMyArray<int> intArr{ 1, 2, 3, 4 };
		intArr.Resize(3);
		REQUIRE(intArr.Size() == 3);
		REQUIRE(intArr == CMyArray<int>{1, 2, 3});
		intArr.Resize(6);
		REQUIRE(intArr.Size() == 6);
		REQUIRE(intArr == CMyArray<int>{1, 2, 3, 0, 0, 0});
	}
}

TEST_CASE("method clear")
{
	cout << "method clear\n";
	{
		CMyArray<int> intArr{ 1, 2, 3, 4 };
		intArr.Clear();
		REQUIRE(intArr.Size() == 0);
		REQUIRE(intArr == CMyArray<int>{});
		intArr.Clear();
		REQUIRE(intArr.Size() == 0);
		REQUIRE(intArr == CMyArray<int>{});
	}
}

TEST_CASE("operator =")
{
	cout << "operator =\n";
	{
		CMyArray<int> intArr{ 1, 2, 3, 4 };
		intArr = CMyArray<int>{ 1, 0, 3 };
		REQUIRE(intArr.Size() == 3);
		REQUIRE(intArr == CMyArray<int>{1, 0, 3});
		intArr = CMyArray<int>{};
		REQUIRE(intArr.Size() == 0);
		REQUIRE(intArr == CMyArray<int>{});
	}
}

TEST_CASE("some different types")
{
	cout << "some different types\n";
	{
		cout << "--int\n";
		{
			CMyArray<int> intArr{ 1, 2, 3, 4 };
			REQUIRE(intArr == CMyArray<int>({ 1, 2, 3, 4 }));
		}
		
		cout << "--string\n";
		{
			CMyArray<string> strArr{ "avc", "as" };
			REQUIRE(strArr == CMyArray<string>({ "avc", "as" }));
		}

		cout << "--bool\n";
		{
			CMyArray<bool> boolArr{ false, true };
			REQUIRE(boolArr == CMyArray<bool>({ false, true }));
		}
	}
}


TEST_CASE("iterators")
{
	cout << "iterators\n";
	{
		CMyArray<int> intArr{ 1, 2, 3, 8 };
		cout << "--begin()\n";
		{
			auto it = intArr.begin();
			REQUIRE(*it == 1);
		}
		cout << "--end()\n";
		{
			auto it = intArr.end();
			REQUIRE(*--it == 8);
		}
		cout << "--begin()\n";
		{
			auto it = intArr.begin();
			REQUIRE(*it == 1);
		}
		cout << "--rbegin()\n";
		{
			auto it = intArr.rbegin();
			REQUIRE(*it == 8);
		}
		cout << "--rend()\n";
		{
			auto it = intArr.rend();
			REQUIRE(*--it == 1);
		}

		cout << "--different methods()\n";
		{
			auto it = intArr.begin();
			cout << "----operator[]\n";
			REQUIRE(it[2] == 3);
			cout << "----operator++\n";
			it++;
			REQUIRE(*it == 2);
			++it;
			REQUIRE(*it == 3);
			cout << "----operator--\n";
			it--;
			REQUIRE(*it == 2);
			--it;
			REQUIRE(*it == 1);
			cout << "----operator+\n";
			it = it + 2;
			REQUIRE(*it == 3);
			cout << "----operator-\n";
			it = it - 2;
			REQUIRE(*it == 1);
		}
	}
}

TEST_CASE("some tests with string")
{
	cout << "some tests with string\n";
	{
		cout << "--small string\n";
		{
			CMyArray<string> strArr{ "avcsadasdasdasds", "as" };
			REQUIRE(strArr == CMyArray<string>({ "avcsadasdasdasds", "as" }));
			REQUIRE(strArr.Size() == 2);
		}
		
		cout << "many strings\n";
		{
			CMyArray<string> strArr{ "avc", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as" };
			REQUIRE(strArr == CMyArray<string>({ "avc", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as", "as" }));
			REQUIRE(strArr.Size() == 470);
		}

		cout << "string\n";
		{
			CMyArray<bool> boolArr{ false, true };
			REQUIRE(boolArr == CMyArray<bool>({ false, true }));
		}
	}
}



template <typename T>
string GetStringFromArr(CMyArray<T>& arr)
{
	ostringstream ostream;
	auto arrSize = arr.Size();
	for (size_t i = 0; i < arrSize; ++i)
	{
		ostream << to_string(arr[i]);
		if (i != arrSize - 1)
		{
			ostream << ' ';
		}
	}
	return ostream.str();
}
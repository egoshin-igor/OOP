#include "stdafx.h"
#include "CMyString.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

TEST_CASE("A string can be created with different parametrs")
{
	cout << "A string can be created with different parametrs\n";

	cout << "--string with constructor with empty params\n";
	{
		CMyString str;
		REQUIRE(str.GetLength() == 0);
		REQUIRE(str.GetStringData() == "");
	}

	cout << "--constructor initializing string with string data\n";
	{
		CMyString str("abc");
		REQUIRE(str.GetLength() == 3);
		REQUIRE(str.GetStringData() == string("abc"));
	}

	cout << "--constructor initializing string with string data with some length\n";
	{
		CMyString str("abc", 2);
		REQUIRE(str.GetLength() == 2);
		REQUIRE(str.GetStringData() == string("ab"));
	}

	cout << "--constructor initializing string with stl string data\n";
	{
		CMyString str(string("abc"));
		REQUIRE(str.GetLength() == 3);
		REQUIRE(str.GetStringData() == string("abc"));
	}

	cout << "--constructor initializing long string with stl string data\n";
	{
		CMyString str(string("abcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabc"));
		REQUIRE(str.GetLength() == 480);
		REQUIRE(str.GetStringData() == string("abcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabcabc"));
	}

	cout << "--copy constructor with CMyString data\b\n";
	{
		CMyString str1("abc");
		CMyString str2(str1);
		REQUIRE(str2.GetLength() == str1.GetLength());
		REQUIRE(str1.GetStringData() == string("abc"));
	}

	cout << "--relocating constructor with CMyString data\n";
	{
		CMyString str(CMyString("abc"));
		REQUIRE(str.GetLength() == 3);
		REQUIRE(str.GetStringData() == string("abc"));
	}

	cout << "--constructor initializing string with \\0 chars in middle\n";
	{
		CMyString str("a\0\0b", 4);
		REQUIRE(str.GetLength() == 4);
		std::ostringstream oStream;

		for (size_t i = 0; i < str.GetLength(); ++i)
		{
			if (str[i] == '\0')
			{
				oStream << "\\0";
			}
			else
			{
				oStream << str[i];
			}
		}
		REQUIRE(oStream.str() == "a\\0\\0b");
		cout << "----string with double \\0 in middle input: a\\0\\0b\n";
		cout << "----string with double \\0 in middle result: " << oStream.str() << '\n';
	}
}

TEST_CASE("A string can be cleared")
{
	cout << "A string can be cleared\n";
	CMyString str1("abc");
	CMyString str2;
	str1.Clear();
	str2.Clear();
	REQUIRE(str1.GetLength() == 0);
	REQUIRE(str1.GetStringData() == string(""));
	REQUIRE(str2.GetLength() == 0);
	REQUIRE(str2.GetStringData() == string(""));
}

TEST_CASE("I can get substring from string")
{
	cout << "Getting substring from string\n";
	CMyString str("abcde");
	REQUIRE(str.SubString(0, 2).GetStringData() == string("ab"));
	REQUIRE(str.SubString(1, 2).GetStringData() == string("bc"));
	REQUIRE(str.SubString(2, 1).GetStringData() == string("c"));
	REQUIRE(str.SubString(2, 0).GetStringData() == string(""));
	REQUIRE(str.SubString(5, 1).GetStringData() == string(""));
	REQUIRE(str.SubString(4, 1).GetStringData() == string("e"));
	REQUIRE(str.SubString(2).GetStringData() == string("cde"));
}

TEST_CASE("Checking operator =")
{
	cout << "Checking operator =\n";
	CMyString str("abcde");
	CMyString str2("abc");
	str = str2;
	REQUIRE((str.GetStringData() == string("abc") && str.GetLength() == 3));
	str = "cabeac";
	REQUIRE((str.GetStringData() == string("cabeac") && str.GetLength() == 6));
	str = str;
	REQUIRE((str.GetStringData() == string("cabeac") && str.GetLength() == 6));
}

TEST_CASE("Checking operator +=")
{
	cout << "Checking operator +=\n";
	CMyString str("abcde");
	CMyString str2("abc");
	str += str2;
	REQUIRE((str.GetStringData() == string("abcdeabc") && str.GetLength() == 8));
	str += "av";
	REQUIRE((str.GetStringData() == string("abcdeabcav") && str.GetLength() == 10));
}

TEST_CASE("Checking operator ==")
{
	cout << "Checking operator ==\n";
	CMyString str("abcde");
	CMyString str2("abc");
	CMyString str3("abcde");
	REQUIRE(!(str == str2));
	REQUIRE(str == str3);
	REQUIRE(str == str);
	REQUIRE(str == "abcde");
}

TEST_CASE("Checking operator !=")
{
	cout << "Checking operator !=\n";
	CMyString str("abcde");
	CMyString str2("abc");
	CMyString str3("abcde");
	REQUIRE(str != str2);
	REQUIRE(!(str != str3));
	REQUIRE(!(str != str));
	REQUIRE(str != "abcdef");
}

TEST_CASE("Checking operator +")
{
	cout << "Checking operator +\n";
	CMyString str1("abc");

	cout << "--CMyString + CMyString\n";
	{
		CMyString str2("abd");
		REQUIRE((str1 + str2) == "abcabd");
		REQUIRE((str1 + str2).GetLength() == 6);
	}

	cout << "--string + CMyString\n";
	{
		string str2("abd");
		REQUIRE((str2 + str1) == "abdabc");
		REQUIRE((str2 + str1).GetLength() == 6);
	}

	cout << "--char* + CMyString\n";
	{
		REQUIRE(("abd" + str1) == "abdabc");
		REQUIRE(("abd" + str1).GetLength() == 6);
	}
}

TEST_CASE("Checking operators < > <= >=")
{
	cout << "Checking operators < > <= >=\n";
	CMyString str1("abc");
	CMyString str2("abcd");
	CMyString str3("abd");

	cout << "--operator <\n";
	{
		REQUIRE(str1 < str2);
		REQUIRE(str1 < str3);
	}

	cout << "--operator >\n";
	{
		REQUIRE(str2 > str1);
		REQUIRE(str3 > str1);
	}

	cout << "--operator <=\n";
	{

		REQUIRE(str1 <= str2);
		REQUIRE(str1 <= str3);
		REQUIRE(str1 <= str1);
	}

	cout << "--operator >=\n";
	{
		REQUIRE(str2 >= str1);
		REQUIRE(str3 >= str1);
		REQUIRE(str3 >= str3);
	}
}

TEST_CASE("Checking operator []")
{
	cout << "Checking operator []\n";

	CMyString str("abcde");

	cout << "--Checking operator [] for reading\n";
	{
		REQUIRE(str[0] == 'a');
		REQUIRE(str[2] == 'c');
		REQUIRE(str[4] == 'e');
	}

	cout << "--Checking operator [] for writing\n";
	{
		str[0] = 'f';
		str[2] = 'f';
		str[4] = 'f';
		REQUIRE(str == "fbfdf");
	}

	cout << "--Checking operator [] for errors\n";
	{
		try
		{
			str[20] == 'a';
		}
		catch (out_of_range& e)
		{
			REQUIRE(e.what() == string("index is out of range"));
		}

		try
		{
			str[20] = 'a';
		}
		catch (out_of_range& e)
		{
			REQUIRE(e.what() == string("index is out of range"));
		}

		try
		{
			str[-5] == 'a';
		}
		catch (out_of_range& e)
		{
			REQUIRE(e.what() == string("index is out of range"));
		}

		try
		{
			str[-5] = 'a';
		}
		catch (out_of_range& e)
		{
			REQUIRE(e.what() == string("index is out of range"));
		}
	}
}

TEST_CASE("Checking for operators << >>")
{
	cout << "Checking for operators << >>\n";

	cout << "--Checking for operator <<\n";
	{
		CMyString str3("cde");
		std::istringstream iStream("de");
		iStream >> str3;
		REQUIRE(str3 == "de");
	}

	cout << "--Checking for operator >>\n";
	{
		CMyString str1("abc");
		CMyString str2("");
		std::ostringstream oStream;

		oStream << str1 << str2;
		REQUIRE(oStream.str() == "abc");
	}

	cout << "--Checking for errors \n";
	{
		CMyString str1("abc");
		std::ostringstream oStream;

		std::istringstream iStream("de");
		iStream.setstate(ios_base::failbit);
		iStream >> str1;
		REQUIRE(str1 == "abc");
	}
}
#include "stdafx.h"
#include "../Calculator/Calculator.h"

using namespace std;

TEST_CASE("Calulator test")
{
	const double E = 0.0001;

	Calculator calculator;

	SECTION("Проверка на правильность идентификатора")
	{
		try
		{
			calculator.DeclareVariable("1A");
		}
		catch (const string& error)
		{
			CHECK("First char of this identifier cant be a digit" == error);
		}

		try
		{
			calculator.DeclareVariable("");
		}
		catch (const string& error)
		{
			CHECK("This Identifier cant be empty" == error);
		}

		try
		{
			calculator.DeclareVariable("Abc#");
		}
		catch (const string& error)
		{
			CHECK("This Identifier has to only digits, latin chars and char \'_\'" == error);
		}
	}

	SECTION("Проверка на переобъявление идентификатора")
	{
		try
		{
			calculator.DeclareVariable("Abc");
			calculator.DeclareVariable("Abc");
		}
		catch (const string& error)
		{
			CHECK("This identifier already declared" == error);
		}
	}

	SECTION("Проверка на инициализацию переменной")
	{
		try
		{
			calculator.LetVariable("Abc", "Cab");
		}
		catch (const string& error)
		{
			CHECK("Value identifier not declared yet" == error);
		}

		try
		{
			calculator.DeclareVariable("Cab");
			calculator.LetVariable("Abc", "Cab");
		}
		catch (const string& error)
		{
			CHECK("The Value of second identifier is NAN" == error);
		}

		try
		{
			calculator.LetVariable("Cab", 5);
			calculator.LetVariable("Abc", "Cab");
		}
		catch (const string&)
		{
			CHECK("This check will not work");
		}
	}

	SECTION("Проверка ошибок при инизциализации функций")
	{
		try
		{
			calculator.DeclareFunction("Qwe", "", "", "");
		}
		catch (const string& error)
		{
			CHECK("The second identifier is empty" == error);
		}

		try
		{
			calculator.DeclareFunction("Qwe", "Abc", "", "");
		}
		catch (const string& error)
		{
			CHECK("The second identifier not declared yet" == error);
		}

		try
		{
			calculator.DeclareVariable("Abc");
			calculator.DeclareFunction("Qwe", "Abc", "", "");
		}
		catch (const string&)
		{
			CHECK("This check will not work");
		}

		try
		{
			calculator.DeclareFunction("Qwer", "Abc", "Cad", "");
		}
		catch (const string& error)
		{
			CHECK("The third identifier not declared yet" == error);
		}

		try
		{
			calculator.DeclareVariable("Cad");
			calculator.DeclareFunction("Qwer", "Abc", "Cad", "");
		}
		catch (const string& error)
		{
			CHECK("Wrong operation" == error);
		}

		try
		{
			calculator.DeclareFunction("Qwer", "Abc", "Cad", "+");
		}
		catch (const string&)
		{
			CHECK("This check will not work");
		}
	}

	SECTION("Проверка на получение значения переменных")
	{
		try
		{
			double d = calculator.GetIdentifierValue("Aq");
		}
		catch (const string& error)
		{
			CHECK("Identifier is not exist" == error);
		}

		calculator.DeclareVariable("Aq");
		double d = calculator.GetIdentifierValue("Aq");
		CHECK(isnan(d) == true);

		calculator.LetVariable("Aq", 8);
		d = calculator.GetIdentifierValue("Aq");
		CHECK(abs(d - 8) < E);
	}
}
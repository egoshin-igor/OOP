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
			calculator.DeclareVariable("var1");
		}
		catch (invalid_argument& error)
		{
			CHECK(static_cast<const string&>("First char of this identifier cant be a digit") == error.what());
		}

		try
		{
			calculator.DeclareVariable("");
		}
		catch (invalid_argument& error)
		{
			CHECK(static_cast<const string&>("This Identifier cant be empty") == error.what());
		}

		try
		{
			calculator.DeclareVariable("Var#");
		}
		catch (invalid_argument& error)
		{
			CHECK(static_cast<const string&>("This Identifier has to only digits, latin chars and char \'_\'") == error.what());
		}
	}

	SECTION("Проверка на переобъявление идентификатора")
	{
		try
		{
			calculator.DeclareVariable("Abc");
			calculator.DeclareVariable("Abc");
		}
		catch (invalid_argument& error)
		{
			CHECK(static_cast<const string&>("This identifier already declared") == error.what());
		}
	}

	SECTION("Проверка на инициализацию переменной")
	{
		try
		{
			calculator.LetVariable("var1", "var2");
		}
		catch (invalid_argument& error)
		{
			CHECK(static_cast<const string&>("Value identifier not declared yet") == error.what());
		}

		try
		{
			calculator.DeclareVariable("var2");
			calculator.LetVariable("var1", "var2");
		}
		catch (invalid_argument& error)
		{
			CHECK(static_cast<const string&>("The Value of second identifier is NAN") == error.what());
		}

		try
		{
			calculator.LetVariable("var2", 5);
			calculator.LetVariable("var1", "var2"); 
		}
		catch (invalid_argument& error)
		{
			CHECK("This check will not work" == error.what());
		}
	}

	SECTION("Проверка ошибок при инизциализации функций")
	{
		try
		{
			calculator.DeclareFunction("Fn1", "", "", "");
		}
		catch (invalid_argument& error)
		{
			CHECK(static_cast<const string&>("The second identifier is empty") == error.what());
		}

		try
		{
			calculator.DeclareFunction("Fn1", "var1", "", "");
		}
		catch (invalid_argument& error)
		{
			CHECK(static_cast<const string&>("The second identifier not declared yet") == error.what());
		}

		try
		{
			calculator.DeclareVariable("var1");
			calculator.DeclareFunction("Fn1", "var1");
		}
		catch (invalid_argument& error)
		{
			CHECK(static_cast<const string&>("This check will not work") == error.what());
		}

		try
		{
			calculator.DeclareFunction("Fn2", "var1", "var2", "");
		}
		catch (invalid_argument& error)
		{
			CHECK(static_cast<const string&>("The third identifier not declared yet") == error.what());
		}

		try
		{
			calculator.DeclareVariable("var2");
			calculator.DeclareFunction("Fn2", "var1", "var2", "");
		}
		catch (invalid_argument& error)
		{
			CHECK(static_cast<const string&>("Wrong operation") == error.what());
		}

		try
		{
			calculator.DeclareFunction("Fn2", "var1", "var2", "+");
		}
		catch (invalid_argument& error)
		{
			CHECK("This check will not work" == error.what());
		}
	}

	SECTION("Проверка на получение значения переменных")
	{
		try
		{
			double d = calculator.GetIdentifierValue("Aq");
		}
		catch (invalid_argument& error)
		{
			CHECK(static_cast<const string&>("Identifier is not exist") == error.what());
		}

		calculator.DeclareVariable("var1");
		double d = calculator.GetIdentifierValue("var1");
		CHECK(isnan(d) == true);

		calculator.LetVariable("var1", 8);
		d = calculator.GetIdentifierValue("var1");
		CHECK(abs(d - 8) < E);

		calculator.LetVariable("var2", "var1");
		calculator.LetVariable("var1", 11);
		d = calculator.GetIdentifierValue("var1");
		CHECK(abs(d - 11) < E);
		d = calculator.GetIdentifierValue("var2");
		CHECK(abs(d - 8) < E);
	}

	SECTION("Проверка на получение значения функций")
	{
		calculator.LetVariable("var1", 8);
		calculator.LetVariable("var2", "var1");
		calculator.DeclareFunction("Fn", "var1");
		calculator.LetVariable("var1", 9);
		double d = calculator.GetIdentifierValue("var2");
		CHECK(abs(d - 8) < E);
		d = calculator.GetIdentifierValue("Fn");
		CHECK(abs(d - 9) < E);

		calculator.DeclareFunction("Var1PlusVar2", "var1", "var2", "+");
		d = calculator.GetIdentifierValue("Var1PlusVar2");
		CHECK(abs(d - 17) < E);

		calculator.LetVariable("var3", 10);
		calculator.DeclareFunction("Var1PlusVar2DivVar3", "Var1PlusVar2", "var3", "/");
		d = calculator.GetIdentifierValue("Var1PlusVar2DivVar3");
		CHECK(abs(d - 1.7) < E);

		calculator.DeclareVariable("var4");
		calculator.DeclareFunction("NanFn", "var4");
		d = calculator.GetIdentifierValue("NanFn");
		CHECK(isnan(d) == true);

		calculator.DeclareFunction("Var1PlusVar2DivVar4", "Var1PlusVar2", "var4", "/");
		d = calculator.GetIdentifierValue("Var1PlusVar2DivVar4");
		CHECK(isnan(d) == true);
	}

	SECTION("Проверка на получение списка функций и переменных")
	{
		calculator.LetVariable("var1", 8);
		calculator.LetVariable("var2", 3);
		calculator.LetVariable("var3", 10);
		calculator.LetVariable("var4", "var2");

		calculator.DeclareFunction("Fn", "var1");
		calculator.DeclareFunction("Var1PlusVar2", "var1", "var2", "+");
		calculator.DeclareFunction("Var1PlusVar2DivVar3", "Var1PlusVar2", "var3", "/");

		auto variables = calculator.GetVariablesValues();
		auto functions = calculator.GetFunctionsValues();

		for (auto variable : variables)
		{
			CHECK(calculator.GetIdentifierValue(variable.first) - variable.second < E);
		}
		for (auto function : functions)
		{
			CHECK(calculator.GetIdentifierValue(function.first) - function.second < E);
		}
	}
}
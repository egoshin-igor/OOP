#include "stdafx.h"
#include "Calculator.h"

using namespace std;

const double E = 0.0001;

void Let(Calculator& calculator);
void Fn(Calculator& calculator);
void Var(Calculator& calculator);
void Print(ostream& output, Calculator& calculator);
void PrintVariables(ostream& output, Calculator& calculator);
void PrintFunctions(ostream& output, Calculator& calculator);
void Help();
bool StringToDouble(const string& str, double& number);

int main()
{
	Calculator calculator;
	string instruction;
	bool exit = false;

	Help();

	while (!exit)
	{
		cin >> instruction;
		exit = instruction != "exit" ? false : true;
		if (!exit)
		{
			try
			{
				if (instruction == "var")
				{
					Var(calculator);
				}
				else if (instruction == "let")
				{
					Let(calculator);
				}
				else if (instruction == "fn")
				{
					Fn(calculator);
				}
				else if (instruction == "print")
				{
					Print(cout, calculator);
				}
				else if (instruction == "printvars")
				{
					PrintVariables(cout, calculator);
				}
				else if (instruction == "printfns")
				{
					PrintFunctions(cout, calculator);
				}
				else if (instruction == "help")
				{
					Help();
				}
			}
			catch (invalid_argument& error)
			{
				cout << error.what() << '\n';
			}
			catch (...)
			{
				cout << "Unexception error, Ups.\n";
			}
		}
	}
	return 0;
}

void Help()
{
	cout << "Existing commands:\n";
	cout << "command \"var <identifier>\"\n";
	cout << "command \"let <identifier1>=<double>\"\n";
	cout << "command \"let <identifier1>=<identifier2>\"\n";
	cout << "command \"fn <identifier1>=<identifier2>\"\n";
	cout << "command \"fn <identifier1>=<identifier2><operation><identifier3>\"\n";
	cout << "command \"print <identifier>\"\n";
	cout << "command \"printvars\"\n";
	cout << "command \"printfns\"\n";
	cout << "command \"help\"\n";
	cout << "command \"exit\"\n";
}

void Var(Calculator& calculator)
{
	string commandValue;
	cin >> commandValue;
	calculator.DeclareVariable(commandValue);
}

void Let(Calculator& calculator)
{
	string commandValue;
	cin >> commandValue;

	auto equalPos = commandValue.find("=");
	if (equalPos == string::npos || equalPos == commandValue.size() - 1)
	{
		throw invalid_argument("Incorrect command. Write Help for getting correct commands");
	}

	auto value = commandValue.substr(equalPos + 1, string::npos);
	double number;
	if (StringToDouble(value, number))
	{
		calculator.LetVariable(commandValue.substr(0, equalPos), number);
	}
	else
	{
		calculator.LetVariable(commandValue.substr(0, equalPos), value);
	}
}

bool StringToDouble(const string& str, double& number)
{
	bool error;
	char* pLastChar = NULL;
	auto charStr = str.c_str();
	number = strtod(charStr, &pLastChar);
	error = !((*(charStr) == '\0') || (*pLastChar != '\0'));
	if (abs(number - HUGE_VAL) < E)
	{
		error = false;
	}
	return error;
}

void Fn(Calculator& calculator)
{
	string commandValue;
	cin >> commandValue;

	auto equalPos = commandValue.find("=");
	if (equalPos == string::npos || equalPos == commandValue.size() - 1)
	{
		throw invalid_argument("Incorrect command. Write Help for getting correct commands");
	}

	auto operationPos = commandValue.find_first_of("+-/*", equalPos);
	auto identifierOne = commandValue.substr(0, equalPos);
	auto identifierTwo = commandValue.substr(equalPos + 1, operationPos - equalPos - 1);
	if (operationPos == string::npos)
	{
		calculator.DeclareFunction(identifierOne, identifierTwo);
	}
	else
	{
		auto identifierThree = commandValue.substr(operationPos + 1, string::npos);
		calculator.DeclareFunction(identifierOne, identifierTwo, identifierThree, commandValue.substr(operationPos, 1));
	}
}

void Print(ostream& output, Calculator& calculator)
{
	string commandValue;
	cin >> commandValue;
	auto number = calculator.GetIdentifierValue(commandValue);
	if (!isnan(number))
	{
		output << round(number * 100) / 100 << '\n';
	}
	else
	{
		cout << "nan" << '\n';
	}
}

void PrintVariables(ostream& output, Calculator& calculator)
{
	auto variables = calculator.GetVariablesValues();
	for (auto variable : variables)
	{
		output << variable.first << ':';
		if (!isnan(variable.second))
		{
			output << round(variable.second * 100) / 100 << '\n';
		}
		else
		{
			output << "nan" << "\n";
		}
	}
}

void PrintFunctions(ostream& output, Calculator& calculator)
{
	auto functions = calculator.GetFunctionsValues();
	for (auto function : functions)
	{
		output << function.first << ':';
		if (!isnan(function.second))
		{
			output << round(function.second * 100) / 100 << '\n';
		}
		else
		{
			output << "nan" << "\n";
		}
	}
}
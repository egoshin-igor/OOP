#include "stdafx.h"
#include "Calculator.h"
#include <cctype>
#include <string>
#include <vector>

using namespace std;

void CheckIdentifier(const std::string identifier)
{
	if (identifier.empty())
	{
		throw invalid_argument("This Identifier cant be empty");
	}

	if (isdigit(identifier[0]))
	{
		throw invalid_argument("First char of this identifier cant be a digit");
	}

	for (size_t i = 1; i < identifier.size(); ++i)
	{
		if (!isalnum(identifier[i]) && identifier[i] != '_')
		{
			throw invalid_argument("This Identifier has to only digits, latin chars and char \'_\'");
		}
	}
}

void Calculator::DeclareVariable(const string& identifier)
{
	CheckIdentifier(identifier);

	if (m_variablesDictionary.find(identifier) != m_variablesDictionary.end() && m_functionsDictionary.find(identifier) == m_functionsDictionary.end())
	{
		throw invalid_argument("This identifier already declared");
	}

	m_variablesDictionary[identifier] = NAN;
}

void Calculator::LetVariable(const string& identifier, double value)
{
	if (m_variablesDictionary.find(identifier) == m_variablesDictionary.end())
	{
		DeclareVariable(identifier);
	}

	m_variablesDictionary[identifier] = value;
}

void Calculator::LetVariable(const string& identifier, const string& valueIdentifier)
{
	if (m_variablesDictionary.find(valueIdentifier) == m_variablesDictionary.end() && m_functionsDictionary.find(valueIdentifier) == m_functionsDictionary.end())
	{
		throw invalid_argument("Value identifier not declared yet");
	}

	if (m_variablesDictionary[valueIdentifier] == NAN)
	{
		throw invalid_argument("The Value of second identifier is NAN");
	}

	if (m_variablesDictionary.find(identifier) == m_variablesDictionary.end() && m_functionsDictionary.find(identifier) == m_functionsDictionary.end())
	{
		DeclareVariable(identifier);
	}
	
	m_variablesDictionary[identifier] = GetIdentifierValue(valueIdentifier);
}

void Calculator::DeclareFunction(const std::string& identifier, const std::string& valueIdentifierOne, const std::string& valueIdentifierTwo, const std::string& operation)
{
	CheckIdentifier(identifier);

	if (valueIdentifierOne.empty())
	{
		throw invalid_argument("The second identifier is empty");
	}

	//if (m_functionsDictionary.find(identifier) != m_functionsDictionary.end() || m_variablesDictionary.find(identifier) != m_variablesDictionary.end())
	//{
	//	throw invalid_argument("The first identifier already declared");
	//}

	if (m_functionsDictionary.find(valueIdentifierOne) == m_functionsDictionary.end() && m_variablesDictionary.find(valueIdentifierOne) == m_variablesDictionary.end())
	{
		throw invalid_argument("The second identifier not declared yet");
	}

	if (m_functionsDictionary.find(valueIdentifierTwo) == m_functionsDictionary.end() && m_variablesDictionary.find(valueIdentifierTwo) == m_variablesDictionary.end() &&
		!valueIdentifierTwo.empty())
	{
		throw invalid_argument("The third identifier not declared yet");
	}

	if (operation != "+" && operation != "-" && operation != "*" && operation != "/" && operation != "")
	{
		throw invalid_argument("Wrong operation");
	}

	vector<string> dictionaryValue(3);
	dictionaryValue[0] = valueIdentifierOne;
	dictionaryValue[1] = valueIdentifierTwo;
	dictionaryValue[2] = operation;
	m_functionsDictionary[identifier] = dictionaryValue;
}

double Calculator::GetIdentifierValue(const std::string& identifier)
{
	auto isVariable = m_variablesDictionary.find(identifier) != m_variablesDictionary.end();
	auto isFunction = m_functionsDictionary.find(identifier) != m_functionsDictionary.end();
	double result = 0;
	if (!isVariable && !isFunction)
	{
		throw invalid_argument("Identifier is not exist");
	}

	if (isVariable)
	{
		result =  m_variablesDictionary[identifier];
	}

	if (isFunction)
	{
		auto functionValue = m_functionsDictionary[identifier];
		double valueOne = 0;
		valueOne = GetIdentifierValue(functionValue[0]);
		if (functionValue[1] != "")
		{
			double valueTwo = 0;
			valueTwo = GetIdentifierValue(functionValue[1]);
			auto operation = functionValue[2];
			if (operation == "+")
			{
				result = valueOne + valueTwo;
			}
			else if (operation == "-")
			{
				result = valueOne - valueTwo;
			}
			else if (operation == "/")
			{
				result = valueOne / valueTwo;
			}
			else if (operation == "*")
			{
				result = valueOne * valueTwo;
			}
		}
		else
		{
			result = valueOne;
		}
	}
	return result;
}

map<std::string, double> Calculator::GetVariablesValues()
{
	map<std::string, double> variablesValues;
	for (auto variable : m_variablesDictionary)
	{
		variablesValues[variable.first] = variable.second;
	}
	return variablesValues;
}

map<std::string, double> Calculator::GetFunctionsValues()
{
	map<std::string, double> functionsValues;
	for (auto function : m_functionsDictionary)
	{
		functionsValues[function.first] = GetIdentifierValue(function.first);
	}
	return functionsValues;
}

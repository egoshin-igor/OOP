#pragma once
#include <string>
#include <map>
#include <vector>

class Calculator
{
public:
	void DeclareVariable(const std::string& identifier);
	void LetVariable(const std::string& identifier, double value);
	void LetVariable(const std::string& identifier, const std::string& valueIdentifier);
	void DeclareFunction(const std::string& identifier, const std::string& valueIdentifierOne, const std::string& valueIdentifierTwo = "", const std::string& operation = "");
	double GetIdentifierValue(const std::string& identifier);
	std::map<std::string, double> GetVariablesValues();
	std::map<std::string, double> GetFunctionsValues();
private:
	std::map<std::string, double> m_variablesDictionary;
	std::map<std::string, std::vector<std::string>> m_functionsDictionary;

};


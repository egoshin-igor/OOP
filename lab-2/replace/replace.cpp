#include "stdafx.h"

using namespace std;

const int WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE = 1;

const int REQUIRED_NUMBER_OF_ARGUMENTS = 3;

string FindAndReplace(string const& subject, string const& search, string const& replace);
string GetReplacedString(istream& input, string const& search, string const& replace);

int main(int argc, char* argv[])
{
	if (argc != REQUIRED_NUMBER_OF_ARGUMENTS)
	{
		cout << "Type only 2 arguments in this format:\n";
		cout << "replace.exe <search-string> <replace-string>\n";
		return WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE;
	}
	const string search = argv[1];
	const string replace = argv[2];
	string replacedString = GetReplacedString(cin, search, replace);
	cout << replacedString;
	return 0;
}

string FindAndReplace(string const& subject, string const& search, string const& replace)
{
	if (search == "")
	{
		return subject;
	}
	size_t lastIndex = 0;
	size_t newIndex;
	string tempString = "";
	while ((newIndex = subject.find(search, lastIndex)) != string::npos)
	{
		tempString.append(subject, lastIndex, newIndex - lastIndex);
		tempString += replace;
		lastIndex = newIndex + search.length();
	}
	tempString += subject.substr(lastIndex);
	return tempString;

}

string GetReplacedString(istream& input, string const& search, string const& replace)
{
	string subject;
	string result = "";
	while (getline(input, subject))
	{
		result += FindAndReplace(subject, search, replace) + '\n';
	}
	return result;
}



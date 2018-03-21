#include "stdafx.h"
#include <string>

using namespace std;

string FindAndReplace(std::string const& subject, string const& search, string const& replace)
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

string HtmlDecode(string const& html)
{

	vector<string> searchWords = { "&quot;", "&apos;", "&lt;", "&gt;", "&amp;" };
	vector<string> replacedWords = { "\"", "\'", "<", ">", "&" };
	string tempString = html;
	for (size_t i = 0; i < searchWords.size(); ++i)
	{
		tempString = FindAndReplace(tempString, searchWords[i], replacedWords[i]);
	}
	return tempString;

}
#include "stdafx.h"
#include "HtmlDecode.h"

using namespace std;

void DecodeProcess(istream& input, ostream& output);

int main()
{
	DecodeProcess(cin, cout);
	return 0;
}

void DecodeProcess(istream& input, ostream& output)
{
	string html;
	string result = "";
	while (getline(input, html))
	{
		result = HtmlDecode(html);
		output << result << '\n';
	}
}
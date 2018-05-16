#include "stdafx.h"
#include "UrlController.h"

using namespace std;

void UrlController::ShowUrlInfo(ostream& output, CHttpUrl& url)
{
	output << "Protocol: " << url.GetProtocolString() << '\n';
	output << "Domain: " << url.GetDomain() << '\n';
	output << "Port: " << to_string(url.GetPort()) << '\n';
	output << "Document: " << url.GetDocument() << "\n\n";
}

void UrlController::Help(ostream& output)
{
	output << "This commands are available:\n";
	output << "<url>\n";
	output << "help - shows commands\n";
	output << "ctrl + z - exit\n";
}

void UrlController::HandleCommand(istream& input, ostream& output)
{
	string line;
	getline(input, line);
	if (line == "help")
	{
		Help(output);
	}
	else if (line != "")
	{
		try
		{
			CHttpUrl url(line);
			ShowUrlInfo(output, url);
		}
		catch (CUrlParsingError e)
		{
			cout << e.What() << '\n';
		}
	}

}
#include "stdafx.h"
#include <string>
#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <sstream>
#include <iostream>
#include "UrlController.h"

using namespace std;

int main()
{
	UrlController::Help(cout);
	while (!cin.eof() && !cin.fail())
	{
		UrlController::HandleCommand(cin, cout);
	}
	return 0;
}
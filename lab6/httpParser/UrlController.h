#pragma once
#include <string>
#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <sstream>
#include <iostream>

class UrlController
{
public:
	static void HandleCommand(std::istream& input, std::ostream& output);
	static void Help(std::ostream& output);
	static void ShowUrlInfo(std::ostream& output, CHttpUrl& url);
};


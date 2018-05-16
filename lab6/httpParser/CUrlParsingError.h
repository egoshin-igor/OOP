#pragma once
#include <string>

class CUrlParsingError : public std::invalid_argument
{
public:
	CUrlParsingError(std::string const& message);
	std::string What() const;
private:
	std::string m_msg;
};
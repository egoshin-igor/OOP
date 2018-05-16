#include "stdafx.h"
#include "CUrlParsingError.h"


CUrlParsingError::CUrlParsingError(std::string const& msg)
	:invalid_argument(msg),
	m_msg(msg)
{
}

std::string CUrlParsingError::What() const
{
	return m_msg;
}
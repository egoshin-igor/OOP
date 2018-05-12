#include "stdafx.h"
#include "CMyString.h"
#include <stdint.h>
#include <iostream>

CMyString::CMyString()
	:m_length(0),
	m_pChars(nullptr)
{
}

CMyString::CMyString(const char* pString, size_t length)
{
	m_length = length;
	m_pChars = new char[m_length + 1];
	memcpy(m_pChars, pString, m_length);
	m_pChars[m_length] = '\0';
}

CMyString::CMyString(const char* pString)
	:CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.GetStringData(), other.GetLength())
{
}

void CMyString::Clear()
{
	delete[] m_pChars;
	m_pChars = nullptr;
	m_length = 0;
}

CMyString::CMyString(CMyString&& other)
	:CMyString(other.GetStringData(), other.GetLength())
{
	other.Clear();
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.data(), stlString.length())
{
}

const char* CMyString::GetStringData() const
{
	return m_pChars == nullptr ? "" : m_pChars;
}

CMyString::~CMyString()
{
	delete[] m_pChars;
}

size_t CMyString::GetLength() const
{
	return m_length;
}


CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start > m_length)
	{
		return CMyString();
	}
	auto remainingLen = m_length - start;
	auto subStrLen = remainingLen > length ? length : remainingLen;
	char* pSubString = new char[subStrLen + 1];
	for (size_t i = start; i < subStrLen + start; ++i)
	{
		pSubString[i - start] = m_pChars[i];
	}
	pSubString[subStrLen] = '\0';
	CMyString subString(pSubString);
	delete[] pSubString;
	return subString;
}

CMyString& CMyString::operator=(CMyString const& other)
{
	if (std::addressof(other) != this)
	{
		CMyString tmpCopy(other);
		std::swap(m_pChars, tmpCopy.m_pChars);
		std::swap(m_length, tmpCopy.m_length);
	}
	return *this;
}

CMyString& CMyString::operator =(CMyString&& other)
{
	*this = other;
	other.Clear();
	return *this;
}

CMyString const CMyString::operator +(CMyString const& other) const
{
	auto newLen = other.m_length + m_length;
	char* newPChars = new char[newLen + 1];
	memcpy(newPChars, m_pChars, m_length);
	memcpy(newPChars + m_length, other.GetStringData(), other.m_length + 1);
	newPChars[newLen] = '\0';
	return CMyString(newPChars);
}

CMyString const operator +(std::string& str, CMyString const& myStr)
{
	return CMyString(str) + myStr;
}

CMyString const operator +(const char * pString, CMyString const& myStr)
{
	return  CMyString(pString) + myStr;
}

CMyString& CMyString::operator +=(CMyString const& other)
{
	auto newLen = other.m_length + m_length;
	char* newPChars = new char[newLen + 1];
	memcpy(newPChars, m_pChars, m_length);
	memcpy(newPChars + m_length, other.GetStringData(), other.m_length + 1);
	newPChars[newLen] = '\0';
	std::swap(m_pChars, newPChars);
	m_length = newLen;
	return *this;
}

bool CMyString::operator ==(CMyString const& other) const
{
	if (other.m_length != m_length)
	{
		return false;
	}

	for (size_t i = 0; i < m_length; ++i)
	{
		if (other.m_pChars[i] != m_pChars[i])
		{
			return false;
		}
	}
	return true;
}

bool CMyString::operator !=(CMyString const& other) const
{
	return !(*this == other);
}

bool CMyString::operator <(CMyString const& other) const
{
	return (other != *this) && (*this <= other);
}

bool CMyString::operator >(CMyString const& other) const
{
	return (other != *this) && (*this >= other);
}

bool CMyString::operator <=(CMyString const& other) const
{
	if (other == *this)
	{
		return true;
	}

	for (size_t i = 0; i < m_length && i < other.m_length; ++i)
	{
		if (m_pChars[i] > other.m_pChars[i])
		{
			return false;
		}
		else if (m_pChars[i] < other.m_pChars[i])
		{
			return true;
		}
	}
	if (m_length < other.m_length)
	{
		return true;
	}
	return false;
}

bool CMyString::operator >=(CMyString const& other) const
{
	return other == *this || !(*this <= other);
}

const char& CMyString::operator [](size_t i) const
{
	if (i >= m_length && i < 0)
	{
		throw std::invalid_argument("index is out of range");
	}
	return m_pChars[i];
}

char& CMyString::operator [](size_t i)
{
	if (i >= m_length && i < 0)
	{
		throw std::out_of_range("index is out of range");
	}
	return m_pChars[i];
}

std::ostream& operator <<(std::ostream& stream, CMyString const& myStr)
{
	stream << myStr.GetStringData();
	return stream;
}

std::istream& operator >>(std::istream& stream, CMyString& myStr)
{
	std::string str;
	if (stream >> str)
	{
		myStr = str;
	}
	else
	{
		stream.setstate(std::ios_base::failbit | stream.rdstate());
	}
	return stream;
}

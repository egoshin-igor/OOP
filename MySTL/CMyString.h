#pragma once
#include <stdint.h>
#include <string>

class CMyString
{
public:
	CMyString();
	CMyString(const char * pString);
	CMyString(const char * pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString && other);
	CMyString(std::string const& stlString);
	~CMyString();

	size_t GetLength() const;
	const char* GetStringData() const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();
	CMyString& operator=(CMyString const& other);
	CMyString& operator =(CMyString&& other);
	CMyString const operator +(CMyString const& other) const;
	CMyString& operator +=(CMyString const& other);
	bool operator ==(CMyString const& other) const;
	bool operator !=(CMyString const& other) const;
	bool operator <(CMyString const& other) const;
	bool operator >(CMyString const& other) const;
	bool operator <=(CMyString const& other) const;
	bool operator >=(CMyString const& other) const;
	const char& operator [](size_t i) const;
	char& operator [](size_t i);
private:
	char* m_pChars;
	size_t m_length;
};

CMyString const operator +(std::string& str, CMyString const& myStr);
CMyString const operator +(const char * pString, CMyString const& myStr);
std::ostream& operator <<(std::ostream& stream, CMyString const& myStr);
std::istream& operator >>(std::istream& stream, CMyString& myStr);
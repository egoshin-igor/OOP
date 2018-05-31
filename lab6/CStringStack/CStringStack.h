#pragma once
#include "../../MySTL/CMyArray.h"
#include <string>

class CStringStack
{
public:
	CStringStack() = default;
	CStringStack(std::initializer_list<std::string> arr);
	CStringStack(const CStringStack& strStack);
	CStringStack(CStringStack&& strStack);
	~CStringStack() = default;
	CStringStack& operator=(const CStringStack& strStack);
	CStringStack& operator=(CStringStack&& strStack);
	void Push(const std::string& value);
	void Pop();
	std::string Top() const;
	size_t Size() const;
	void Clear();

private:
	CMyArray<std::string> m_arr;
};


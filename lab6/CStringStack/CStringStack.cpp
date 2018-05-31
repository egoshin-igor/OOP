#include "stdafx.h"
#include "CStringStack.h"

CStringStack::CStringStack(std::initializer_list<std::string> arr)
{
	size_t i = 0;
	m_arr.Resize(arr.size());
	for (auto elem : arr)
	{
		m_arr[i] = elem;
		++i;
	}
}

CStringStack::CStringStack(const CStringStack& strStack)
{
	m_arr = strStack.m_arr;
}

CStringStack::CStringStack(CStringStack&& strStack)
{
	m_arr = strStack.m_arr;
	strStack.Clear();
}

CStringStack& CStringStack::operator=(const CStringStack& strStack)
{
	m_arr = strStack.m_arr;
	return *this;
}

CStringStack& CStringStack::operator=(CStringStack&& strStack)
{
	m_arr = strStack.m_arr;
	strStack.Clear();
	return *this;
}


void CStringStack::Push(const std::string& value)
{
	m_arr.PushBack(value);
}

void CStringStack::Pop()
{
	auto stackSize = m_arr.Size();
	if (stackSize > 0)
	{
		m_arr.Resize(stackSize - 1);
	}
	else
	{
		throw std::underflow_error("Stack is empty. Pop is not available");
	}
}

std::string CStringStack::Top() const
{
	auto stackSize = m_arr.Size();
	if (stackSize > 0)
	{
		return m_arr[m_arr.Size() - 1];
	}
	else
	{
		throw std::underflow_error("Stack is empty. Top is not available");
	}
}

size_t CStringStack::Size() const
{
	return m_arr.Size();
}

void CStringStack::Clear()
{
	m_arr.Clear();
}
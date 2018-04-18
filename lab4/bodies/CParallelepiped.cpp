#include "stdafx.h"
#include "CParallelepiped.h"


CParallelepiped::CParallelepiped(double height, double width, double depth, double density)
	: CBody("Parallelepiped", density)
	, m_height(height)
	, m_width(width)
	, m_depth(depth)
{
}

double CParallelepiped::GetWidth() const
{
	return m_width;
}

double CParallelepiped::GetHeight() const
{
	return m_height;
}

double CParallelepiped::GetDepth() const
{
	return m_depth;
}

double CParallelepiped::GetVolume() const
{
	return GetDepth() * GetHeight() * GetWidth();
}

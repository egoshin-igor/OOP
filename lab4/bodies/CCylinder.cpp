#include "stdafx.h"
#include "CCylinder.h"

CCylinder::CCylinder(double baseRadius, double height, double density)
	: CBody("Cylinder", density)
	, m_baseRadius(baseRadius)
	, m_height(height)
{
}

double CCylinder::GetBasedRadius() const
{
	return m_baseRadius;
}

double CCylinder::GetHeight() const
{
	return m_height;
}

double CCylinder::GetVolume() const
{
	return M_PI *  pow(m_baseRadius, 2) * m_height;
}
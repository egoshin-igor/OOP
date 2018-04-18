#include "stdafx.h"
#include "CCone.h"

CCone::CCone(double baseRadius, double height, double density)
	: CBody("Cone", density)
	, m_baseRadius(baseRadius)
	, m_height(height)
{
}

double CCone::GetBasedRadius() const
{
	return m_baseRadius;
}

double CCone::GetHeight() const
{
	return m_height;
}

double CCone::GetVolume() const
{
	return (1 / 3) * m_height * M_PI *  pow(m_baseRadius, 2);
}
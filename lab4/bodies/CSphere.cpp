#include "stdafx.h"
#include "CSphere.h"

CSphere::CSphere(double density, double radius)
	: CBody("Sphere", density)
	, m_radius(radius)
{
}

double CSphere::GetRadius() const
{
	return m_radius;
}

double CSphere::GetVolume() const
{
	return (4 / 3) * M_PI * pow(m_radius, 3);
}

#include "stdafx.h"
#include "Cbody.h"
#include "CSphere.h"

CBody::CBody()
{
}

CBody::CBody(const std::string& type, double density)
	: m_density(density)
	, m_type(type)
{
}

CBody::~CBody()
{
}

double CBody::GetDensity() const
{
	return m_density;
}

double CBody::GetMass() const
{
	return GetDensity() * GetVolume();
}

std::string CBody::ToString() const
{
	std::ostringstream strStream;
	strStream << m_type << ":" << '\n'
		<< "\tdensity = " << GetDensity() << '\n'
		<< "\tvolume = " << GetVolume() << '\n'
		<< "\tmass = " << GetMass() << '\n';
	return strStream.str();
}

double CBody::GetVolume() const
{
	return 0.0;
}
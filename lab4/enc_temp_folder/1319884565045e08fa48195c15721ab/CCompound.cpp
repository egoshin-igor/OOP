#include "stdafx.h"
#include "CCompound.h"

/*
CCompound::BodyParametrs CCompound::GetBodyParametrs(CBody const& body)
{
	CCompound::BodyParametrs params;
	params.density = body.GetDensity();
	params.mass = body.GetMass();
	params.volume = body.GetVolume();
	params.toString = body.ToString();
	
	return params;
}
*/

double CCompound::GetVolume() const
{
	double sumVolume = 0;
	for (size_t i = 0; i < m_bodies.size(); ++i)
	{
		auto params = m_bodies[i];
		sumVolume += params->GetVolume();
	}
	return sumVolume;
}

double CCompound::GetMass() const
{
	double sumMass = 0;
	for (size_t i = 0; i < m_bodies.size(); ++i)
	{
		auto params = m_bodies[i];
		sumMass += params->GetMass();
	}
	return sumMass;
}

double CCompound::GetDensity() const
{
	return GetMass() / GetVolume();
}

std::string CCompound::ToString() const
{
	std::ostringstream strStream;
	strStream << "Compound" << ":" << '\n'
		<< "\tdensity = " << GetDensity() << '\n'
		<< "\tvolume = " << GetVolume() << '\n'
		<< "\tmass = " << GetMass() << '\n';
	std::string str = strStream.str() + '\n';
	for (size_t i = 0; i < m_bodies.size(); ++i)
	{
		auto params = m_bodies[i];
		str += params->ToString() + '\n';
	}
	return str;
}

bool CCompound::AddChildBody(std::shared_ptr<CBody> child)
{
	if (this == &*child)
	{
		return false;
	}

	m_bodies.push_back(std::move(child));
	return true;
}

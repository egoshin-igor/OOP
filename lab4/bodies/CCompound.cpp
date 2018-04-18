#include "stdafx.h"
#include "CCompound.h"

CCompound::CCompound()
{
}

double CCompound::GetVolume() const
{
	double sumVolume = 0;
	for (size_t i = 0; i < bodiesPtr.size(); ++i)
	{
		auto child = *bodiesPtr[i];
		sumVolume += child.GetVolume();
	}
	return sumVolume;
}

double CCompound::GetMass() const
{
	double sumMass = 0;
	for (size_t i = 0; i < bodiesPtr.size(); ++i)
	{
		auto child = *bodiesPtr[i];
		sumMass += child.GetMass();
	}
	return sumMass;
}

double CCompound::GetDensity() const
{
	double sumDensity = 0;
	for (size_t i = 0; i < bodiesPtr.size(); ++i)
	{
		auto child = *bodiesPtr[i];
		sumDensity += child.GetDensity();
	}
	return sumDensity;
}

std::string CCompound::ToString() const
{
	std::ostringstream strStream;
	strStream << "Compound" << ":" << '\n'
		<< "\tdensity = " << GetDensity() << '\n'
		<< "\tvolume = " << GetVolume() << '\n'
		<< "\tmass = " << GetMass() << '\n';
	std::string str = strStream.str() + '\n';
	for (size_t i = 0; i < bodiesPtr.size(); ++i)
	{
		auto child = *bodiesPtr[i];
		str += child.ToString() + '\n';
	}
	return str;
}

bool CCompound::AddChildBody(CBody const& child)
{
	if (this == &child)
	{
		return false;
	}
	auto childPtr = std::make_shared<CBody>(child);
	bodiesPtr.push_back(childPtr);
	return true;
}

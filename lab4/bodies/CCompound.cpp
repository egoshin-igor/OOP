#include "stdafx.h"
#include "CCompound.h"

CCompound::CCompound()
	: CBody("Compound")
{
}

double CCompound::GetVolume() const
{
	double sumVolume = 0;
	for (size_t i = 0; i < m_bodiesPtr.size(); ++i)
	{
		sumVolume += m_bodiesPtr[i]->GetVolume();
	}
	return sumVolume;
}

bool CCompound::IsHadSameChild(std::shared_ptr<CCompound> verifiableBody)
{
	for (size_t i = 0; i < m_bodiesPtr.size(); ++i)
	{
		if (m_bodiesPtr[i]->GetType() == "Compound")
		{
			auto childValue = dynamic_cast<CCompound&>(*m_bodiesPtr[i]);
			bool isHadSameChild = childValue.IsHadSameChild(std::make_shared<CCompound>(*this));
			if (isHadSameChild)
			{
				throw std::invalid_argument("Adding compound body on yourself is not allowed\n");
			}
		}
		if (m_bodiesPtr[i].get() == verifiableBody.get())
		{
			return true;
		}
	}
	return false;
}

double CCompound::GetMass() const
{
	double sumMass = 0;
	for (size_t i = 0; i < m_bodiesPtr.size(); ++i)
	{
		sumMass += m_bodiesPtr[i]->GetMass();
	}
	return sumMass;
}

double CCompound::GetDensity() const
{
	return GetMass() / GetVolume();
}

std::string CCompound::ToString() const
{
	if (m_bodiesPtr.size() == 0)
	{
		return "Compound:\n\tbody is empty\n";
	}
	std::string str = "Compound:\n";
	str += "  Compound childs begin\n";
	for (size_t i = 0; i < m_bodiesPtr.size(); ++i)
	{
		str += "    " + m_bodiesPtr[i]->ToString();
	}
	str += "  Compound childs end\n";
	return str;
}

void CCompound::AddChildBody(std::shared_ptr<CBody> child)
{
	if (child->GetType() == "Compound")
	{
		auto childValue = dynamic_cast<CCompound&>(*child);
		bool isHadSameChild = childValue.IsHadSameChild(std::make_shared<CCompound>(*this));
		if (isHadSameChild)
		{
			throw std::invalid_argument("Adding compound body on yourself is not allowed\n");
		}
	}

	if (child.get() == this)
	{
		throw std::invalid_argument("Adding compound body on yourself is not allowed\n");
	}

	m_bodiesPtr.push_back(child);
}
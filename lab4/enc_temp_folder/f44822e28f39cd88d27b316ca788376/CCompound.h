#pragma once
#include "Cbody.h"
#include <string>
#include <memory>
#include <vector>
#include <map>

class CCompound : public CBody
{
public:
	double GetVolume() const override;
	double GetMass() const override;
	double GetDensity() const override;
	std::string ToString() const override;
	bool AddChildBody(std::shared_ptr<CBody> child);
private:
	std::vector<std::shared_ptr<CBody>> m_bodies;
	/*
	struct BodyParametrs
	{
		double mass, volume, density;
		std::string toString;
	};

	std::vector<BodyParametrs> m_bodies;

	BodyParametrs GetBodyParametrs(CBody const& body);
	*/
	
};

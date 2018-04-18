#pragma once
#include "Cbody.h"
#include <string>
#include <memory>
#include <vector>

class CCompound : public CBody
{
public:
	CCompound();
	double GetVolume() const override;
	double GetMass() const override;
	double GetDensity() const override;
	std::string ToString() const override;
	bool AddChildBody(CBody const& child);

private:
	std::vector<std::shared_ptr<CBody>> bodiesPtr;
};


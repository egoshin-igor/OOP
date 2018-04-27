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
	void AddChildBody(std::shared_ptr<CBody> child);
private:
	bool IsHadSameChild(std::shared_ptr<CCompound> verifiableBody);
	std::vector<std::shared_ptr<CBody>> m_bodiesPtr;
};


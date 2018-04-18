#pragma once
#include "Cbody.h"

class CCylinder : public CBody
{
public:
	CCylinder(double baseRadius, double height, double density);

	double GetBasedRadius() const;
	double GetHeight() const;
	double GetVolume() const override;
private:
	double m_baseRadius, m_height;
};


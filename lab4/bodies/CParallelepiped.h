#pragma once
#include "Cbody.h"

class CParallelepiped : public CBody
{
public:
	CParallelepiped(double height, double width, double depth, double density);

	double GetWidth() const;
	double GetHeight() const;
	double GetDepth() const;
	double GetVolume() const override;
private:
	double m_height, m_width, m_depth;
};


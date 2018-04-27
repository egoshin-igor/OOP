#pragma once
#include <string>

class CBody
{
public:
	CBody();
	CBody(const std::string& type);
	CBody(const std::string& type, double density);

	virtual double GetDensity() const;
	virtual double GetMass() const;
	virtual std::string ToString() const;
	virtual double GetVolume() const;

	virtual std::string GetType()const;

	virtual ~CBody();
private:
	double m_density;
	std::string m_type = "CBody";
};
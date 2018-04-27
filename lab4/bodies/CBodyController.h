#pragma once

#include "stdafx.h"
#include "Cbody.h"
#include "CCompound.h"
#include "CCone.h"
#include "CCylinder.h"
#include "CParallelepiped.h"
#include "CSphere.h"
#include "CCone.h"
#include "CCompound.h"
#include "memory"

class CBodyController
{
public:
	CBodyController(std::istream& input, std::ostream& output);
	
	void HandleCommand();
	std::shared_ptr<CBody> GetBodyWithMaxMass();
	std::shared_ptr<CBody> GetBodyWithMinMassInWater();
private:
	bool StringToDouble(const std::string& str, double& number);
	void AddSphere(std::istream& args);
	void AddCone(std::istream& args);
	void AddCylinder(std::istream& args);
	void AddParallelepiped(std::istream& args);
	void AddCompound();
	void TypeInfoAboutBodies();
	bool ChooseBody(std::istream& stream, const std::string body);
	void Help();

	std::istream& m_input;
	std::ostream& m_output;
	std::vector <std::shared_ptr<CBody>> m_bodies;
};


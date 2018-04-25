#include "stdafx.h"
#include "CBodyController.h"

CBodyController::CBodyController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
	Help();
}

CBodyController::~CBodyController()
{
	TypeInfoAboutBodies();
}

void CBodyController::Help()
{
	std::cout << "This bodies are available:\n";
	std::cout << "cone <baseRadius> <height> <density>\n";
	std::cout << "cylinder <baseRadius> <height> <density>\n";
	std::cout << "parallelepiped <height> <width> <depth> <density>\n";
	std::cout << "sphere <density> <radius>\n";
	std::cout << "compound\n";
}

void CBodyController::HandleCommand()
{
	std::string line;
	getline(m_input, line);
	if (m_input.eof() && line == "")
	{
		return ;
	}

	std::istringstream stream(line);
	std::string body;
	stream >> body;
	ChooseCommand(stream, body);
}

bool CBodyController::ChooseCommand(std::istream& stream, const std::string body)
{
	if (body == "sphere")
	{
		AddSphere(stream);
		return true;
	}
	if (body == "cone")
	{
		AddCone(stream);
		return true;
	}
	if (body == "cylinder")
	{
		AddCylinder(stream);
		return true;
	}
	if (body == "parallelepiped")
	{
		AddParallelepiped(stream);
		return true;
	}
	if (body == "compound")
	{
		AddCompound();
		return true;
	}
	std::cout << "unknown command\n";
	return false;
}

void CBodyController::AddSphere(std::istream& args)
{
	std::string radius, density;

	if (!(args >> radius))
	{
		m_output << "Cant read radius\n";
		return;
	}

	if (!(args >> density))
	{
		m_output << "Cant read density\n";
		return;
	}

	double dRadius, dDensity;

	if (!StringToDouble(radius, dRadius) || !StringToDouble(density, dDensity))
	{
		m_output << "One of args is not a number\n";
		return;
	}


	std::shared_ptr<CSphere> bodyPtr(new CSphere(dDensity, dRadius));
	m_bodies.push_back(std::move(bodyPtr));
}

void CBodyController::AddCone(std::istream& args)
{
	std::string radius, height, density;

	if (!(args >> radius))
	{
		m_output << "Cant read radius\n";
		return;
	}

	if (!(args >> height))
	{
		m_output << "Cant read height\n";
		return;
	}

	if (!(args >> density))
	{
		m_output << "Cant read density\n";
		return;
	}

	double dRadius, dHeight, dDensity;

	if (!StringToDouble(radius, dRadius) || !StringToDouble(density, dDensity) || !StringToDouble(density, dHeight))
	{
		m_output << "One of args is not a number\n";
		return;
	}

	std::shared_ptr<CCone> bodyPtr(new CCone(dRadius, dHeight, dDensity));
	m_bodies.push_back(std::move(bodyPtr));
}

void CBodyController::AddParallelepiped(std::istream& args)
{
	std::string height, width, depth, density;

	if (!(args >> density))
	{
		m_output << "Cant read density\n";
		return;
	}

	if (!(args >> height))
	{
		m_output << "Cant read height\n";
		return;
	}

	if (!(args >> width))
	{
		m_output << "Cant read width\n";
		return;
	}

	if (!(args >> depth))
	{
		m_output << "Cant read depth\n";
		return;
	}

	double dHeight, dWidth, dDepth, dDensity;

	if (!StringToDouble(height, dHeight) || !StringToDouble(width, dWidth) || !StringToDouble(depth, dDepth) || !StringToDouble(density, dDensity))
	{
		m_output << "One of args is not a number\n";
		return;
	}

	std::shared_ptr<CParallelepiped> bodyPtr(new CParallelepiped(dHeight, dWidth, dDepth, dDensity));
	m_bodies.push_back(std::move(bodyPtr));
}


void CBodyController::AddCylinder(std::istream& args)
{
	std::string radius, height, density;

	if (!(args >> radius))
	{
		m_output << "Cant read radius\n";
		return;
	}

	if (!(args >> height))
	{
		m_output << "Cant read height\n";
		return;
	}

	if (!(args >> density))
	{
		m_output << "Cant read density\n";
		return;
	}

	double dRadius, dHeight, dDensity;

	if (!StringToDouble(radius, dRadius) || !StringToDouble(density, dDensity) || !StringToDouble(density, dHeight))
	{
		m_output << "One of args is not a number\n";
		return;
	}

	std::shared_ptr<CCylinder> bodyPtr(new CCylinder(dRadius, dHeight, dDensity));
	m_bodies.push_back(std::move(bodyPtr));
}

void CBodyController::AddCompound()
{
	std::string command = "";
	std::string body;
	m_output << "Type <body name> parametrs for add a simple body to a compound one\n";
	m_output << "Type <end> for stop add bodies\n";
	CCompound compound;
	bool haveChanges = false;
	while (!m_input.eof() || !m_input.fail())
	{
		getline(m_input, command);
		if (command != "end")
		{
			std::istringstream stream(command);
			stream >> body;
			if (ChooseCommand(stream, body))
			{
				haveChanges = true;
				compound.AddChildBody((*m_bodies.back()));
				m_bodies.pop_back();
			}
		}
		else
		{
			break;
		}
	}
	if (haveChanges)
	{
		auto bodyPtr = std::make_shared<CCompound>(compound);
		m_bodies.push_back(std::move(bodyPtr));
	}
}

std::shared_ptr<CBody> CBodyController::GetBodyWithMaxMass()
{
	if (m_bodies.size() != 0)
	{
		double maxMass = 0;
		size_t b = 0;
		for (size_t i = 0; i < m_bodies.size(); ++i)
		{
			b = ((*m_bodies[i]).GetMass()) > maxMass ? i : b;
		}
		return std::shared_ptr<CBody>(m_bodies[b]);
	}
	return NULL;
}

std::shared_ptr<CBody> CBodyController::GetBodyWithMinMassInWater()
{
	if (m_bodies.size() != 0)
	{
		const double WATER_DENSITY = 1000;
		const double G = 9.88;

		double density, volume;
		double minMass = HUGE_VAL;
		size_t b = 0;
		for (size_t i = 0; i < m_bodies.size(); ++i)
		{
			density = (*m_bodies[i]).GetDensity();
			volume = (*m_bodies[i]).GetVolume();
			b = ((density - WATER_DENSITY) * G * volume) < minMass ? i : b;
		}
		return std::shared_ptr<CBody>(m_bodies[b]);
	}
	return NULL;
}


void CBodyController::TypeInfoAboutBodies()
{
	for (auto body : m_bodies)
	{
		m_output << (*body).ToString();
	}
	m_output << "This is body with min mass in water:\n";
	auto bodyPtr = GetBodyWithMinMassInWater();
	if (bodyPtr != NULL)
	{
		m_output << (*bodyPtr).ToString();
	}
	m_output << "This is body with max mass:\n";
	bodyPtr = GetBodyWithMaxMass();
	if (bodyPtr != NULL)
	{
		m_output << (*bodyPtr).ToString();
	}
}

bool CBodyController::StringToDouble(const std::string& str, double& number)
{
	const double E = 0.01;
	bool error;
	char* pLastChar = NULL;
	auto charStr = str.c_str();
	number = strtod(charStr, &pLastChar);
	error = !((*(charStr) == '\0') || (*pLastChar != '\0'));
	if (abs(number - HUGE_VAL) < E)
	{
		error = false;
	}
	return error;
}
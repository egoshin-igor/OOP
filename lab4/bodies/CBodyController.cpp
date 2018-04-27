#include "stdafx.h"
#include "CBodyController.h"

CBodyController::CBodyController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
	Help();
}

void CBodyController::Help()
{
	std::cout << "This commands are available:\n";
	std::cout << "cone <baseRadius> <height> <density>\n";
	std::cout << "cylinder <baseRadius> <height> <density>\n";
	std::cout << "parallelepiped <height> <width> <depth> <density>\n";
	std::cout << "sphere <density> <radius>\n";
	std::cout << "compound\n";
	std::cout << "info - information about bodies\n";
	std::cout << "help - information about commands\n";
}

void CBodyController::HandleCommand()
{
	std::string line;
	bool BodyIsChoosed = false;
	getline(m_input, line);
	if (m_input.eof() && line == "")
	{
		return;
	}

	std::istringstream stream(line);
	std::string command;
	stream >> command;
	
	try 
	{
		ChooseBody(stream, command);
	}
	catch (std::invalid_argument& ex)
	{
		std::cout << ex.what();
	}
}

bool CBodyController::ChooseBody(std::istream& stream, const std::string command)
{
	if (command == "sphere")
	{
		AddSphere(stream);
		return true;
	}
	if (command == "cone")
	{
		AddCone(stream);
		return true;
	}
	if (command == "cylinder")
	{
		AddCylinder(stream);
		return true;
	}
	if (command == "parallelepiped")
	{
		AddParallelepiped(stream);
		return true;
	}
	if (command == "compound")
	{
		AddCompound();
		return true;
	}
	if (command == "help")
	{
		Help();
		return true;
	}
	if (command == "info")
	{
		TypeInfoAboutBodies();
		return true;
	}
	else
	{
		std::cout << "unknown command\n";
	}
	return false;
}

void CBodyController::AddSphere(std::istream& args)
{
	std::string radius, density;

	if (!(args >> radius))
	{
		throw std::invalid_argument("Cant read radius\n");
	}

	if (!(args >> density))
	{
		throw std::invalid_argument("Cant read density\n");
	}

	double dRadius, dDensity;

	if (!StringToDouble(radius, dRadius) || !StringToDouble(density, dDensity))
	{
		throw std::invalid_argument("One of args is not a number\n");
	}

	std::shared_ptr<CSphere> bodyPtr(new CSphere(dDensity, dRadius));
	m_bodies.push_back(std::move(bodyPtr));
}

void CBodyController::AddCone(std::istream& args)
{
	std::string radius, height, density;

	if (!(args >> radius))
	{
		throw std::invalid_argument("Cant read radius\n");
	}

	if (!(args >> height))
	{
		throw std::invalid_argument("Cant read height\n");
	}

	if (!(args >> density))
	{
		throw std::invalid_argument("Cant read density\n");
	}

	double dRadius, dHeight, dDensity;

	if (!StringToDouble(radius, dRadius) || !StringToDouble(density, dDensity) || !StringToDouble(density, dHeight))
	{
		throw std::invalid_argument("One of args is not a number\n");
	}

	std::shared_ptr<CCone> bodyPtr(new CCone(dRadius, dHeight, dDensity));
	m_bodies.push_back(std::move(bodyPtr));
}

void CBodyController::AddParallelepiped(std::istream& args)
{
	std::string height, width, depth, density;

	if (!(args >> density))
	{
		throw std::invalid_argument("Cant read density\n");
	}

	if (!(args >> height))
	{
		throw std::invalid_argument("Cant read height\n");
	}

	if (!(args >> width))
	{
		throw std::invalid_argument("Cant read width\n");
		return;
	}

	if (!(args >> depth))
	{
		throw std::invalid_argument("Cant read depth\n");
	}

	double dHeight, dWidth, dDepth, dDensity;

	if (!StringToDouble(height, dHeight) || !StringToDouble(width, dWidth) || !StringToDouble(depth, dDepth) || !StringToDouble(density, dDensity))
	{
		throw std::invalid_argument("One of args is not a number\n");
	}

	std::shared_ptr<CParallelepiped> bodyPtr(new CParallelepiped(dHeight, dWidth, dDepth, dDensity));
	m_bodies.push_back(std::move(bodyPtr));
}


void CBodyController::AddCylinder(std::istream& args)
{
	std::string radius, height, density;

	if (!(args >> radius))
	{
		throw std::invalid_argument("Cant read radius\n");
	}

	if (!(args >> height))
	{
		throw std::invalid_argument("Cant read height\n");
	}

	if (!(args >> density))
	{
		throw std::invalid_argument("Cant read density\n");
	}

	double dRadius, dHeight, dDensity;

	if (!StringToDouble(radius, dRadius) || !StringToDouble(density, dDensity) || !StringToDouble(density, dHeight))
	{
		throw std::invalid_argument("One of args is not a number\n");
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
	bool bodyIsChoosed = false;
	while (!m_input.eof() || !m_input.fail())
	{
		getline(m_input, command);
		if (command != "end")
		{
			std::istringstream stream(command);
			stream >> body;
			try 
			{
				if (ChooseBody(stream, body))
				{
					compound.AddChildBody((m_bodies.back()));
					m_bodies.pop_back();
				}
			}
			catch (std::invalid_argument& ex)
			{
				std::cout << ex.what();
			}
		}
		else
		{
			break;
		}
	}
	auto bodyPtr = std::make_shared<CCompound>(compound);
	m_bodies.push_back(std::move(bodyPtr));
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
	if (m_bodies.size() == 0)
	{
		m_output << "bodies not added yet\n";
		return;
	}
	for (auto body : m_bodies)
	{
		m_output << body->ToString();
	}
	m_output << "This is body with min mass in water:\n";
	auto bodyPtr = GetBodyWithMinMassInWater();
	if (bodyPtr != NULL)
	{
		m_output << bodyPtr->ToString();
	}
	m_output << "This is body with max mass:\n";
	bodyPtr = GetBodyWithMaxMass();
	if (bodyPtr != NULL)
	{
		m_output << bodyPtr->ToString();
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
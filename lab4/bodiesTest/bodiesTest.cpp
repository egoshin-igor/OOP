#include "stdafx.h"
#include "../bodies/Cbody.h"
#include "../bodies/CCompound.h"
#include "../bodies/CCone.h"
#include "../bodies/CCylinder.h"
#include "../bodies/CParallelepiped.h"
#include "../bodies/CSphere.h"
#include "../bodies/CBodyController.h"
#include <iostream>
#include <sstream>
#pragma optimize( "", off )

using namespace std;

bool IsEqualDouble(double d1, double d2)
{
	const double E = 0.1;
	return abs(d1 - d2) < E;
}

TEST_CASE("Bodies test")
{
	cout << "Bodies test\n";

	cout << "--CSphereTest\n";
	{
		double radius = 11;
		double density = 15.8;
		double volume = 5575.28;
		double mass = 88089.4;

		CSphere sphere(density, radius);
		CHECK(static_cast<const CBody*>(&sphere)); //объемное тело

		CHECK(IsEqualDouble(sphere.GetRadius(), radius)); //радиус совпадает

		CHECK(IsEqualDouble(sphere.GetDensity(), density)); //плотность совпадает

		CHECK(IsEqualDouble(sphere.GetVolume(), volume)); //объем совпадает

		CHECK(IsEqualDouble(sphere.GetMass(), mass)); //масса совпадает
	}

	cout << "--CCylinderTest\n";
	{
		double radius = 4;
		double height = 6;
		double density = 20;
		double volume = 301.59;
		double mass = 6031.86;

		CCylinder cylinder(radius, height, density);

		CHECK(static_cast<const CBody*>(&cylinder)); //объемное тело

		CHECK(IsEqualDouble(cylinder.GetBasedRadius(), radius)); //радиус совпадает

		CHECK(IsEqualDouble(cylinder.GetHeight(), height)); //высота совпадает

		CHECK(IsEqualDouble(cylinder.GetDensity(), density)); //плотность совпадает

		CHECK(IsEqualDouble(cylinder.GetVolume(), volume)); //объем совпадает

		CHECK(IsEqualDouble(cylinder.GetMass(), mass)); //масса совпадает
	}

	cout << "--CConeTest\n";
	{
		double radius = 4;
		double height = 6;
		double density = 20;
		double volume = 100.53;
		double mass = 2010.62;

		CCone cone(radius, height, density);

		CHECK(static_cast<const CBody*>(&cone)); //объемное тело

		CHECK(IsEqualDouble(cone.GetBasedRadius(), radius)); //радиус совпадает

		CHECK(IsEqualDouble(cone.GetHeight(), height)); //высота совпадает

		CHECK(IsEqualDouble(cone.GetDensity(), density)); //плотность совпадает

		CHECK(IsEqualDouble(cone.GetVolume(), volume)); //объем совпадает

		CHECK(IsEqualDouble(cone.GetMass(), mass)); //масса совпадает
	}

	cout << "--CParallelepipedTest\n";
	{
		double height = 6;
		double width = 4;
		double depth = 10;
		double density = 20;
		double volume = 240;
		double mass = 4800;

		CParallelepiped parallelepiped(height, width, depth, density);

		CHECK(static_cast<const CBody*>(&parallelepiped)); //объемное тело

		CHECK(IsEqualDouble(parallelepiped.GetWidth(), width)); //ширина совпадает

		CHECK(IsEqualDouble(parallelepiped.GetHeight(), height)); //высота совпадает

		CHECK(IsEqualDouble(parallelepiped.GetDepth(), depth)); //глубина совпадает

		CHECK(IsEqualDouble(parallelepiped.GetDensity(), density)); //плотность совпадает

		CHECK(IsEqualDouble(parallelepiped.GetVolume(), volume)); //объем совпадает

		CHECK(IsEqualDouble(parallelepiped.GetMass(), mass)); //масса совпадает
	}

	cout << "--CCompoundTest\n";
	{
		cout << "----Try to add compound body on yourself\n";
		{
			CCompound compoundBody;
			CCompound tempCompound;

			try
			{
				compoundBody.AddChildBody(std::make_shared<CCompound>(compoundBody));
			}
			catch (std::invalid_argument& ex)
			{
				CHECK(ex.what() == static_cast<const string&>("Adding compound body on yourself is not allowed\n"));
			}

			try
			{
				tempCompound.AddChildBody(std::make_shared<CCompound>(compoundBody));
				compoundBody.AddChildBody(std::make_shared<CCompound>(tempCompound));

			}
			catch (std::invalid_argument& ex)
			{
				CHECK(ex.what() == static_cast<const string&>("Adding compound body on yourself is not allowed\n"));
			}
		}

		cout << "----Check methods of compound body\n";
		{
			CCompound compoundBody;
			CCompound tempCompound;

			CParallelepiped parallelepipedTwo(10, 10, 10, 10);
			CSphere sphereTwo(10, 10);
			CCone cone(5, 5, 5);
			CCylinder cylinder(9, 2, 8);

			CParallelepiped parallelepipedOne(10, 10, 10, 10);
			CSphere sphereOne(10, 10);

			tempCompound.AddChildBody(std::make_shared<CParallelepiped>(parallelepipedOne));
			tempCompound.AddChildBody(std::make_shared<CSphere>(sphereOne));

			double volume = parallelepipedTwo.GetVolume() + sphereTwo.GetVolume() + cone.GetVolume() + cylinder.GetVolume() + tempCompound.GetVolume();
			double mass = parallelepipedTwo.GetMass() + sphereTwo.GetMass() + cone.GetMass() + cylinder.GetMass() + tempCompound.GetMass();
			double density = mass / volume;

			compoundBody.AddChildBody(std::make_shared<CParallelepiped>(parallelepipedTwo));
			compoundBody.AddChildBody(std::make_shared<CSphere>(sphereTwo));
			compoundBody.AddChildBody(std::make_shared<CCone>(cone));
			compoundBody.AddChildBody(std::make_shared<CCylinder>(cylinder));
			compoundBody.AddChildBody(std::make_shared<CCompound>(tempCompound));


			CHECK(static_cast<const CBody*>(&compoundBody)); //объемное тело

			CHECK(IsEqualDouble(compoundBody.GetDensity(), density)); //плотность совпадает

			CHECK(IsEqualDouble(compoundBody.GetVolume(), volume)); //объем совпадает

			CHECK(IsEqualDouble(compoundBody.GetMass(), mass)); //масса совпадает
		}
	}
}

void AddCommand(stringstream& input, CBodyController& bodyController, const string& body)
{
	input << body << "\n";
	bodyController.HandleCommand();
}

TEST_CASE("Max mass and min mass in water")
{
	cout << "Max mass and min mass in water\n";
	stringstream input;
	stringstream output;
	CBodyController bodyController(input, output);
	AddCommand(input, bodyController, "sphere 1 1");
	AddCommand(input, bodyController, "cylinder 3 2 1");
	AddCommand(input, bodyController, "cone 1 2 3");
	//AddCommand(input, bodyController, "info");
	AddCommand(input, bodyController, "min");
	AddCommand(input, bodyController, "max");
	REQUIRE(output.str() == "Cylinder\nCylinder\n"); //max mass 28.27; min mass in water(Ft - Fa = -279071)
}
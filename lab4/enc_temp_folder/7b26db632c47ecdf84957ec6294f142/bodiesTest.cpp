#include "stdafx.h"
#include "../bodies/Cbody.h"
#include "../bodies/CCompound.h"
#include "../bodies/CCone.h"
#include "../bodies/CCylinder.h"
#include "../bodies/CParallelepiped.h"
#include "../bodies/CSphere.h"

using namespace std;

bool IsEqualDouble(double d1, double d2)
{
	const double E = 0.1;
	return abs(d1 - d2) < E;
}

TEST_CASE("Bodies test")
{
	//cout << "Bodies test\n";

	//cout << "\tCSphereTest\n";
	SECTION("CSphereTest")
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

	//cout << "\CCylinderTest\n";
	SECTION("CCylinderTest")
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

	//cout << "\CConeTest\n";
	SECTION("CConeTest")
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

	//cout << "\tCParallelepipedTest\n";
	SECTION("CParallelepipedTest")
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

	//cout << "\tCCompoundTest\n";
	SECTION("CCompoundTest")
	{
		CCompound compoundBody;
		CParallelepiped parallelepiped(10, 10, 10, 10);
		CSphere sphere(10, 10);
		CCone cone(5, 5, 5);
		CCylinder cylinder(9, 2, 8);
		CCompound compound;
		compound.AddChildBody(make_shared<CBody>(parallelepiped));
		compound.AddChildBody(make_shared<CBody>(sphere));

		double volume = parallelepiped.GetVolume() + sphere.GetVolume() + cone.GetVolume() + cylinder.GetVolume() + compound.GetVolume();
		double mass = parallelepiped.GetMass() + sphere.GetMass() + cone.GetMass() + cylinder.GetMass() + compound.GetMass();
		double density = mass / volume;

		compoundBody.AddChildBody(make_shared<CBody>(parallelepiped));
		compoundBody.AddChildBody(make_shared<CBody>(sphere));
		compoundBody.AddChildBody(make_shared<CBody>(cone));
		compoundBody.AddChildBody(make_shared<CBody>(cylinder));
		compoundBody.AddChildBody(make_shared<CBody>(compound));

		CHECK(compoundBody.AddChildBody(make_shared<CBody>(compoundBody)) == false); // самого в себя добавить нельзя

		CHECK(static_cast<const CBody*>(&compound)); //объемное тело

		cout << compoundBody.GetDensity() << ' ' << density;
		CHECK(IsEqualDouble(compoundBody.GetDensity(), density)); //плотность совпадает

		CHECK(IsEqualDouble(compoundBody.GetVolume(), volume)); //объем совпадает

		CHECK(IsEqualDouble(compoundBody.GetMass(), mass)); //масса совпадает
	}
}


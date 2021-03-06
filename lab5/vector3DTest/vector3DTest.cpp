#include "stdafx.h"
#include "../vector3D/CVector3D.h"

bool IsEqualDouble(double d1, double d2)
{
	const double E = 0.1;
	return abs(d1 - d2) < E;
}

TEST_CASE("vector3D test")
{
	SECTION("инициализация переменной")
	{
		CVector3D v3;
		CHECK((IsEqualDouble(v3.x, 0) && IsEqualDouble(v3.y, 0) && IsEqualDouble(v3.z, 0)) == true);

		CVector3D vector3(1, 1, 2);
		CHECK((IsEqualDouble(vector3.x, 1) && IsEqualDouble(vector3.y, 1) && IsEqualDouble(vector3.z, 2)) == true);
	}

	SECTION("проверка на равенство векторов")
	{
		CVector3D v1(1, 2, 3);
		CVector3D v2(1, 2, 3);
		CVector3D v3(2, 2, 3);

		CHECK((v1 == v2 && v2 == v1) == true);
		CHECK((v1 != v3 && v3 != v1) == true);
	}

	SECTION("проверка на бинарные операции")
	{
		CVector3D v1(1, 2, 3);
		CVector3D v2(4, 4, 4);

		CHECK((v1 + v2) == CVector3D(5, 6, 7));
		CHECK((v1 - v2) == CVector3D(-3, -2, -1));
		CHECK(((v1 * 2) == CVector3D(2, 4, 6) && (2 * v1) == CVector3D(2, 4, 6)) == true);
		CHECK((v1 / 2) == CVector3D(0.5, 1, 1.5));
	}

	SECTION("проверка на короткие версии бинарных операции")
	{
		CVector3D v1(1, 2, 3);
		CVector3D v2(4, 4, 4);

		v1 += v2;
		CHECK(v1 == CVector3D(5, 6, 7));
		v1 -= v2;
		CHECK(v1 == CVector3D(1, 2, 3));
		v1 *= 2;
		CHECK(v1 == CVector3D(2, 4, 6));
		v1 /= 2;
		CHECK(v1 == CVector3D(1, 2, 3));
	}

	SECTION("унарный + -")
	{
		CVector3D v2(4, 4, 4);
		v2 = -v2;
		CHECK(v2 == CVector3D(-4, -4, -4));
		v2 = +v2;
		CHECK(v2 == CVector3D(-4, -4, -4));
	}

	SECTION("операции << >>")
	{
		std::string str = "1 2 3";
		std::istringstream iStream(str);
		CVector3D v1;
		iStream >> v1;
		CHECK(v1 == CVector3D(1, 2, 3));

		std::ostringstream oStream;
		oStream << v1;
		CHECK(oStream.str() == "1, 2, 3");

		//проверка на неудачное считывание данных
		str = "4 4";
		std::istringstream wrongIStream(str);
		wrongIStream >> v1;
		CHECK(v1 == CVector3D(1, 2, 3));
	}
	
	SECTION("Проверка встроенных методов класса")
	{
		CVector3D v2(4, 4, 4);
		double expectedLength = 6.928;
		
		CHECK(IsEqualDouble(v2.GetLength(), expectedLength));

		v2.Normalize();
		CHECK(v2.GetLength() == 1);

		CVector3D v1(1, 2, 3);
		CVector3D v3(2, 2, 2);
		CHECK(CVector3D::DotProduct(v1, v3) == 12);
		CHECK(CVector3D::CrossProduct(v1, v3) == CVector3D(-2, 4, -2));
		CHECK((CVector3D::Normalize(v3).GetLength() == 1 && v3 == CVector3D(2, 2, 2)));
	}

	SECTION("Проверка деления на 0")
	{
		CVector3D v1(1, 2, 3);
		try
		{
			v1 = v1 / 0;
		}
		catch(std::invalid_argument ex)
		{
			CHECK(static_cast<const std::string&>("Divizion by zero") == ex.what());
		}

		try
		{
			v1 /= 0;
		}
		catch (std::invalid_argument ex)
		{
			CHECK(static_cast<const std::string&>("Divizion by zero") == ex.what());
		}
	}
}
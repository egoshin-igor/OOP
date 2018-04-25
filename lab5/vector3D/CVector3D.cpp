#include "stdafx.h"
#include "CVector3D.h"
#include <cmath>

const double E = 0.001;

CVector3D::CVector3D()
{
	x = 0;
	y = 0;
	z = 0;
}

CVector3D::CVector3D(double x0, double y0, double z0)
	: x(x0)
	, y(y0)
	, z(z0)
{
}

double CVector3D::GetLength()const
{
	return std::sqrt(x * x + y * y + z * z);
}

void CVector3D::Normalize()
{
	auto invLength = 1 / GetLength();
	x *= invLength;
	y *= invLength;
	z *= invLength;
}

double CVector3D::DotProduct(CVector3D const& v1, CVector3D const& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

CVector3D CVector3D::CrossProduct(CVector3D const& v1, CVector3D const& v2)
{
	auto vX = v1.y * v2.z - v1.z * v2.y;
	auto vY = -(v1.x * v2.z - v1.z * v2.x);
	auto vZ = v1.x * v2.y - v1.y * v2.x;

	return CVector3D(vX, vY, vZ);
}

CVector3D const CVector3D::operator +(CVector3D const& vector3)const
{
	return CVector3D(x + vector3.x, y + vector3.y, z + vector3.z);
}

CVector3D const CVector3D::operator -(CVector3D const& vector3)const
{
	return CVector3D(x - vector3.x, y - vector3.y, z - vector3.z);
}

CVector3D const CVector3D::operator *(double scalar) const
{
	return CVector3D(x * scalar, y * scalar, z * scalar);
}

CVector3D const operator *(double scalar, CVector3D const& vector3)
{
	return CVector3D(scalar * vector3.x, scalar * vector3.y, scalar * vector3.z);
}

CVector3D const CVector3D::operator /(double scalar) const
{
	return CVector3D(x / scalar, y / scalar, z / scalar);
}
CVector3D const CVector3D::operator -() const
{
	return CVector3D(-x, -y, -z);
}

CVector3D const CVector3D::operator +() const
{
	return *this;
}

CVector3D const CVector3D::operator +=(CVector3D const& vector3)
{
	x += vector3.x;
	y += vector3.y;
	z += vector3.z;

	return *this;
}

CVector3D const CVector3D::operator -=(CVector3D const& vector3)
{
	x -= vector3.x;
	y -= vector3.y;
	z -= vector3.z;

	return *this;
}

CVector3D const CVector3D::operator *=(double scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

CVector3D const CVector3D::operator /=(double scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;

	return *this;
}

bool CVector3D::operator ==(CVector3D const& vector3) const
{
	auto equalX = abs(x - vector3.x) < E;
	auto equalY = abs(y - vector3.y) < E;
	auto equalZ = abs(z - vector3.z) < E;
	return equalX && equalY && equalZ;
}

bool CVector3D::operator !=(CVector3D const& vector3) const
{
	return !(*this == vector3);
}

std::ostream& operator <<(std::ostream& stream, CVector3D const& vector3)
{
	stream << vector3.x << ", " << vector3.y << ", " << vector3.z;
	return stream;
}

std::istream& operator >>(std::istream& stream, CVector3D& vector3)
{
	double vX, vY, vZ;

	if (stream >> vX && stream >> vY && stream >> vZ)
	{
		vector3 = CVector3D(vX, vY, vZ);
	}
	else
	{
		stream.setstate(std::ios_base::failbit | stream.rdstate());
	}

	return stream;
}
#include "stdafx.h"
#include "../bodies/Cbody.h"
#include "../bodies/CCompound.h"
#include "../bodies/CCone.h"
#include "../bodies/CCylinder.h"
#include "../bodies/CParallelepiped.h"
#include "../bodies/CSphere.h"

TEST_CASE("Bodies test")
{
	SECTION("CSphereTest")
	{

	}

	SECTION("CCylinderTest")
	{

	}

	SECTION("CConeTest")
	{

	}

	SECTION("CParallelepipedTest")
	{

	}

	SECTION("CCompoundTest")
	{
		CCompound compoundBody;
		CParallelepiped parallelepiped(10, 10, 10, 10);
		CSphere s(10, 10);
		compoundBody.AddChildBody(s);
		CHECK(std::abs(compoundBody.GetVolume() - s.GetVolume()) < 0.001);
	}
}


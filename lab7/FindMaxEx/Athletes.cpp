#include "stdafx.h"
#include "Athletes.h"
#include "FindMaxEx.h"


bool Athletes::GetPersonWithMaxWeight(std::vector<Athlete> const& people, Athlete& person)
{
	if (FindMax(people, person, LessWeight()))
	{
		return true;
	}
	return false;
}

bool Athletes::GetPersonWithMaxHeight(std::vector<Athlete> const& people, Athlete& person)
{
	if (FindMax(people, person, LessHeight()))
	{
		return true;
	}
	return false;
}

void Athletes::PrintPersonInfo(Athlete const& person)
{
	std::cout << "Full name: " << person.fullName << '\n';
	std::cout << "Weight: " << person.weight << '\n';
	std::cout << "Height: " << person.height << '\n';
}

Athletes::~Athletes()
{
}

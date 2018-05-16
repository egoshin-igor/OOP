#include "stdafx.h"
#include "Athletes.h"


template < typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.size() == 0)
	{
		return false;
	}
	maxValue = arr[0];
	for (size_t i = 1; i < arr.size(); ++i)
	{
		if (less(maxValue, arr[i]))
		{
			maxValue = arr[i];
		}
	}
	return true;
}

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

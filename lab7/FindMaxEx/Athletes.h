#pragma once
struct Athlete
{
	std::string fullName;
	double height;
	double weight;
};

struct LessWeight
{
	bool operator() (Athlete const& a1, Athlete const& a2) const
	{
		return a1.weight < a2.weight;
	}
};

struct LessHeight
{
	bool operator() (Athlete a1, Athlete a2) const
	{
		return a1.height < a2.height;
	}
};
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <iostream>

class Athletes
{
public:
	static bool GetPersonWithMaxHeight(std::vector<Athlete> const& people, Athlete& person);
	static bool GetPersonWithMaxWeight(std::vector<Athlete> const& people, Athlete& person);
	static void PrintPersonInfo(Athlete const& person);
	~Athletes();
private:
	std::vector<Athlete> m_people;
};


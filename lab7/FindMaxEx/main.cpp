#include "stdafx.h"
#include "Athletes.h"

using namespace std;

int main()
{
	vector<Athlete> people{ { "A.Smith", 160, 70 },{ "B.Smith", 180, 50 },{ "C.Smith", 165, 60 } };
	Athlete person;
	if (Athletes::GetPersonWithMaxHeight(people, person))
	{
		cout << "Person with max height:\n";
		Athletes::PrintPersonInfo(person);
		cout << "\n";
	}

	if (Athletes::GetPersonWithMaxWeight(people, person))
	{
		cout << "Person with max weight:\n";
		Athletes::PrintPersonInfo(person);
		cout << '\n';
	}
	return 0;
}




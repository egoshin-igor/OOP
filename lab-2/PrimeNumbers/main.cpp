#include "stdafx.h"
#include "GeneratePrimeNumbersSet.h"


using namespace std;

const long MAX_VALUE = 100000000;
const int MIN_VALUE = 2;

bool StringToInt(const char* str, int& i);
void PrintIntSet(ostream& output, set<int> set);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Upper bound value must be printed in params\n";
		return 1;
	}
	int  upperBound = 0;
	if (!StringToInt(argv[1], upperBound))
	{
		cout << "First argument's not a number\n";
		return 1;
	}
	if (upperBound > MAX_VALUE || upperBound < MIN_VALUE)
	{
		cout << "First argument value is higher or lower then a bounds of prime numbers\n";
		cout << "Print this value in range 2 - 100000000\n";
		return 1;
	}
	set<int> primeNumbersSet = GeneratePrimeNumbersSet(upperBound);
	//cout << static_cast<int>(primeNumbersSet.size());
	PrintIntSet(cout, primeNumbersSet);
	return 0;
}

bool StringToInt(const char* str, int& i)
{
	char* pLastChar = NULL;
	i = strtol(str, &pLastChar, 10);
	return !(*str == '\0' || *pLastChar != '\0');
}

void PrintIntSet(ostream& output, set<int> set)
{
	for (auto value : set)
	{
		output << value << " ";
	}
	if (!set.empty())
	{
		output << '\b' << '\n';
	}
}
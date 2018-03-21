#include "stdafx.h"
#include <set>

using namespace std;

set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < 1)
	{
		return {};
	}
	vector<bool> isPrimeNumbers(upperBound + 1, true);
	set<int> primeNumbersSet;
	for (size_t i = 2; i <= static_cast<size_t>(upperBound); ++i)
	{
		if (isPrimeNumbers[i])
		{
			primeNumbersSet.insert(i);
			if (i * i <= static_cast<size_t>(upperBound))
			{
				for (size_t j = i + i; j <= static_cast<size_t>(upperBound); j += i)
				{
					isPrimeNumbers[j] = false;
				}
			}
		}
	}
	return primeNumbersSet;
}
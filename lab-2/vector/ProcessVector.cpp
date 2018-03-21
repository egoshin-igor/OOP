#include "stdafx.h"
#include "ProcessVector.h"
#include <algorithm>
#include <vector>

using namespace std;

void MulEachElement(vector<double>& numbers, double value)
{
	for (size_t i = 0; i < numbers.size(); ++i)
	{
		numbers[i] *= value;
	}
}

void ProcessVector(vector<double>& numbers)
{
	if (!numbers.empty())
	{
		double min = *(min_element(numbers.begin(), numbers.end()));
		MulEachElement(numbers, min);
	}
}

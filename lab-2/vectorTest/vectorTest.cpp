#include "stdafx.h"
#include <vector>
#include "../vector/ProcessVector.h"
using namespace std;
const double E = 0.0001;

bool IsEqualVectors(vector<double>& vector1, vector<double>& vector2)
{
	size_t firstVectorLength = vector1.size();
	size_t secondVectorLength = vector2.size();
	if (firstVectorLength != secondVectorLength)
	{
		return false;
	}
	for (size_t i = 0; i < firstVectorLength; ++i)
	{
		if (fabs(vector1[i] - vector2[i]) > E)
		{
			return false;
		}
	}
	return true;
}

vector<double> numbers1 = {};
vector<double> numbers1Result = {};

vector<double> numbers2 = {2};
vector<double> numbers2Result = {4};

vector<double> numbers3 = { 2.2, 4, 8, 16 };
vector<double> numbers3Result = { 4.84, 8.8, 17.6, 35.2 };

vector<double> numbers4 = {0, 4, 8, 16 };
vector<double> numbers4Result = {0, 0, 0, 0 };

vector<double> numbers5 = { -1, 4, 8, 16 };
vector<double> numbers5Result = { 1, -4, -8, -16 };

TEST_CASE("ProcessVector test")
{
	ProcessVector(numbers1);
	CHECK(IsEqualVectors(numbers1, numbers1Result));
	ProcessVector(numbers2);
	CHECK(IsEqualVectors(numbers2, numbers2Result));
	ProcessVector(numbers3);
	CHECK(IsEqualVectors(numbers3, numbers3Result));
	ProcessVector(numbers4);
	CHECK(IsEqualVectors(numbers4, numbers4Result));
	ProcessVector(numbers5);
	CHECK(IsEqualVectors(numbers5, numbers5Result));
}
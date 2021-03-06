#include "stdafx.h"
#include "ProcessVector.h"

using namespace std;

void FillMatrix(vector<double>& numbers);
void PrintNumbers(ostream& output, vector<double>& numbers);

int main()
{
	vector<double> numbers;
	FillMatrix(numbers);
	ProcessVector(numbers);
	sort(numbers.begin(), numbers.end());
	PrintNumbers(cout, numbers);
	return 0;
}

void FillMatrix(vector<double>& numbers)
{
	double value = 0;
	while (cin >> value)
	{
		numbers.push_back(value);
	}
}

void PrintNumbers(ostream& output, vector<double>& numbers)
{
	for (auto elem : numbers)
	{
		output << elem << " ";
	}
	if (!numbers.empty())
	{
		output << '\b' << '\n';
	}
}
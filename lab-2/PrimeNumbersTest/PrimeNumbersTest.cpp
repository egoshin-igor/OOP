#include "stdafx.h"
#include <set>
#include "../PrimeNumbers/GeneratePrimeNumbersSet.h"

using namespace std;

set<int> primeNumbersFor1{};
set<int> primeNumbersFor2{ 2 };
set<int> primeNumbersFor13{ 2, 3, 5, 7, 11, 13 };
set<int> primeNumbersFor100{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53,59, 61, 67, 71, 73, 79, 83, 89, 97 };
size_t primeNumbersAmountFor10000 = 1229;
size_t primeNumbersAmountFor100000000 = 5761455;

TEST_CASE("PrimeNumbers test")
{
	CHECK(GeneratePrimeNumbersSet(1) == primeNumbersFor1);
	CHECK(GeneratePrimeNumbersSet(2) == primeNumbersFor2);
	CHECK(GeneratePrimeNumbersSet(13) == primeNumbersFor13);
	CHECK(GeneratePrimeNumbersSet(10000).size() == primeNumbersAmountFor10000);
	CHECK(GeneratePrimeNumbersSet(100000000).size() == primeNumbersAmountFor100000000);
}

/*
Разработайте приложение flipbyte.exe, выполняющее изменение порядка следования двоичных битов в 8-битовом целом числе (байте),
заданном в десятичном представлении, на противоположный.
*/
#include "stdafx.h"

using namespace std;

const int WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE = 1;
const int NOT_A_NUMBER_ERROR_CODE = 2;
const int NOT_IN_NEED_RANGE_ERROR_CODE = 3;

bool CorrectnessOfArgumentsAmount(int argc);
bool StringToInt(const char* str, int& byte);
bool IntToByte(int i, uint8_t& byte);
uint8_t FlipByte(uint8_t i);

int main(int argc, char* argv[])
{
	if (!CorrectnessOfArgumentsAmount(argc))
		return WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE;
	uint8_t byte;;
	int i;
	if (!StringToInt(argv[1], i))
		return NOT_A_NUMBER_ERROR_CODE;
	if (!IntToByte(i, byte))
		return NOT_IN_NEED_RANGE_ERROR_CODE;
	uint8_t flipByte;
	flipByte = FlipByte(byte);
	cout << int(flipByte) << "\n";
	return 0;
}

bool StringToInt(const char* str, int& i)
{
	char* pLastChar = NULL;
	i = strtol(str, &pLastChar, 10);
	if (*str == '\0' || *pLastChar != '\0')
	{
		cout << "First argument's not a number\n";
		return false;
	}
	return true;
}

bool IntToByte(int i, uint8_t& byte)
{
	if (i < 0 || i > 255)
	{
		cout << "First argument must be a number in range 0 - 255\n";
		return false;
	}
	byte = i;
	return true;
}

bool CorrectnessOfArgumentsAmount(int argc)
{
	if (argc != 2)
	{
		cout << "Type only one argument in this format:\n";
		cout << "flipbyte.exe <input byte>\n";
		return false;
	}
	return true;
}

uint8_t FlipByte(uint8_t i)
{
	const uint8_t BIT_CHECKER = 1 << 7;
	uint8_t flipByte = 0;
	for (int bitIndex = 7; bitIndex >= 0; i <<= 1, --bitIndex)
		flipByte |= (i & BIT_CHECKER) >> bitIndex;
	return flipByte;
}

/*
Разработайте приложение flipbyte.exe, выполняющее изменение порядка следования двоичных битов в 8-битовом целом числе (байте),
заданном в десятичном представлении, на противоположный.
*/
#include "stdafx.h"

using namespace std;

const int WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE = 1;
const int NOT_A_NUMBER_ERROR_CODE = 2;
const int NOT_IN_NEED_RANGE_ERROR_CODE = 3;

const int REQUIRED_NUMBER_OF_ARGUMENTS = 1;

bool StringToInt(const char* str, int& i);
bool IntToByte(int i, uint8_t& byte);
uint8_t FlipByte(uint8_t i);

int main(int argc, char* argv[])
{
	uint8_t byte;
	int i;
	if (argc != REQUIRED_NUMBER_OF_ARGUMENTS + 1)
	{
		cout << "Type only one argument in this format:\n";
		cout << "flipbyte.exe <input byte>\n";
		return WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE;
	}
	if (!StringToInt(argv[1], i))
	{
		cout << "First argument's not a number\n";
		return NOT_A_NUMBER_ERROR_CODE;
	}
	if (!IntToByte(i, byte))
	{
		cout << "First argument must be a number in range 0 - 255\n";
		return NOT_IN_NEED_RANGE_ERROR_CODE;
	}

	uint8_t flipByte;
	flipByte = FlipByte(byte);
	cout << static_cast<int>(flipByte) << "\n";
	return 0;
}

bool StringToInt(const char* str, int& i)
{
	char* pLastChar = NULL;
	i = strtol(str, &pLastChar, 10);
	return !(*str == '\0' || *pLastChar != '\0');
}

bool IntToByte(int i, uint8_t& byte)
{
	if (i < 0 || i > 255)
		return false;
	byte = static_cast<uint8_t>(i);
	return true;
}

uint8_t FlipByte(uint8_t i)
{
	const uint8_t BIT_CHECKER = 1 << (8 - 1);
	uint8_t flipByte = 0;
	for (int bitIndex = (8 - 1); bitIndex >= 0; i <<= 1, --bitIndex)
		flipByte |= (i & BIT_CHECKER) >> bitIndex;
	return flipByte;
}

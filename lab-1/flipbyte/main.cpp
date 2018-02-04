#include "stdafx.h"

using namespace std;

const int WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE = 1;
const int NOT_A_NUMBER_ERROR_CODE = 2;
const int NOT_IN_NEED_RANGE_ERROR_CODE = 3;

void CheckArgumentsAmount(int argc);
int StringToInt(const char* str);
unsigned char StringToUnsignedChar(const char* str);
void flipByte(unsigned char& i);

int main(int argc, char* argv[])
{
	CheckArgumentsAmount(argc);
	unsigned char i = StringToUnsignedChar(argv[1]);
	flipByte(i);
	cout << (int)i << "\n";
	return 0;
}

int StringToInt(const char* str)
{
	char* pLastChar = NULL;
	int param = strtol(str, &pLastChar, 10);
	if (*str == '\0' || *pLastChar != '\0')
	{
		cout << "First argument's not a number\n";
		exit(NOT_A_NUMBER_ERROR_CODE);
	}
	return param;
}

unsigned char StringToUnsignedChar(const char* str)
{
	int i = StringToInt(str);
	if (i < 0 || i > 255)
	{
		cout << "First argument must be a number in range 0 - 255\n";
		exit(NOT_IN_NEED_RANGE_ERROR_CODE);
	}
	return (unsigned char)i;
}

void CheckArgumentsAmount(int argc)
{
	if (argc != 2)
	{
		cout << "Type only one argument in this format:\n";
		cout << "flipbyte.exe <input byte>\n";
		exit(WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE);
	}
}

void flipByte(unsigned char& i)
{
	unsigned char tempI = 0;
	for (int iterator = 7; iterator >= 0; i <<= 1, --iterator)
	{
		tempI |= (i & 128) >> iterator;
	}
	i = tempI;
}
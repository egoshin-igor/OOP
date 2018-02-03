#include "stdafx.h"

using namespace std;

const int FEW_ARGUMENTS_ERROR_CODE = 1, MANY_ARGUMENTS_ERROR_CODE = 2;
const int NOT_OPENED_IN_FILE_ERROR_CODE = 3, NOT_OPENED_OUT_FILE_ERROR_CODE = 4;
const int SEARCH_STRING_LENGTH_ERROR_CODE = 5;

void CheckArgumentsAmount(int argc);
template <typename fileType>
void OpenFileAndCheckIt(fileType &file, const char *fileName, const int errorCode);
void CheckSearchStringLength(char* searchStr);

int main(int argc, char* argv[])
{
	CheckArgumentsAmount(argc);
	const char* inFileName = argv[1];
	const char* outFileName = argv[2];
	ifstream inFile;
	OpenFileAndCheckIt(inFile, inFileName, NOT_OPENED_IN_FILE_ERROR_CODE);
	ofstream outFile;
	OpenFileAndCheckIt(outFile, outFileName, NOT_OPENED_OUT_FILE_ERROR_CODE);
	CheckSearchStringLength(argv[3]);
	return 0;
}

void CheckArgumentsAmount(int argc)
{
	if (argc < 5)
	{
		cout << "There are not enough arguments\nPrint 4 arguments in this format:\n";
		cout << "replace.exe <input file> <output file> <search string> <replace string>\n";
		exit(FEW_ARGUMENTS_ERROR_CODE);
	}
	else if (argc > 5)
	{
		cout << "There are many arguments\nPrint 4 arguments in this format:\n";
		cout << "replace.exe <input file> <output file> <search string> <replace string>\n";
		exit(MANY_ARGUMENTS_ERROR_CODE);
	}
}

template <typename fileType>
void OpenFileAndCheckIt(fileType &file, const char *fileName, const int errorCode)
{
	file.open(fileName);
	if (!file.is_open())
	{
		cout << "File " << fileName << " is not open\n";
		exit(errorCode);
	}
}

void CheckSearchStringLength(char* searchStr)
{
	if (searchStr == "")
	{
		cout << "The third argument can't be an empty string";
		exit(SEARCH_STRING_LENGTH_ERROR_CODE);
	}
}
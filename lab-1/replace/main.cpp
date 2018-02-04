#include "stdafx.h"

using namespace std;

const int FEW_ARGUMENTS_ERROR_CODE = 1, MANY_ARGUMENTS_ERROR_CODE = 2;
const int NOT_OPENED_IN_FILE_ERROR_CODE = 3, NOT_OPENED_OUT_FILE_ERROR_CODE = 4;
const int SEARCH_STRING_LENGTH_ERROR_CODE = 5;

void CheckArgumentsAmount(int argc);
template <typename fileType>
void OpenFileAndCheckIt(fileType& file, string fileName, const int errorCode);
void CheckSearchStringLength(string searchStr);
void TextProcessing(ifstream& inFile, ofstream& outFile, string searchString, string replaceString);
// подфункции TextProcessing
bool findSearchString(string searchString, string lineOfFile, int& firstIndex, int& lastIndex);
string ReplacePartOfString(string originalString, string replaceString, int firstIndex, int lastIndex);
// подфункции TextProcessing

int main(int argc, char* argv[])
{
	CheckArgumentsAmount(argc);
	string inFileName = argv[1];
	string outFileName = argv[2];
	ifstream inFile;
	OpenFileAndCheckIt(inFile, inFileName, NOT_OPENED_IN_FILE_ERROR_CODE);
	ofstream outFile;
	OpenFileAndCheckIt(outFile, outFileName, NOT_OPENED_OUT_FILE_ERROR_CODE);
	string searchString = argv[3];
	string replaceString = argv[4];
	CheckSearchStringLength(searchString);
	TextProcessing(inFile, outFile, searchString, replaceString);
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
void OpenFileAndCheckIt(fileType& file, string fileName, const int errorCode)
{
	file.open(fileName);
	if (!file.is_open())
	{
		cout << "The File " << fileName << " can't be opened\n";
		exit(errorCode);
	}
}

void CheckSearchStringLength(string searchStr)
{
	if (searchStr == "")
	{
		cout << "The third argument can't be an empty string";
		exit(SEARCH_STRING_LENGTH_ERROR_CODE);
	}
}

void TextProcessing(ifstream& inFile, ofstream& outFile, string searchString, string replaceString)
{
	string lineOfFile;
	bool searchStringIsFound = false;
	int firstIndex = 0, lastIndex = 0;
	while (getline(inFile, lineOfFile))
	{
		if (!searchStringIsFound)
		{
			searchStringIsFound = findSearchString(searchString, lineOfFile, firstIndex, lastIndex);
			if (searchStringIsFound)
				lineOfFile = ReplacePartOfString(lineOfFile, replaceString, firstIndex, lastIndex);
		}
		outFile << lineOfFile;
		if (!inFile.eof())
			outFile << "\n";
	}
}

bool findSearchString(string searchString, string lineOfFile, int& firstIndex, int& lastIndex)
{
	int searchStringIndex;
	int searchStringLength = searchString.length();
	int lineOfFileLength = lineOfFile.length();
	for (int i = 0; i < lineOfFileLength; ++i)
	{
		if (lineOfFile[i] == searchString[0])
		{
			searchStringIndex = 0;
			firstIndex = i;
			for (int k = i; k < lineOfFileLength; ++k)
			{
				if (lineOfFile[k] == searchString[searchStringIndex])
				{
					++searchStringIndex;
					if (searchStringIndex == searchStringLength)
					{
						lastIndex = k;
						return true;
					}
				}
				else
					break;
			}
		}
	}
	return false;
}

string ReplacePartOfString(string originalString, string replaceString, int firstIndex, int lastIndex)
{
	string changedString = "";
	int originalStringLength = originalString.length();
	for (int i = 0; i < firstIndex; ++i)
		changedString += originalString[i];
	changedString += replaceString;
	for (int i = lastIndex + 1; i < originalStringLength; ++i)
		changedString += originalString[i];
	return changedString;
}
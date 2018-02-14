/*
Разработайте программу replace.exe, выполняющую замену подстроки в текстовом файле на другую строку,
и записывающей результат в выходной файл (отличный от входного).
*/
#include "stdafx.h"
#pragma optimize( "", off )

using namespace std;

const int WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE = 1;
const int NOT_OPENED_IN_FILE_ERROR_CODE = 2;
const int NOT_OPENED_OUT_FILE_ERROR_CODE = 3;
const int SEARCH_STRING_LENGTH_ERROR_CODE = 4;

const int REQUIRED_NUMBER_OF_ARGUMENTS = 4;

void ReplaceNeedSubstringsInTheText(ifstream& inFile, ofstream& outFile, const string searchString, const string replaceString);
// подфункция TextProcessing
void ReplaceSubstringsInTheString(string& str, const string searchString, const string replaceString);
// подфункция TextProcessing

int main(int argc, char* argv[])
{
	if (argc != REQUIRED_NUMBER_OF_ARGUMENTS + 1)
	{
		cout << "Type only 4 arguments in this format:\n";
		cout << "replace.exe <input file> <output file> <search string> <replace string>\n";
		return WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE;
	}

	const string inFileName = argv[1];
	const string outFileName = argv[2];
	ifstream inFile(inFileName);
	ofstream outFile(outFileName);
	if (!inFile.is_open())
	{
		cout << "The File " << inFileName << " can't be opened\n";
		return NOT_OPENED_IN_FILE_ERROR_CODE;
	}
	if (!outFile.is_open())
	{
		cout << "The File " << outFileName << " can't be opened\n";
		return NOT_OPENED_OUT_FILE_ERROR_CODE;
	}

	const string searchString = argv[3];
	const string replaceString = argv[4];
	if (searchString == "")
	{
		cout << "The third argument can't be an empty string\n";
		return SEARCH_STRING_LENGTH_ERROR_CODE;
	}
	ReplaceNeedSubstringsInTheText(inFile, outFile, searchString, replaceString);

	if (!outFile.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}
	inFile.close();
	outFile.close();
	return 0;
}

void ReplaceNeedSubstringsInTheText(ifstream& inFile, ofstream& outFile, const string searchString, const string replaceString)
{
	string lineOfFile;
	while (getline(inFile, lineOfFile))
	{
		ReplaceSubstringsInTheString(lineOfFile, searchString, replaceString);
		outFile << lineOfFile;
		if (!inFile.eof())
			outFile << "\n";
	}
}

void ReplaceSubstringsInTheString(string& str, const string searchString, const string replaceString)
{
	size_t lastIndex = 0;
	size_t newIndex;
	string tempString = "";
	while ((newIndex = str.find(searchString, lastIndex)) != string::npos)
	{
		tempString.append(str, lastIndex, newIndex - lastIndex);
		tempString += replaceString;
		lastIndex = newIndex + searchString.length();
	}
	tempString += str.substr(lastIndex);
	str = tempString;
}

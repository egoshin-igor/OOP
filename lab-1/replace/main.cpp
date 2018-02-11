﻿/*
Разработайте программу replace.exe, выполняющую замену подстроки в текстовом файле на другую строку,
и записывающей результат в выходной файл (отличный от входного).
*/
#include "stdafx.h"

using namespace std;

const int WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE = 1;
const int NOT_OPENED_IN_FILE_ERROR_CODE = 2;
const int NOT_OPENED_OUT_FILE_ERROR_CODE = 3;
const int SEARCH_STRING_LENGTH_ERROR_CODE = 4;

const int REQUIRED_NUMBER_OF_ARGUMENTS = 4;

void TextProcessing(ifstream& inFile, ofstream& outFile, string searchString, string replaceString);
// подфункция TextProcessing
void ReplaceSubstrings(string& str, const string searchString, string replaceString);
// подфункция TextProcessing

int main(int argc, char* argv[])
{
	if (argc != REQUIRED_NUMBER_OF_ARGUMENTS + 1)
	{
		cout << "Type only one argument in this format:\n";
		cout << "replace.exe <input file> <output file> <search string> <replace string>\n";
		return WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE;
	}

	string inFileName = argv[1];
	string outFileName = argv[2];
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

	string searchString = argv[3];
	string replaceString = argv[4];
	if (searchString == "")
	{
		cout << "The third argument can't be an empty string\n";
		return SEARCH_STRING_LENGTH_ERROR_CODE;
	}
	TextProcessing(inFile, outFile, searchString, replaceString);
	return 0;
}

void TextProcessing(ifstream& inFile, ofstream& outFile, string searchString, string replaceString)
{
	string lineOfFile;
	bool searchStringIsFound = false;
	int firstIndex = 0, lastIndex = 0;
	while (getline(inFile, lineOfFile))
	{
		ReplaceSubstrings(lineOfFile, searchString, replaceString);
		outFile << lineOfFile;
		if (!inFile.eof())
			outFile << "\n";
	}
}

void ReplaceSubstrings(string& str, string searchString, string replaceString)
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

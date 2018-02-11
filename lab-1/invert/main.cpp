#include "stdafx.h"

using namespace std;

const int LINES = 3, COLUMNS = 3;
const int WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE = 1;
const int NOT_OPENED_IN_FILE_ERROR_CODE = 2;
const int INCORRECT_FILE_CONTENT = 3;
const int NOT_EXIST_INVERSE_MATRIX_ERROR_CODE = 4;

const int REQUIRED_NUMBER_OF_ARGUMENTS = 1;

bool FillMatrix(float matrix[LINES][COLUMNS], ifstream& inFile);
void CheckAvailabilityOfInverseMatrix(float matrix[LINES][COLUMNS], float& determinate);
float Determinate2x2(float matrix[LINES][COLUMNS], int lineNumber, int columnNumber);
void TransposeTheMatrix(float matrix[LINES][COLUMNS]);
void InverseMatrix(float matrix[LINES][COLUMNS], float inverseMatrix[LINES][COLUMNS], float determinate);
void showMatrix(float matrix[LINES][COLUMNS]);

int main(int argc, char* argv[])
{
	if (argc != REQUIRED_NUMBER_OF_ARGUMENTS + 1)
	{
		cout << "Type only one argument in this format:\n";
		cout << "invert.exe <matrix file>\n";
		return WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE;
	}

	char* inFileName = argv[1];
	ifstream inFile(inFileName);
	if (!inFile.is_open())
	{
		cout << "The File " << inFileName << " can't be opened\n";
		return NOT_OPENED_IN_FILE_ERROR_CODE;
	}

	float matrix[LINES][COLUMNS];
	float inverseMatrix[LINES][COLUMNS];
	float determinate = 0;
	if (!FillMatrix(matrix, inFile))
	{
		cout << "Incorrect input file content. Print matrix 3x3\n";
		return INCORRECT_FILE_CONTENT;
	}
	CheckAvailabilityOfInverseMatrix(matrix, determinate);
	TransposeTheMatrix(matrix);
	InverseMatrix(matrix, inverseMatrix, determinate);
	showMatrix(inverseMatrix);
	return 0;
}

bool FillMatrix(float matrix[LINES][COLUMNS], ifstream& inFile)
{
	int i = 0;
	int j = 0;
	int digitsAmount = 0;
	while (inFile >> matrix[i][j])
	{
		++j;
		++digitsAmount;
		if (j == COLUMNS)
		{
			j = 0;
			++i;
		}
		if (i == 4)
			--i;
	}
	return digitsAmount == (LINES * COLUMNS);

}

void CheckAvailabilityOfInverseMatrix(float matrix[LINES][COLUMNS], float& determinate)
{
	for (int j = 0; j < LINES; ++j)
		if (j != 1)
			determinate += matrix[0][j] * Determinate2x2(matrix, 0, j);
		else
			determinate += -matrix[0][j] * Determinate2x2(matrix, 0, j);
	if (determinate == 0)
	{
		cout << "Determinate = 0. The inverse matrix does not exist\n";
		exit(NOT_EXIST_INVERSE_MATRIX_ERROR_CODE);
	}
}

float Determinate2x2(float matrix[LINES][COLUMNS], int lineNumber, int columnNumber)
{
	float tempMatrix[2][2];
	int i = 0, j = 0;
	for (int k = 0; k < LINES; ++k)
		for (int l = 0; l < COLUMNS; ++l)
			if (k != lineNumber && l != columnNumber)
			{
				tempMatrix[i][j] = matrix[k][l];
				++j;
				if (j == 2)
				{
					++i;
					j = 0;
				}

			}
	float determinate;
	determinate = tempMatrix[0][0] * tempMatrix[1][1] - tempMatrix[1][0] * tempMatrix[0][1];
	if (determinate == -0)
		determinate = 0;
	return determinate;
}

void TransposeTheMatrix(float matrix[LINES][COLUMNS])
{
	int k = 1;
	float tempI;
	for (int i = 0; i < LINES - 1; ++i)
	{
		for (int j = k; j < COLUMNS; ++j)
		{
			tempI = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = tempI;
		}
		++k;
	}
}

void InverseMatrix(float matrix[LINES][COLUMNS], float inverseMatrix[LINES][COLUMNS], float determinate)
{
	determinate = 1 / determinate;
	bool plus = true;
	for (int i = 0; i < LINES; ++i)
		for (int j = 0; j < COLUMNS; ++j)
			if (plus)
			{
				inverseMatrix[i][j] = Determinate2x2(matrix, i, j) * determinate;
				plus = false;
			}
			else
			{
				inverseMatrix[i][j] = (-Determinate2x2(matrix, i, j)) * determinate;
				if (inverseMatrix[i][j] == -0)
					inverseMatrix[i][j] = 0;
				plus = true;
			}
}

void showMatrix(float matrix[LINES][COLUMNS])
{
	for (int i = 0; i < LINES; cout << "\n", ++i)
		for (int j = 0; j < COLUMNS; ++j)
			if (j != COLUMNS - 1)
				cout << round(matrix[i][j] * 1000) / 1000 << "\t";
			else
				cout << round(matrix[i][j] * 1000) / 1000;
}
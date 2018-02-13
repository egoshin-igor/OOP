#include "stdafx.h"

using namespace std;

const int LINES = 3, COLUMNS = 3;
const int WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE = 1;
const int NOT_OPENED_IN_FILE_ERROR_CODE = 2;
const int NOT_EXIST_INVERSE_MATRIX_ERROR_CODE = 3;

const int REQUIRED_NUMBER_OF_ARGUMENTS = 1;

void FillMatrix(ifstream& inFile, float matrix[LINES][COLUMNS]);
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
	FillMatrix(inFile, matrix);
	CheckAvailabilityOfInverseMatrix(matrix, determinate);
	if (determinate == 0)
	{
		cout << "Determinate = 0. The inverse matrix does not exist\n";
		return NOT_EXIST_INVERSE_MATRIX_ERROR_CODE;
	}
	TransposeTheMatrix(matrix);
	InverseMatrix(matrix, inverseMatrix, determinate);
	showMatrix(inverseMatrix);
	return 0;
}

void FillMatrix(ifstream& inFile, float matrix[LINES][COLUMNS])
{
	for (size_t i = 0; i < LINES; ++i)
		for (size_t j = 0; j < COLUMNS; ++j)
			inFile >> matrix[i][j];
}

void CheckAvailabilityOfInverseMatrix(float matrix[LINES][COLUMNS], float& determinate)
{
	const size_t MINUS_POSITION_IN_MATRIX = 1;
	for (size_t j = 0; j < LINES; ++j)
		if (j != MINUS_POSITION_IN_MATRIX)
			determinate += matrix[0][j] * Determinate2x2(matrix, 0, j);
		else
			determinate += -matrix[0][j] * Determinate2x2(matrix, 0, j);
}

float Determinate2x2(float matrix[LINES][COLUMNS], int lineNumber, int columnNumber)
{
	float tempMatrix[2][2];
	int i = 0, j = 0;
	for (size_t k = 0; k < LINES; ++k)
		for (size_t l = 0; l < COLUMNS; ++l)
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
	return tempMatrix[0][0] * tempMatrix[1][1] - tempMatrix[1][0] * tempMatrix[0][1];
}

void TransposeTheMatrix(float matrix[LINES][COLUMNS])
{
	int k = 1;
	float tempI;
	for (size_t i = 0; i < LINES - 1; ++i)
	{
		for (size_t j = k; j < COLUMNS; ++j)
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
	bool plusPositionInMatrix = true;
	for (size_t i = 0; i < LINES; ++i)
		for (size_t j = 0; j < COLUMNS; ++j)
			if (plusPositionInMatrix)
			{
				inverseMatrix[i][j] = Determinate2x2(matrix, i, j) * determinate;
				plusPositionInMatrix = false;
			}
			else
			{
				inverseMatrix[i][j] = (-Determinate2x2(matrix, i, j)) * determinate;
				if (inverseMatrix[i][j] == -0)
					inverseMatrix[i][j] = 0;
				plusPositionInMatrix = true;
			}
}

void showMatrix(float matrix[LINES][COLUMNS])
{
	for (size_t i = 0; i < LINES; cout << "\n", ++i)
		for (size_t j = 0; j < COLUMNS; ++j)
			if (j != COLUMNS - 1)
				cout << round(matrix[i][j] * 1000) / 1000 << "\t";
			else
				cout << round(matrix[i][j] * 1000) / 1000;
}
/*
Разработайте приложение invert.exe, выполняющее инвертирование матрицы 3*3, т.е. нахождение обратной матрицы и
выводящее коэффициенты результирующей матрицы в стандартный поток вывода.
*/
#include "stdafx.h"

using namespace std;

const int LINES = 3, COLUMNS = 3;
const int WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE = 1;
const int NOT_OPENED_IN_FILE_ERROR_CODE = 2;
const int NOT_EXIST_INVERSE_MATRIX_ERROR_CODE = 3;

const int REQUIRED_NUMBER_OF_ARGUMENTS = 1;

void FillMatrix(istream& inFile, float matrix[LINES][COLUMNS]);
bool isExistInverseMatrix(float matrix[LINES][COLUMNS], float& determinant);
float Get3x3MatrixMinor(float matrix[LINES][COLUMNS], size_t lineNumber, size_t columnNumber);
void TransposeTheMatrix(float matrix[LINES][COLUMNS]);
void InverseMatrix(float matrix[LINES][COLUMNS], float inverseMatrix[LINES][COLUMNS], float determinant);
void ShowMatrix(ostream& output, float matrix[LINES][COLUMNS]);

int main(int argc, char* argv[])
{
	if (argc != REQUIRED_NUMBER_OF_ARGUMENTS + 1)
	{
		cout << "Type only one argument in this format:\n";
		cout << "invert.exe <matrix file>\n";
		return WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE;
	}

	const char* inFileName = argv[1];
	ifstream inFile(inFileName);
	if (!inFile.is_open())
	{
		cout << "The File " << inFileName << " can't be opened\n";
		return NOT_OPENED_IN_FILE_ERROR_CODE;
	}

	float matrix[LINES][COLUMNS];
	float inverseMatrix[LINES][COLUMNS];
	float determinant = 0;
	FillMatrix(inFile, matrix);
	if (!isExistInverseMatrix(matrix, determinant))
	{
		cout << "determinant = 0. The inverse matrix does not exist\n";
		return NOT_EXIST_INVERSE_MATRIX_ERROR_CODE;
	}
	TransposeTheMatrix(matrix);
	InverseMatrix(matrix, inverseMatrix, determinant);
	ShowMatrix(cout, inverseMatrix);
	return 0;
}

void FillMatrix(istream& inFile, float matrix[LINES][COLUMNS])
{
	for (size_t i = 0; i < LINES; ++i)
	{
		for (size_t j = 0; j < COLUMNS; ++j)
		{
			inFile >> matrix[i][j];
		}
	}
		
}

bool isExistInverseMatrix(float matrix[LINES][COLUMNS], float& determinant)
{
	int minorSign;
	for (size_t j = 0; j < LINES; ++j)
	{
		minorSign = static_cast<int>(pow(-1, j));
		determinant += matrix[0][j] * Get3x3MatrixMinor(matrix, 0, j) * minorSign;
	}
	return abs(determinant) == 0 ? false : true;
}

float Get3x3MatrixMinor(float matrix[LINES][COLUMNS], size_t lineNumber, size_t columnNumber)
{
	float tempMatrix[LINES - 1][COLUMNS - 1];
	size_t i = 0;
	size_t j = 0;
	for (size_t k = 0; k < LINES; ++k)
	{
		for (size_t l = 0; l < COLUMNS; ++l)
		{
			if (k != lineNumber && l != columnNumber)
			{
				tempMatrix[i][j] = matrix[k][l];
				++j;
				if (j == COLUMNS - 1)
				{
					++i;
					j = 0;
				}
			}
		}
	}
	return tempMatrix[0][0] * tempMatrix[1][1] - tempMatrix[1][0] * tempMatrix[0][1];
}

void TransposeTheMatrix(float matrix[LINES][COLUMNS])
{
	size_t swapPosition = 1;
	float tempI;
	for (size_t i = 0; i < LINES - 1; ++i)
	{
		for (size_t j = swapPosition; j < COLUMNS; ++j)
		{
			tempI = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = tempI;
		}
		++swapPosition;
	}
}

void InverseMatrix(float matrix[LINES][COLUMNS], float inverseMatrix[LINES][COLUMNS], float determinant)
{
	determinant = 1 / determinant;
	int minorSign;
	for (size_t i = 0; i < LINES; ++i)
	{
		for (size_t j = 0; j < COLUMNS; ++j)
		{
			minorSign = static_cast<int>(pow(-1, i + j));
			inverseMatrix[i][j] = Get3x3MatrixMinor(matrix, i, j) * determinant * minorSign;
			if (inverseMatrix[i][j] == -0)
			{
				inverseMatrix[i][j] = 0;
			}
		}
	}
}

void ShowMatrix(ostream& output, float matrix[LINES][COLUMNS])
{
	for (size_t i = 0; i < LINES; cout << "\n", ++i)
	{
		for (size_t j = 0; j < COLUMNS; ++j)
		{
			if (j != COLUMNS - 1)
			{
				output << round(matrix[i][j] * 1000) / 1000 << "\t";

			}
			else
			{
				output << round(matrix[i][j] * 1000) / 1000;
			}
		}
	}
		
}
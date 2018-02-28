#include "stdafx.h"

const int WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE = 1;
const int NOT_OPENED_IN_FILE_ERROR_CODE = 2;
const int NOT_OPENED_OUT_FILE_ERROR_CODE = 3;
const int WRONG_AMOUNT_OF_POSITIONS_ERROR_CODE = 4;

const int REQUIRED_NUMBER_OF_ARGUMENTS = 2;
const int LINES = 101, COLUMNS = 100;
const int MATRIX_ELEMS = LINES * COLUMNS;

const int WALL = 0;
const int START_POSITION = 1;
const int FREE_SPACE = MATRIX_ELEMS;
const int FINISH_POSITION = MATRIX_ELEMS + 1;
const int LABYRINTH_END = MATRIX_ELEMS + 2;
const int POINT = MATRIX_ELEMS + 3;
const int NOT_FOUND_POSITION = MATRIX_ELEMS + 4;


struct MatrixPosition
{
	size_t i;
	size_t j;
};

void FillMatrix(int matrix[LINES][COLUMNS], int digit);
bool WriteLabyrinthInMatrix(std::istream& input, int matrix[LINES][COLUMNS]);
bool FindPathToFinish(int matrix[LINES][COLUMNS], MatrixPosition& currPosition);
void DrawPath(int matrix[LINES][COLUMNS], MatrixPosition& finishPosition);
void PrintLabyrinth(std::ostream& output, int matrix[LINES][COLUMNS]);

MatrixPosition FindPosition(int matrix[LINES][COLUMNS], int position);
void PushCoordsInQ(int i, int j, int currentStep, std::queue<MatrixPosition>& q, int matrix[LINES][COLUMNS]);
size_t GetLastWallPositon(int matrix[LINES][COLUMNS], size_t i);
MatrixPosition GetMinNearestCoord(int matrix[LINES][COLUMNS], MatrixPosition& currPosition);
void minValue(int matrix[LINES][COLUMNS], MatrixPosition& matrixCoord, int i, int j, int& min);
void StepBackAlongThePath(int matrix[LINES][COLUMNS], MatrixPosition& currPosition, int i, int j, int value);

int main(int argc, char* argv[])
{
	if (argc != REQUIRED_NUMBER_OF_ARGUMENTS + 1)
	{
		std::cout << "Type only 2 arguments in this format:\n";
		std::cout << "labyrinth.exe <input file> <output file>\n";
		return WRONG_AMOUNT_OF_ARGUMENTS_ERROR_CODE;
	}

	const std::string inFileName = argv[1];
	const std::string outFileName = argv[2];

	std::ifstream inFile(inFileName);
	if (!inFile.is_open())
	{
		std::cout << "The File " << inFileName << " can't be opened\n";
		return NOT_OPENED_IN_FILE_ERROR_CODE;
	}

	std::ofstream outFile(outFileName);
	if (!outFile.is_open())
	{
		std::cout << "The File " << outFileName << " can't be opened\n";
		return NOT_OPENED_OUT_FILE_ERROR_CODE;
	}

	int labyrinthMatrix[LINES][COLUMNS];
	FillMatrix(labyrinthMatrix, FREE_SPACE);
	if (!WriteLabyrinthInMatrix(inFile, labyrinthMatrix))
	{
		std::cout << "The labyrinth has wrong amount of start and|or finish position\n";
		std::cout << "The labyrinth must has one start and finish position\n";
		return WRONG_AMOUNT_OF_POSITIONS_ERROR_CODE;
	}

	MatrixPosition currPosition = FindPosition(labyrinthMatrix, START_POSITION);
	if (FindPathToFinish(labyrinthMatrix, currPosition))
	{
		DrawPath(labyrinthMatrix, currPosition);
	}
	PrintLabyrinth(outFile, labyrinthMatrix);
	return 0;
}

void FillMatrix(int matrix[LINES][COLUMNS], int digit)
{
	for (size_t i = 0; i < LINES; ++i)
	{
		for (size_t j = 0; j < COLUMNS; ++j)
		{
			matrix[i][j] = digit;
		}
	}
}

bool WriteLabyrinthInMatrix(std::istream& input, int matrix[LINES][COLUMNS])
{
	int startAndFinishPositions = 0;
	std::string line;
	int i = 0;
	while (std::getline(input, line))
	{
		size_t lineLength = line.length();
		for (size_t j = 0; j < lineLength; ++j)
		{
			switch (line[j])
			{
			case ' ':
				matrix[i][j] = FREE_SPACE;
				break;
			case '#':
				matrix[i][j] = WALL;
				break;
			case 'A':
				++startAndFinishPositions;
				matrix[i][j] = START_POSITION;
				break;
			case 'B':
				++startAndFinishPositions;
				matrix[i][j] = FINISH_POSITION;
				break;
			default:
				break;
			}
			if (startAndFinishPositions > 2)
			{
				return false;
			}
		}
		++i;
	}
	matrix[i][0] = LABYRINTH_END;
	return true;
}

size_t GetLastWallPositon(int matrix[LINES][COLUMNS], size_t i)
{
	for (size_t j = COLUMNS - 1; j > 0; --j)
	{
		if (matrix[i][j] == WALL)
		{
			return j;
		}
	}
	return 0;
}

void PrintLabyrinth(std::ostream& output, int matrix[LINES][COLUMNS])
{
	for (size_t i = 0; i < LINES; ++i)
	{
		size_t lastWallPosition = GetLastWallPositon(matrix, i);
		if (matrix[i][0] == LABYRINTH_END)
		{
			break;
		}
		if (lastWallPosition != 0)
		{
			for (size_t j = 0; j <= lastWallPosition; ++j)
			{
				switch (matrix[i][j])
				{
				case WALL:
					output << '#';
					break;
				case START_POSITION:
					output << 'A';
					break;
				case FINISH_POSITION:
					output << 'B';
					break;
				case POINT:
					output << '.';
					break;
				default:
					output <<' ';
					break;
				}
			}
		}
		if (matrix[i][0] != LABYRINTH_END)
		{
			output << std::endl;
		}
	}
}

MatrixPosition FindPosition(int matrix[LINES][COLUMNS], int position)
{
	MatrixPosition coordinates;
	coordinates.j = NOT_FOUND_POSITION;
	coordinates.i = NOT_FOUND_POSITION;
	for (size_t i = 0; i < LINES; ++i)
	{
		for (size_t j = 0; j < COLUMNS; ++j)
		{
			if (matrix[i][j] == position)
			{
				coordinates.i = i;
				coordinates.j = j;
				return coordinates;
			}
		}
	}
	return coordinates;
}

bool FindPathToFinish(int matrix[LINES][COLUMNS], MatrixPosition& currPosition)
{
	std::queue<MatrixPosition> coordsQ;
	coordsQ.push(currPosition);
	int i = currPosition.i;
	int j = currPosition.j;
	while (!coordsQ.empty() && matrix[currPosition.i][currPosition.j] != FINISH_POSITION)
	{
		currPosition = coordsQ.front();
		size_t i = currPosition.i;
		size_t j = currPosition.j;
		coordsQ.pop();
		int currentStep = matrix[i][j];
		PushCoordsInQ(i + 1, j, currentStep, coordsQ, matrix);
		PushCoordsInQ(i - 1, j, currentStep, coordsQ, matrix);
		PushCoordsInQ(i, j + 1, currentStep, coordsQ, matrix);
		PushCoordsInQ(i, j - 1, currentStep, coordsQ, matrix);
	}
	return matrix[currPosition.i][currPosition.j] == FINISH_POSITION ? true : false;
}

void PushCoordsInQ(int i, int j, int currentStep, std::queue<MatrixPosition>& q, int matrix[LINES][COLUMNS])
{
	MatrixPosition nearestPosition;
	nearestPosition.i = i;
	nearestPosition.j = j;
	if (matrix[i][j] == FINISH_POSITION)
	{
		q.push(nearestPosition);
	}
	if (matrix[i][j] == FREE_SPACE)
	{
		matrix[i][j] = currentStep + 1;
		q.push(nearestPosition);
	}
}

void DrawPath(int matrix[LINES][COLUMNS], MatrixPosition& currPosition)
{
	currPosition = GetMinNearestCoord(matrix, currPosition);
	int i = currPosition.i;
	int j = currPosition.j;
	while (matrix[i][j] != START_POSITION)
	{
		StepBackAlongThePath(matrix, currPosition, i + 1, j, matrix[i][j]);
		StepBackAlongThePath(matrix, currPosition, i - 1, j, matrix[i][j]);
		StepBackAlongThePath(matrix, currPosition, i, j + 1, matrix[i][j]);
		StepBackAlongThePath(matrix, currPosition, i, j - 1, matrix[i][j]);
		matrix[i][j] = POINT;
		i = currPosition.i;
		j = currPosition.j;
	}
}

void StepBackAlongThePath(int matrix[LINES][COLUMNS], MatrixPosition& currPosition, int i, int j, int value)
{
	if (matrix[i][j] == value - 1)
	{
		currPosition.i = i;
		currPosition.j = j;
	}
}

MatrixPosition GetMinNearestCoord(int matrix[LINES][COLUMNS], MatrixPosition& currPosition)
{
	int i = currPosition.i;
	int j = currPosition.j;
	int min = MATRIX_ELEMS;
	MatrixPosition matrixCoord;
	minValue(matrix, matrixCoord, i + 1, j, min);
	minValue(matrix, matrixCoord, i - 1, j, min);
	minValue(matrix, matrixCoord, i, j + 1, min);
	minValue(matrix, matrixCoord, i, j - 1, min);
	return matrixCoord;
}

void minValue(int matrix[LINES][COLUMNS], MatrixPosition& matrixCoord, int i, int j, int& min)
{
	if (matrix[i][j] != WALL and matrix[i][j] < min)
	{
		matrixCoord.i = i;
		matrixCoord.j = j;
		min = matrix[i][j];
	}
}
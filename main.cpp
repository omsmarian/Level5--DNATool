/*********************************************************************
 * @file   main.cpp
 * @brief  22.08 EDA
 * Main module, responsible of the output
 * and creating Needleman-Wunsch matrix
 *
 *
 * @author Grupo 4: Mariano Oms, Adriel Schmunck
 *********************************************************************/
#include <fstream>
#include <string>
#include "utility.h"


using namespace std;

int main(int argc, char* argv[])
{

	string genome1 = extraccion(argv[1]);
	string genome2 = extraccion(argv[2]);

	vector<uint8_t> directions;

	vector<int> matrix(genome1.size() * genome2.size());

	int diagonalVal, upVal, leftVal;

	/*
	* Needleman-Wunsch algorithm complexity is M*N,
	* M and N being the lenght of the strings
	*/

	for (int j = 1; j < genome2.size(); j++)
	{
		matrix[j * genome1.size()] = -j;
		for (int i = 1; i < genome1.size(); i++)
		{
			matrix[i] = -i;
			upVal = matrix[i + (j - 1) * genome1.size()] - 1;

			leftVal = matrix[i + j * genome1.size() - 1] - 1;

			diagonalVal = (matrix[i - 1 + (j - 1) * genome1.size()]);
			if (genome1[i] == genome2[j])
				diagonalVal++;
			else
				diagonalVal--;

			if (upVal >= leftVal && upVal >= diagonalVal)
			{
				matrix[i + j * genome1.size()] = upVal;
				directions.push_back(UP);
			}
			else if (leftVal >= upVal && leftVal >= diagonalVal)
			{
				matrix[i + j * genome1.size()] = leftVal;
				directions.push_back(LEFT);
			}
			else
			{
				matrix[i + j * genome1.size()] = diagonalVal;
				directions.push_back(DIAGONAL);
			}
		}
	}

	int score = matrix.back();

	forward_list<uint8_t> optimalPath = writtingGuide(&matrix, &directions,
		genome2.size(), genome1.size());


	//file header
	cout << "------------------------------------------------------------" << endl;
	cout << "ALIGNED SEQUENCES" << endl << endl << "FILE 1: " << argv[1] <<
		endl << "FILE 2: " << argv[2] << endl;
	cout << endl << "SCORE = " << score << endl;
	cout << "------------------------------------------------------------" << endl << endl;

	string alignment;
	genome1.erase(0, 1);
	genome2.erase(0, 1);
	int index = 0;
	for (auto i : optimalPath)
	{
		if (i == MATCH)
			alignment += "|";
		else if (i == MISMATCH)
			alignment += "*";
		else if (i == UP_GAP)
		{
			genome1.insert(index, "-");
			alignment += " ";
		}
		else if (i == LEFT_GAP)
		{
			genome2.insert(index, "-");
			alignment += " ";
		}
		index++;
	}

	for (int a = 0; a <= (index / 60); a++)
	{
		cout << genome1.substr(a * 60, 60);
		cout << endl;
		cout << alignment.substr(a * 60, 60);
		cout << endl;
		cout << genome2.substr(a * 60, 60);
		cout << endl << endl;
	}

	return 0;
}

/**********************************************************************
 * @file   utility.cpp
 * @brief  22.08 EDA 
 * This file contains the extraccion and writtingGuide functions
 * 
 * @author Grupo 4: Mariano Oms, Adriel Schmunck
 *********************************************************************/
#include "utility.h"

/**
 * @brief Reads and extracts the usefull 
 * characters of the file
 * 
 * @param path of the file to read (string)
 * @return string compose of usefull characters (string)
 */
string extraccion(string namefile)
{
	ifstream file(namefile);

	string word;
	string output;
	char letter;
	bool originFound = false;
	bool endFound = false;

	while ((!originFound) && (file >> word))
	{
		if (word == "ORIGIN")
			originFound = true;
	}

	while ((!endFound) && (file >> letter))
	{
		if ((letter == 'a') || (letter == 'c') || (letter == 'g') || (letter == 't'))
			output += letter;
		else if (letter == '/')
			endFound = true;
	}

	output.insert(0, " ");
	return output;
}

/**
* @brief Goes through the Needleman-Wunsch matrix
* and directrions matrix, to create an optimal path
* 
 * @param pointer to Needlan-Wunsch matrix (vector<int>*)
 * @param pointer to directions matrix (vector<uint8_t>*)
 * @param height of Needlan-Wunsch matrix (int)
 * @param width of Needlan-Wunsch matrix (int)
 * 
 * @return optimal path (foward_list)
 */
forward_list<uint8_t> writtingGuide(vector<int>* number, vector<uint8_t>* directions
	, size_t height, size_t wide)
{
	forward_list<uint8_t> list;
	bool outOfMatrix = false;
	int n = directions->size() - 1;
	int nextValue;

	while (!outOfMatrix)
	{
		if (directions->data()[n] == LEFT)
		{
			n--;
			list.push_front(LEFT_GAP);
		}
		else if (directions->data()[n] == UP)
		{
			n -= wide - 1;
			list.push_front(UP_GAP);
		}
		else if (directions->data()[n] == DIAGONAL)
		{
			int value = n + (n / (wide - 1)) + wide + 1;	// index scaling
			n -= wide;
			if (n < 0)
			{
				outOfMatrix = true;
				nextValue = n + wide + 1 - ((-n) / (wide - 1));
			}
			else
				nextValue = n + wide + 1 + (n / (wide - 1));
			if (number->data()[value] >= number->data()[nextValue])
				list.push_front(MATCH);
			else if (number->data()[value] <= number->data()[nextValue])
				list.push_front(MISMATCH);
		}
	}
	while (nextValue > 0)
	{
		if (nextValue < wide && nextValue > 0)
		{
			list.push_front(LEFT_GAP);
			nextValue--;
		}

		for (int j = height - 1; j > 0; j--)
		{
			if (nextValue == (j * wide))
				list.push_front(UP_GAP);

			nextValue -= wide;
		}
	}

	return list;
}

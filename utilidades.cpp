#include "utilidades.h"

string extraccion(string namefile)
{
	ifstream file("../../../resources/test/" + namefile + ".txt", ios::in);
	string word;
	string ADN;
	char letter;
	bool originFound = false;
	bool endFound = false;

	while ((!originFound) && ( file >> word))
	{
		if (word == "ORIGIN")
			originFound = true;
	}

	while ((!endFound) && (file >> letter))
	{
		if ((letter == 'a') || (letter == 'c') || (letter == 'g') || (letter == 't'))
			ADN += letter;
		else if (letter == '/')
			endFound = true;
	}

	return ADN;
}

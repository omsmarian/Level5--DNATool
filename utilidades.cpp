#include "utilidades.h"

string extraccion(string namefile)
{
	ifstream file("../../../resources/test/" + namefile + ".txt", ios::in);

	if (file.is_open())
		cout << namefile + ".txt abierto" << endl;
	else
		cout << namefile + ".txt no existe" << endl;


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

	ADN.insert(0," ");
	return ADN;
}


forward_list<int> writtingGuide(vector<int>* number, vector<int>* directions ,size_t altura , size_t ancho)
{
												// arriba = 0, izq = 1, diagonal = 3
	forward_list<int> list;						// match = 0, mismatch = 1, gap arriba = 3, gap izquierda = 4

	bool ceroFound = false;
	int n = directions->size() - 1;
	int nextValue;
	while (!ceroFound)
	{
		if (directions->data()[n] == 1)
		{
			n--;
			list.push_front(4);
		}
		else if (directions->data()[n] == 0)
		{
			n -= ancho - 1;
			list.push_front(3);
		}
		else if (directions->data()[n] == 3)
		{
			int value = n + (n /( ancho - 1)) + ancho + 1;
			n -= ancho;
			if (n < 0)
			{
				ceroFound = true;
				nextValue = n + ancho + 1 - ((-n) / (ancho - 1));
			}
			else
				nextValue = n + ancho + 1 + (n / (ancho - 1));
			if (number->data()[value] >= number->data()[nextValue])
				list.push_front(0);
			else if (number->data()[value] <= number->data()[nextValue])
				list.push_front(1);
		}
	}
	while (nextValue > 0)
	{
		if (nextValue < ancho && nextValue > 0)			// chequea la fila superior
		{
			list.push_front(4);
			nextValue--;
		}

		for (int j = altura - 1; j > 0; j--)
		{
			if (nextValue == (j * ancho))				// chequea la primera columna
				list.push_front(3);

			nextValue -= ancho;
		}
	}

	return list;
}

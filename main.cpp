#include <fstream>
#include <string>
#include <sstream>
#include "utilidades.h"


using namespace std;

int main()
{

	cout << "INGRESE NOMBRE DE LOS ARCHIVOS A COMPARAR SIN .txt" << endl;
	string namefile1;
	string namefile2;

	cout << "FILE 1: ";

	getline(cin, namefile1);

	cout << "FILE 2: ";

	getline(cin, namefile2);

	string genome1 = extraccion(namefile1);
	string genome2 = extraccion(namefile2);

	vector<uint8_t> direcciones;											// arriba = 0, izq = 1, diagonal = 3

	vector<int> matriz(genome1.size() * genome2.size());				//genome1 horizontal, genome2 vertical

	int diagonalVal, arribaVal, izqVal;
	for (int j = 1; j < genome2.size(); j++)
	{
		matriz[j * genome1.size()] = -j;
		for (int i = 1; i < genome1.size(); i++)
		{
			matriz[i] = -i;
			arribaVal = matriz[i + (j - 1) * genome1.size()] - 1;

			izqVal = matriz[i + j * genome1.size() - 1] - 1;

			diagonalVal = (matriz[i - 1 + (j - 1) * genome1.size()]);
			if (genome1[i] == genome2[j])
				diagonalVal++;
			else
				diagonalVal--;

			if (arribaVal >= izqVal && arribaVal >= diagonalVal)
			{
				matriz[i + j * genome1.size()] = arribaVal;
				direcciones.push_back(0);
			}
			else if (izqVal >= arribaVal && izqVal >= diagonalVal)
			{
				matriz[i + j * genome1.size()] = izqVal;
				direcciones.push_back(1);
			}
			else
			{
				matriz[i + j * genome1.size()] = diagonalVal;
				direcciones.push_back(3);
			}
		}
	}

	int score = matriz.back();

	forward_list<int> escritura = writtingGuide(&matriz, &direcciones,
		genome2.size(), genome1.size());				// match = 0, mismatch = 1, gap arriba = 3, gap izquierda = 4

	cout << "score = " << score << endl;



	ofstream file("../../../aligment.txt", ios::out);
	if (file.is_open())
		cout << "archivo creado exitosamente" << endl;
	else
		cout << "ocurrio un error" << endl;

	string lineaDelMedio;
	genome1.erase(0, 1);
	genome2.erase(0, 1);
	int index = 0;
	for (auto i : escritura)
	{
		if (i == 0)
			lineaDelMedio += "|";
		if (i == 1)
			lineaDelMedio += "*";
		if (i == 3)
		{
			genome2.insert(index, "-");
			lineaDelMedio += " ";
		}
		if (i == 4)
		{
			genome1.insert(index, "-");
			lineaDelMedio += " ";
		}
		index++;
	}

	int maxLenght = (genome1.length()>genome2.length()? genome1.length() : genome2.length())/60;
	
	for (int a = 0; a <= maxLenght; a++)
	{
		file << genome1.substr(a*60, 60);
		file << endl;
		file << lineaDelMedio.substr(a*60, 60);
		file << endl;
		file << genome2.substr(a*60, 60);
		file << endl << endl;
	}

		
		
	

	return 0;
}

#include <fstream>
#include <string>
#include <sstream>
#include "utilidades.h"


using namespace std;

int main(int argc, char* argv[])
{
	/*string namefile1 = argv[1];
	string namefile2 = argv[2];

	cout << "FILE 1: ";

	getline(cin, namefile1);

	cout << "FILE 2: ";

	getline(cin, namefile2);*/

	string genome1 = extraccion(argv[1]);
	string genome2 = extraccion(argv[2]);

	vector<uint8_t> direcciones;											// arriba = 0, izq = 1, diagonal = 3

	vector<int> matriz(genome1.size() * genome2.size());				//genome1 horizontal, genome2 vertical

	int i = 1;
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

	cout << endl;
	
	int score = matriz.back();

	forward_list<int> escritura = writtingGuide(&matriz, &direcciones,
		genome2.size(), genome1.size());				// match = 0, mismatch = 1, gap arriba = 3, gap izquierda = 4

	/*ofstream file("../../../aligment.txt", ios::out);
	if (file.is_open())
		cout << "archivo creado exitosamente" << endl;
	else
		cout << "ocurrio un error" << endl;*/


	//header del archivo txt de salida
	cout << "------------------------------------------------------------" << endl;
	cout << "ALIGNED SEQUENCES FOR: " << argv[1]  <<
		"  | " << argv[2] << endl;
	cout << endl << "SCORE = " << score << endl;
	cout << "------------------------------------------------------------" << endl << endl;

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
			genome1.insert(index, "-");
			lineaDelMedio += " ";
		}
		if (i == 4)
		{
			genome2.insert(index, "-");
			lineaDelMedio += " ";
		}
		index++;
	}

	for (int a = 0; a <= (index / 60); a++)
	{
		cout << genome1.substr(a * 60, 60);
		cout << endl;
		cout << lineaDelMedio.substr(a * 60, 60);
		cout << endl;
		cout << genome2.substr(a * 60, 60);
		cout << endl << endl;
	}

	return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
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

	vector<int> valores1(genome1.size());
	for (int i = 0; i < valores1.size(); i++)
		valores1[i] = -i;
	vector<int> valores2(genome2.size());
	for (int i = 0; i < valores2.size(); i++)
		valores2[i] = -i;

	vector<int> matriz(genome1.size() * genome2.size());
	for (int i = 0; i < genome2.size(); i++)
	{
		matriz[i] = -i;
		matriz[i * genome1.size()] = -i;
	}

	int diagonalVal, arribaVal, izqVal;
	for (int j = 1; j < genome2.size(); j++)
	{
		for (int i = 1; i < genome1.size(); i++)
		{
			arribaVal = matriz[i + (j -1) * genome1.size()] -1;
			cout << "arriba = " << arribaVal << endl;
			izqVal = matriz[i + j * genome1.size() - 1] -1;
			cout << "izq = " << izqVal << endl;
			diagonalVal = (matriz[i - 1 + (j - 1) * genome1.size()]);
			if (genome1[i] == genome2[j])
				diagonalVal++;
			else
				diagonalVal--;
			cout << "diagonal = " << diagonalVal << endl;
			if (arribaVal >= izqVal && arribaVal >= diagonalVal)
				matriz[i + j * genome1.size()] = arribaVal;
			else if (izqVal >= arribaVal && izqVal >= diagonalVal)
				matriz[i + j * genome1.size()] = izqVal;
			else
				matriz[i + j * genome1.size()] = diagonalVal;
			cout << "[" << j << "]" << "[" << i << "] = " << matriz[i + j * genome1.size()] << endl;


		}
	}


	cout << "matriz:" << endl;
	int i = 0;
	for (int x : matriz)
	{
		cout << x << ",";
		i++;
		if (i == genome1.size())
		{
			cout << endl;
			i = 0;
		}
	}

	return 0;
}

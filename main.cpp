#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <forward_list>
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

	vector<int> direcciones;											// arriba = 0, izq = 1, diagonal = 3

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

	forward_list<int> escritura;				// match = 0, mismatch = 1, gap = 3
	int score = matriz.back();
	bool ceroFound = false;
	int n = direcciones.size() - 1;
	int nextValue;
	while (!ceroFound)
	{
		if (direcciones[n] == 1)
		{
			n--;
			escritura.push_front(3);
		}
		else if (direcciones[n] == 0)
		{
			n -= genome1.size() - 1;
			escritura.push_front(3);
		}
		else if (direcciones[n] == 3)
		{
			int value = n + ((n / (genome1.size() - 1)) + genome1.size() + 1);
			n -= genome1.size();
			if (n < 0)
			{
				ceroFound = true;
				nextValue = n + genome1.size() + 1 - ((-n) / (genome1.size() - 1));
			}
			else
				nextValue = n + genome1.size() + 1 + (n / (genome1.size() - 1));
			if (matriz[value] >= matriz[nextValue])
				escritura.push_front(0);
			else if (matriz[value] <= matriz[nextValue])
				escritura.push_front(1);
		}
	}
	while (nextValue > 0)
	{
		if (nextValue < genome1.size() && nextValue > 0)
		{
			escritura.push_front(3);
			nextValue--;
		}

		for (int j = genome2.size() - 1; j > 0; j--)
		{
			if (nextValue == (j* genome1.size()))
				escritura.push_front(3);
				
			nextValue -= genome1.size();
		}
	}
	
	
	cout << "score = " << score << endl;

	//cout << "matriz:" << endl;
	//int i = 0;
	//for (int x : matriz)
	//{
	//	cout << x << ",";
	//	i++;
	//	if (i == genome1.size())
	//	{
	//		cout << endl;
	//		i = 0;
	//	}
	//}
	//int x = 1;
	//cout << "direcciones: " << endl;
	//for (auto i : direcciones)
	//{
	//	x++;
	//	cout << i << ",";
	//	if (x == genome1.size())
	//	{
	//		cout << endl;
	//		x = 1;
	//	}
	//}
	//cout << endl;

	//cout << "escritura: " << endl;
	//for (auto i : escritura)
	//	cout << i << ",";
	//cout << endl;


	return 0;
}

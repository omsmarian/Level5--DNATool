#include <iostream>
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

	getline(cin,namefile1);

	cout << "FILE 2: ";

	getline(cin,namefile2);

	string genome1 = extraccion(namefile1);
	string genome2 = extraccion(namefile2);

	cout << genome1 << endl;

	cout << genome2 << endl;

	return 0;
}

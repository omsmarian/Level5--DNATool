#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
#include <fstream>
#include <iostream>
#include <forward_list>
#include <vector>

using namespace std;

string extraccion(string namefile);
forward_list<int> writtingGuide(vector<int>* number, vector<int>* directions, size_t altura, size_t ancho);



#endif // !UTILIDADES_H

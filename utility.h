/*********************************************************************
 * @file   utility.h
 * @brief  22.08 EDA 
 * This file contains the extraccion and writtingGuide prototypes
 * 
 * @author Grupo 4: Mariano Oms, Adriel Schmunck
 *********************************************************************/
#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
#include <fstream>
#include <iostream>
#include <forward_list>
#include <vector>

#define UP 0
#define LEFT 1
#define DIAGONAL 2
#define MATCH 3
#define MISMATCH 4
#define UP_GAP 5
#define LEFT_GAP 6

using namespace std;

string extraccion(string namefile);
forward_list<uint8_t> writtingGuide(vector<int>* number, vector<uint8_t>* directions,
	size_t height, size_t wide);



#endif // !UTILIDADES_H

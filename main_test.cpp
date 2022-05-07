#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream fin("/resurces/test/Mystery genome 1 - OV806939.txt");

	if (fin.is_open())
	{
		cout << "hola" << endl;
	}

	return 0;
}

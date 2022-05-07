#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

int main()
{
	string namefile1 = "Mystery genome 1 - OV806939";
	string namefile2 = "Mystery genome 2 - MT345875";

	/*getline(cin,namefile1);
	getline(cin,namefile2);*/

	cout << endl << namefile1 <<  ", " << namefile2 << endl;

	ifstream genome1("../../../resources/test/" + namefile1 + ".txt", ios::in);
	ifstream genome2("../../../resources/test/" + namefile2 + ".txt", ios::in);


	if (genome1.is_open())
	{
		cout << "genome 1 abierto uwu" << endl;
	}

	if (genome2.is_open())
	{
		cout << "genome 2 abierto owo" << endl;
	}

	string word;
	string ADN;
	char letter;
	bool originFound = false;
	bool endFound = false;

	while ((!originFound)&&(genome1 >> word))
	{
		//if (word == "//")
			//endFound = true;

		//else if (originFound)
		//{
		//	if (!((word[0] < '9') && (word[0] > '0')))
		//	{
		//		for (int i = 0; i < word.size(); i++)
		//		{
		//			if (word[i] != 'a' || word[i] != 't' || word[i] != 'c' || word[i] != 'g')
		//				word.erase(word[i]);
		//		}
		//		ADN += word;
		//	}
				
		//}

		if (word == "ORIGIN")
			originFound = true;
	}

	while ((!endFound)&&(genome1 >> letter))
	{
		if ((letter == 'a') || (letter == 'c') || (letter == 'g') || (letter == 't'))
			cout << letter;
		else if (letter == '/')
			endFound = true;
	}



	cout << ADN << endl;

	return 0;
}

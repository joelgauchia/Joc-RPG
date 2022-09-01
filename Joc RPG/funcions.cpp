#include "funcions.h"

using namespace std;

void getOpcio(int& opcio, const string menu_str, const int stream_size) {

	cout << menu_str;

	cout << endl << " - Opcio: ";
	cin >> setw(stream_size) >> opcio;

	while (cin.fail()) {

		system("CLS");
		cout << "Input incorrecte!" << endl;
		system("pause");
		system("CLS");

		cin.clear();
		cin.ignore(INT_MAX, '\n');

		cout << menu_str;

		cout << " - Opcio: ";
		cin >> setw(stream_size) >> opcio;
	}

	cin.clear();
	cin.ignore(INT_MAX, '\n');
}
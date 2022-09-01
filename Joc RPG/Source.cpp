#include <iostream>
#include <Windows.h>
#include "Joc.h"

using namespace std;

int main() {
	
	//system("color 17");
	SetConsoleTitleA("Joc RPG");

	cout << "BENVINGUT AL JOC RPG" << endl << endl;

	Joc joc;
	joc.inicialitzarJoc();

	while (not joc.acabat()) {

		joc.menuJoc();
	}
	return 0;
}
#ifndef JOC_H
#define JOC_H

#include <vector>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Event.h"
#include "dArr.h"
#include "funcions_gui.h"
#include "funcions.h"
//#include "Event.h"

using namespace std;

class Joc {

public:
	Joc();
	//Functions
	void inicialitzarJoc();
	void menuJoc();
	void crearNouPersonatge();
	void levelUpPersonatge();
	void menuPersonatges();
	void guardarPersonatges();
	void carregarPersonatges();
	void seleccionaPersonatge();
	void aventura();
	void descansar();

	//Accessors
	bool acabat() const;

private:
	int _opcio;
	bool _acabat;

	// Control de personatges
	int _jugadorActual;
	vector<Personatge> _personatges;
	string _fitxer;

	//Enemics
	dArr<Enemic> _enemics;
};

#endif // JOC_H
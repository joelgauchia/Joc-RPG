#include "Puzzle.h"
#include <iostream>

using namespace std;

Puzzle::Puzzle(string fitxer) {

	this->_respostaCorrecta = 0;
	this->_nRespostes = 0;

	ifstream in(fitxer);

	string resposta = " ";
	int _respostaCorrecta = 0;

	if (in.is_open()) {
		getline(in, this->_pregunta);
		in >> _nRespostes;
		in.ignore();

		for (int i = 0; i < _nRespostes; i++) {
			getline(in, resposta);
			this->_respostes.push_back(resposta);
		}

		in >> _respostaCorrecta;
		in.ignore();
	}
	else throw("No s'ha pogut obrir el fitxer!");
	in.close();
}

bool Puzzle::respostaCorrecta(const int& resposta_usuari) const {

	bool correcta = false;
	if (this->_respostaCorrecta == resposta_usuari) {
		correcta = true;
	}
	return correcta;
}

string Puzzle::aString() {

	string respostes = "";

	for (int i = 0; i < this->_respostes.size(); i++) {
		respostes += to_string(i) + ": " + this->_respostes[i] + "\n";
	}

	//return this->_pregunta + "\n" + "\n" + respostes + "\n" + to_string(this->_respostaCorrecta) + "\n";

	return this->_pregunta + "\n" + "\n" + respostes + "\n";
}
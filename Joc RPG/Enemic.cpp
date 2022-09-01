#include "Enemic.h"
#include <iostream>

using namespace std;

Enemic::Enemic(int nivell) {

	this->_nivell = nivell;
	this->_vidaMax = rand () % (nivell * 10) + (nivell * 2);
	this->_vida = this->_vidaMax;
	this->_malMin = this->_nivell * 1;
	this->_malMax = this->_nivell * 2;
	this->_percentatgeDrop = rand() % 100 + 1;
	this->_defensa = rand() % _nivell * 4 + 1;
	this->_precisio = rand() % _nivell * 5 + 1;
}

void Enemic::repMal(int mal) {

	this->_vida -= mal;

	if (this->_vida <= 0) {
		this->_vida = 0;
	}
}

int Enemic::fesMal() const {

	return rand() % this->_malMax + this->_malMin;
}

int Enemic::guanyaExp() const {

	return this->_nivell * 100;
}

int Enemic::taxaGemas() const {
	return this->_nivell * 10 + 1;
}


void Enemic::mostraEnemic() const {
	cout << "Nivell: " << this->_nivell;
	cout << " | Vida: " << this->_vida << " / " << this->_vidaMax;
	cout << " | Mal: " << this->_malMin << " - " << this->_malMax;
	cout << " | Defensa: " << this->_defensa;
	cout << " | Precisio: " << this->_precisio;
	cout << " | % Drop: " << this->_percentatgeDrop;
}

string Enemic::mostraNivelliVida() const {
	return "Nivell: " + to_string(this->_nivell) + " - Vida: " + to_string(this->_vida) + "/" + to_string(this->_vidaMax) +
		" - Defensa: " + to_string(this->_defensa) + " - Precisio: " + to_string(this->_precisio) + " - Mal: " + to_string(this->_malMin) + " - " + to_string(this->_malMax);

}
#include "Arma.h"
#include <iostream>

using namespace std;

dArr<string> Arma::noms;

void Arma::initNoms() {

	Arma::noms.afegeix("Cuchillo-Mariposa");
	Arma::noms.afegeix("Franco-Barret");
	Arma::noms.afegeix("Punys-Americans");
	Arma::noms.afegeix("Katana");
	Arma::noms.afegeix("Excalibur");
	Arma::noms.afegeix("Daga-espiral");
}

Arma::Arma() : Item() {
	
	this->_malMin = 0;
	this->_malMax = 0;
}

Arma::Arma(int nivell, int raresa) : Item(_tipusItem::ARMA, nivell, raresa) {
	
	this->_malMax = rand() % nivell * (raresa + 1);
	this->_malMax += (raresa + 1) * 5;
	this->setNom(Arma::noms[rand() % Arma::noms.tamany() - 1]);

	if (raresa == 3) this->_malMax += nivell * 5;
	else if (raresa == 4) this->_malMax += nivell * 10;

	this->_malMin = this->_malMax / 2;
}

Arma::Arma(int malMin, int malMax, string nom, int nivell, int preuCompra, int preuVenta, int raresa) : Item(_tipusItem::ARMA, nom, nivell, preuCompra, preuVenta, raresa) {
	
	this->_malMin = malMin;
	this->_malMax = malMax;
}

Arma* Arma::clone() const {

	return new Arma(*this);
}

void Arma::mostrarArma() const {
	cout << "Mal minim: " << this->_malMin << " Mal maxim: " << this->_malMax << endl;
}

string Arma::toString() const {
	
	string str =
		this->nom() + " | Niv: " + to_string(this->nivell()) + " | Raresa: " + to_string(this->raresa()) + " | Mal: " +
		to_string(this->_malMin) + " - " +
		to_string(this->_malMax);

		return str;
}

string Arma::toStringGuarda() const {

	string str =
		to_string(this->getTipusItem())
		+ " " + this->nom() 
		+ " " + to_string(this->nivell()) 
		+ " " + to_string(this->raresa()) 
		+ " " + to_string(this->preuCompra())
		+ " " + to_string(this->preuVenta())
		+ " " + to_string(this->_malMin) 
		+ " " + to_string(this->_malMax)
		+" ";

	return str;
}
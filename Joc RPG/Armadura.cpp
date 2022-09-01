#include "Armadura.h"
#include <iostream>

using namespace std;

dArr<string> Armadura::noms;

void Armadura::initNoms() {

	Armadura::noms.afegeix("Armadura-diamant");
	Armadura::noms.afegeix("Bro-saver");
	Armadura::noms.afegeix("Balaclava-diabolica");
	Armadura::noms.afegeix("Collons-d'angel");
	Armadura::noms.afegeix("Deez-nuts-salvadores");
	Armadura::noms.afegeix("Barret-de-ferro");
}

Armadura::Armadura() : Item() {

	this->_tipus = -1;
	this->_defensa = 0;
}

Armadura::Armadura(int nivell, int raresa) : Item(_tipusItem::ARMADURA, nivell, raresa){

	this->_defensa = rand() % (nivell * (raresa + 1));
	this->_defensa = (raresa + 1) * 5;
	this->_tipus = rand() % 4;

	switch (this->_tipus) {
		case tipusArmadura::CASC:
			this->tipusStr = "Casc";
			break;
		case tipusArmadura::PECHERA:
			this->tipusStr = "Pechera";
			break;
		case tipusArmadura::PANTALONS:
			this->tipusStr = "Pantalons";
			break;
		case tipusArmadura::BOTES:
			this->tipusStr = "Botes";
			break;
		default:
			this->tipusStr = "INVALID!";
			break;
	}

	this->setNom(Armadura::noms[rand() % Armadura::noms.tamany() - 1]);
	if (raresa == 3) this->_defensa += nivell * 5;
	else if (raresa == 4) this->_defensa += nivell * 10;
}

Armadura::Armadura(int tipus, int defensa, string nom, int nivell, int preuCompra, int preuVenta, int raresa) : Item(_tipusItem::ARMADURA, nom, nivell, preuCompra, preuVenta, raresa) {

	this->_tipus = tipus;
	this->_defensa = defensa;
}

Armadura* Armadura::clone() const {
	return new Armadura(*this);
}

void Armadura::mostrarArmadura() const {
	cout << "Tipus: " << this->_tipus << " Defensa: " << this->_defensa << endl;
}

string Armadura::toString() const {

	string str =
		this->nom() + " | Tipus: " + this->tipusStr + " | Niv: " + to_string(this->nivell()) + " | Raresa: " + to_string(this->raresa()) + " | Defensa: " +
		to_string(this->_defensa);

	return str;
}

string Armadura::toStringGuarda() const {

	string str =
		to_string(this->getTipusItem())
		+ " " + this->nom()
		+ " " + to_string(this->nivell())
		+ " " + to_string(this->raresa())
		+ " " + to_string(this->preuCompra())
		+ " " + to_string(this->preuVenta())
		+ " " + to_string(this->_defensa)
		+ " " + to_string(this->_tipus)
		+" ";

	return str;
}
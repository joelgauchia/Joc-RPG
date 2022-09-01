#include "Personatge.h"
#include <iostream>
#include <iomanip>
using namespace std;

Personatge::Personatge() {

	this->_distanciaViatjada = 0;
	this->_gemas = 0;

	this->_nom = "";
	this->_nivell = 1;
	this->_exp = 0;
	this->_expSeg = 0;
	
	this->_forca = 0;
	this->_vitalitat = 0;
	this->_saviesa = 0;
	this->_astucia = 0;

	this->_vida = 0;
	this->_vidaMax = 0;
	this->_stamina = 0;
	this->_staminaMax = 0;
	this->_dmgMax = 0;
	this->_dmgMin = 0;
	this->_defensa = 0;
	this->_precisio = 0;
	this->_sort = 0;

	this->_stats = 0;
}

Personatge::Personatge(string nom) {

	this->_distanciaViatjada = 0;
	this->_gemas = 100;

	this->_nom = nom;
	this->_nivell = 1;
	this->_exp = 0;

	this->_forca = 5;
	this->_vitalitat = 5;
	this->_saviesa = 5;
	this->_astucia = 5;

	this->_stats = 0;

	actualitzaStats();
}

Personatge::Personatge(string nom, int distanciaViatjada, int gemas, int nivell, int exp, int forca, int vitalitat, int saviesa, int astucia, int vida, int stamina, int stats) {

	this->_distanciaViatjada = distanciaViatjada;
	this->_gemas = gemas;

	this->_nom = nom;
	this->_nivell = nivell;
	if (this->_nivell == 0) this->_nivell = 1;
	this->_exp = exp;
	this->_expSeg = 0;

	this->_forca = forca;
	this->_vitalitat = vitalitat;
	this->_saviesa = saviesa;
	this->_astucia = astucia;

	this->_vida = vida;
	this->_vidaMax = 0;
	this->_stamina = stamina;
	this->_staminaMax = 0;
	this->_dmgMax = 0;
	this->_dmgMin = 0;
	this->_defensa = 0;
	this->_precisio = 0;
	this->_sort = 0;

	this->_stats = stats;

	actualitzaStats();
}

void Personatge::pujaNivell() {

	if (this->_exp >= this->_expSeg) {

		this->_exp -= this->_expSeg;
		this->_nivell++;
		this->_exp = 0;
		this->_expSeg = static_cast<int>((50 / 3) * ((pow(this->_nivell, 3) - 6 * pow(this->_nivell, 2)) + 17 * this->_nivell - 12)) + 100;

		if (this->_stats == -1) this->_stats = 0;
		this->_stats++;

		actualitzaStats();

		cout << endl << "Ara ets nivell " << this->_nivell << "!" << endl;
	}
	else cout << endl << " - EXP insuficient!" << endl << endl;
}

void Personatge::moure() {

	this->_distanciaViatjada++;
}

void Personatge::guanya_exp(const int& exp) {

	this->_exp += exp;
	//pujaNivell();
}

void Personatge::guanya_gemas(const int& gemas) {

	this->_gemas += gemas;
}

void Personatge::equiparItem(unsigned index) {

	if (index < 0 or index > this->_inventari.tamany()) {
		cout << "Cap item valid seleccionat!" << endl << endl;
	}
	else {
		Arma* w = nullptr;
		w = dynamic_cast<Arma*>(&this->_inventari[index]);

		Armadura* a = nullptr;
		a = dynamic_cast<Armadura*>(&this->_inventari[index]);

		// si es arma
		if (w != nullptr) {

			this->_inventari.afegirItem(this->_arma);
			cout << " - S'ha equipat l'arma " << this->_inventari[index].nom() << endl;
			this->_arma = *w;
			this->_inventari.esborraItem(index);
		}
		else if (a != nullptr) {

			switch (a->tipus()) {
			case tipusArmadura::BOTES:
				if (this->_botes.raresa() >= 0) {
					this->_inventari.afegirItem(this->_botes);
					cout << " - S'han afegit les botes " << this->_inventari[index].nom() << endl;
				}
				this->_botes = *a;
				this->_inventari.esborraItem(index);
				break;
			case tipusArmadura::PANTALONS:
				if (this->_pantalons.raresa() >= 0) {
					this->_inventari.afegirItem(this->_pantalons);
					cout << " - S'han afegit els pantalons " << this->_inventari[index].nom() << endl;
				}
				this->_pantalons = *a;
				this->_inventari.esborraItem(index);
				break;
			case tipusArmadura::CASC:
				if (this->_casc.raresa() >= 0) {
					this->_inventari.afegirItem(this->_casc);
					cout << " - S'ha afegit el casc " << this->_inventari[index].nom() << endl;
				}
				this->_casc = *a;
				this->_inventari.esborraItem(index);
				break;
			case tipusArmadura::PECHERA:
				if (this->_pechera.raresa() >= 0) {
					this->_inventari.afegirItem(this->_pechera);
					cout << " - S'ha afegit la pechera " << this->_inventari[index].nom() << endl;
				}
				this->_pechera = *a;
				this->_inventari.esborraItem(index);
				break;
			default:
				cout << "Tipus d'armadura invalid!" << endl;
			}
		}
		else {
			cout << "Error al equipar item, no es ni arma ni armadura!" << endl;
		}
	}
}

void Personatge::borraItem(const int index) {

	if (index < 0 or index >= this->_inventari.tamany())
		cout << "Error, no s'ha pogut eliminar l'item" << endl;
	else
		this->_inventari.esborraItem(index);
}

const Item& Personatge::getItem(const int index) {

	if (index < 0 or index >= this->_inventari.tamany()){
		cout << "Error, no s'ha pogut eliminar l'item" << endl;
		throw("ERROR FORA DE LIMITS");
	}
	return this->_inventari[index];
}

const string Personatge::getBarraMenu() const {

	stringstream ss;

	ss << endl << string(30, '-') << endl;

	ss << " | Nom: " << this->_nom << endl;
	ss << " | Nivell: " << this->_nivell << gui::barraProgres(this->_exp, this->_expSeg, 10, '-', '=') << "(" << this->_exp << "/" << this->_expSeg << ")" << endl;
	ss << " | Punts de stats: " << this->_stats << endl;
	ss << " | HP: " << gui::barraProgres(this->_vida, this->_vidaMax, 10, '-', '=') << this->_vida << "/" << this->_vidaMax << endl;

	ss << string(30, '-') << endl;

	return ss.str();
}

void Personatge::actualitzaStats() {

	this->_expSeg = static_cast<int>((50 / 3) * ((pow(_nivell, 3) - 6 * pow(_nivell, 2)) + 17 * _nivell - 12)) + 100;

	this->_vidaMax = (this->_vitalitat * 5) + (this->_forca) + this->_nivell * 5;
	this->_staminaMax = this->_vitalitat + (this->_forca / 2) + (this->_saviesa / 3);
	this->_stamina = this->_staminaMax;
	this->_dmgMax = this->_forca + 2;
	this->_dmgMin = this->_forca;
	this->_defensa = this->_saviesa + (this->_astucia / 2);
	this->_precisio = (this->_saviesa / 2) + _astucia;
	this->_sort = this->_astucia;

	this->_vida = this->_vidaMax;
}

void Personatge::afegiraStat(int stat, int valor) {

	if (this->_stats < valor) cout << "Error! Punts de stat insuficients!" << endl;
	else {
		switch (stat) {
		case 0:
			this->_forca += valor;
			cout << "S'ha incrementat la forca!" << endl;
			break;
		case 1:
			this->_vitalitat += valor;
			cout << "S'ha incrementat la vitalitat!" << endl;
			break;
		case 2:
			this->_saviesa += valor;
			cout << "S'ha incrementat la saviesa!" << endl;
			break;
		case 3:
			this->_astucia += valor;
			cout << "S'ha incrementat l'astucia!" << endl;
			break;
		default:
			cout << "Stat incorrecte!" << endl;
			break;
		}

		this->_stats -= valor;
		actualitzaStats();
	}
}

void Personatge::mostraPersonatge() {

	cout << "Fitxa del personatge" << endl;
	cout << "========================================" << endl;
	cout << "Nom: " << this->_nom << endl;
	cout << "Nivell: " << this->_nivell << endl;
	cout << "Exp: " << this->_exp << endl;
	cout << "Exp fins al seguent nivell: " << this->_expSeg << endl;
	cout << "Punts de stats: " << this->_stats << endl;
	cout << "========================================" << endl;
	cout << "Forca: " << this->_forca << endl;
	cout << "Vitalitat: " << this->_vitalitat << endl;
	cout << "Saviesa: " << this->_saviesa << endl;
	cout << "Astucia: " << this->_astucia << endl;
	cout << "========================================" << endl;
	cout << "HP: " << this->_vida << "/" << this->_vidaMax << endl;
	cout << "Stamina: " << this->_stamina << "/" << this->_staminaMax << endl;
	cout << "Mal: " << this->_dmgMin << " (+" << this->_arma.malMin() << ")" << " MAX - " << this->_dmgMax << " (+" << this->_arma.malMax() << ")" << endl;
	cout << "Defensa: " << this->_defensa << " (+" << to_string(getDefensaAfegida()) << ")" << endl;
	cout << "Precisio: " << this->_precisio << endl;
	cout << "Sort: " << this->_sort << endl;
	cout << "========================================" << endl;
	cout << "Distancia viatjada: " << this->_distanciaViatjada << endl;
	cout << "Gemas:	" << this->_gemas << endl;
	cout << "========================================" << endl;
	cout << "Arma: " << this->_arma.nom() << 
		" Niv:" << this->_arma.nivell() <<
		" Mal:" << this->_arma.malMin() << " - " << this->_arma.malMax() << endl;
	cout << "Casc armadura: " << this->_casc.nom() <<
		" Niv:" << this->_casc.nivell() <<
		" Def:" << this->_casc.defensa() << endl;
	cout << "Pechera armadura: " << this->_pechera.nom() <<
		" Niv:" << this->_pechera.nivell() <<
		" Def:" << this->_pechera.defensa() << endl;
	cout << "Pantalons armadura: " << this->_pantalons.nom() <<
		" Niv:" << this->_pantalons.nivell() <<
		" Def:" << this->_pantalons.defensa() << endl;
	cout << "Botes armadura: " << this->_botes.nom() <<
		" Niv:" << this->_botes.nivell() <<
		" Def:" << this->_botes.defensa() << endl << endl;
}

string Personatge::aString() const {

	return _nom + " " + to_string(_gemas) + " " + to_string(_nivell) + " " + to_string(_exp) + " " + to_string(_forca) +
		" " + to_string(_vitalitat) + " " + to_string(_saviesa) + " " + to_string(_astucia) + " " + to_string(_vida) + " " + to_string(_stamina) +
		" " + to_string(_stats) +
		" " + this->_arma.toStringGuarda() +
		" " + this->_casc.toStringGuarda() +
		" " + this->_pechera.toStringGuarda() +
		" " + this->_pantalons.toStringGuarda() +
		" " + this->_botes.toStringGuarda();
}

string Personatge::InvaString(bool tenda) {

	string inv;

	for (size_t i = 0; i < this->_inventari.tamany(); i++) {
		if (tenda) {
			inv += to_string(i) + ": " + this->_inventari[i].toString() + "\n" + "- Preu de venta: " + to_string(this->_inventari[i].preuVenta()) + "\n";
		}
		else inv += to_string(i) + ": " + this->_inventari[i].toString() + "\n";
	}
	return inv;
}

string Personatge::InvaStringGuarda() {

	string inv;

	for (size_t i = 0; i < this->_inventari.tamany(); i++) {
		if (this->_inventari[i].getTipusItem() == _tipusItem::ARMA)
			inv += this->_inventari[i].toStringGuarda() + "/n";
	}

	inv += "\n";

	for (size_t i = 0; i < this->_inventari.tamany(); i++) {
		if (this->_inventari[i].getTipusItem() == _tipusItem::ARMADURA)
			inv += this->_inventari[i].toStringGuarda() + "/n";
	}

	return inv;
}

string Personatge::nom() const {
	return this->_nom;
}

int Personatge::nivell() const {
	return this->_nivell;
}

int Personatge::stats() const {
	return this->_stats;
}

bool Personatge::potPujarNivell() const {
	
	bool pot = false;

	if (this->_exp >= this->_expSeg) pot = true;
	return pot;
}

void Personatge::rebreMal(const int mal) {

	this->_vida -= mal;

	if (this->_vida <= 0) this->_vida = 0;
}

void Personatge::reiniciaVida() {

	if (this->_vida == this->_vidaMax) cout << " - La vida ja esta al maxim!" << endl;
	else {
		this->_vida = this->_vidaMax;
		cout << " - S'ha curat la vida de " << this->_nom << endl;
	}
}

void Personatge::pagaGemas(int pagar) {

	this->_gemas -= pagar;
}
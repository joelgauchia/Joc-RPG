#ifndef PERSONATGE_H
#define PERSONATGE_H

#include <string>
#include "Inventari.h"
#include "funcions_gui.h"
#include <sstream>

using namespace std;

class Personatge {

public:
	Personatge();
	Personatge(string nom);
	Personatge(string nom, int distanciaViatjada, int gemas, int nivell, int exp, int forca, int vitalitat, int saviesa, int astucia, int vida, int stamina, int stats);

	void pujaNivell();
	void mostraPersonatge();
	void moure();
	void guanya_exp(const int& exp);
	void guanya_gemas(const int& gemas);
	void actualitzaStats();
	void afegiraStat(int stat, int valor);
	void rebreMal(const int mal);
	void reiniciaVida();
	void pagaGemas(int pagar);
	void afegirItem(const Item& item) { this->_inventari.afegirItem(item); }
	void borraItem(const int index);
	void equiparItem(unsigned index);
	const Item& getItem(const int index);
	const string getBarraMenu() const;

	string aString() const;
	string InvaString(bool tenda = false);
	string InvaStringGuarda();
	string nom() const;
	int nivell() const;
	int stats() const;
	bool potPujarNivell() const;
	
	inline const bool estaViu() { return this->_vida > 0; }
	inline const int getMal() { return rand() % (this->_dmgMax + this->_arma.malMax()) + (this->_dmgMin + this->_arma.malMin()); }
	inline const int getPrecisio() { return this->_precisio; }
	inline const int getDefensa() { return this->_defensa; }
	inline const int getDefensaAfegida() const { return this->_casc.defensa() + this->_pechera.defensa() + this->_pantalons.defensa() + this->_botes.defensa(); }
	inline const int getVidaMax() { return this->_vidaMax; }
	inline const int getVida() { return this->_vida; }
	inline const int getGemas() { return this->_gemas; }
	inline const int getTamanyInventari() { return this->_inventari.tamany(); }
	inline void setArma(Arma arma) { this->_arma = arma; }
	inline void setArmaduraCasc(Armadura casc) { this->_casc = casc; }
	inline void setArmaduraPechera(Armadura pechera) { this->_pechera = pechera; }
	inline void setArmaduraPantalons(Armadura pantalons) { this->_pantalons = pantalons; }
	inline void setArmaduraBotes(Armadura botes) { this->_botes = botes; }

private:

	int _distanciaViatjada;

	Inventari _inventari;
	Arma _arma;
	Armadura _casc;
	Armadura _pechera;
	Armadura _pantalons;
	Armadura _botes;

	string _nom;
	int _gemas;
	int _nivell;
	int _exp;
	int _expSeg;

	int _forca;
	int _vitalitat;
	int _saviesa;
	int _astucia;

	int _vida;
	int _vidaMax;
	int _stamina;
	int _staminaMax;
	int _dmgMin;
	int _dmgMax;
	int _defensa;
	int _precisio;
	int _sort;

	int _stats;
};

#endif //PERSONATGE_H
#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "dArr.h"

using namespace std;

enum _tipusItem {ARMA = 0, ARMADURA};
enum raresa {COMU = 0, POC_COMU, RARO, EPIC, LLEGENDARI, MITIC};

class Item {

public:
	Item();
	Item(int tipusItem, int nivell, int raresa);
	Item(int tipusItem, string nom, int nivell, int preuCompra, int preuVentea, int raresa);
	
	inline const string& nom() const { return this->_nom; };
	inline const int& nivell() const { return this->_nivell; };
	inline const int& preuCompra() const { return this->_preuCompra; };
	inline const int& preuVenta() const { return this->_preuVenta; };
	inline const int& raresa() const { return this->_raresa; };
	inline const int& getTipusItem() const { return this->_tipusItem; }
	inline void setNom(string nom) { this->_nom = nom; }
	virtual Item* clone() const = 0;
	virtual string toString() const = 0;
	virtual string toStringGuarda() const = 0;

private:
	int _tipusItem;
	string _nom;
	int _nivell;
	int _preuVenta;
	int _preuCompra;
	int _raresa;
};

#endif // item_h


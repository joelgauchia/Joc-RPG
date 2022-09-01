#ifndef ARMADURA_H
#define ARMADURA_H

#include <string>
#include "Item.h"

using namespace std;

enum tipusArmadura { CASC = 0, PECHERA, BOTES, PANTALONS};
class Armadura : public Item {

public:
	Armadura();
	Armadura(int nivell, int raresa);
	Armadura(int tipus, int defensa, string nom, int nivell, int preuCompra, int preuVenta, int raresa);

	void mostrarArmadura() const;
	inline int defensa() const { return this->_defensa; }
	inline int tipus() const { return this->_tipus; }
	string toString() const;
	string toStringGuarda() const;

	virtual Armadura* clone() const;

	static dArr<string> noms;
	static void initNoms();

private:
	int _tipus;
	int _defensa;
	string tipusStr;
};
#endif //armadura_h


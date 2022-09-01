#ifndef ARMA_H
#define ARMA_H

#include <string>
#include "Item.h"

using namespace std;

class Arma : public Item {

public:
	Arma();
	Arma(int nivell, int raresa);
	Arma(int malMin, int malMax, string nom, int nivell, int preuCompra, int preuVenta, int raresa);
	
	void mostrarArma() const;
	inline int malMin() const { return this->_malMin; }
	inline int malMax() const { return this->_malMax; }
	string toString() const;
	string toStringGuarda() const;
	virtual Arma* clone() const;

	static dArr<string> noms;
	static void initNoms();

private:
	int _malMin;
	int _malMax;
};
#endif //Arma_h


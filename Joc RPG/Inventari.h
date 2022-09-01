#ifndef INVENTARI_H
#define INVENTARI_H

#include <string>
#include "Arma.h"
#include "Armadura.h"
using namespace std;

class Inventari {

public:
	Inventari();
	Inventari(const Inventari& i);
	~Inventari();
	inline int tamany() const { return this->_nombreItems; }
	Item& operator[] (const int index);
	void operator=(const Inventari& i);
	void afegirItem(const Item& item);
	void esborraItem(int index);
	string toString();

private:
	void inicialitza(const int n = 0);
	void expandeix();
	void copia(const Inventari& i);

	Item** _vectorItems;
	int _capacitat;
	int _nombreItems;
};

#endif // Inventari_h




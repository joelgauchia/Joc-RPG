#include "Item.h"
#include <iostream>

Item::Item() {

	this->_tipusItem = -1;
	this->_nom = "BUIT";
	this->_nivell = 0;
	this->_preuCompra = 0;
	this->_preuVenta = 0;
	this->_raresa = 0;
}

Item::Item(int tipusItem, int nivell, int raresa) {

	this->_nom = "BUIT";
	this->_nivell = rand() % (nivell + 2) + 1;
	this->_raresa = raresa;
	this->_preuCompra = (this->_nivell + this->_raresa) + this->_nivell * this->_raresa * 10;
	this->_preuVenta = this->_preuCompra / 2;
	this->_tipusItem = tipusItem;
}

Item::Item(int tipusItem, string nom, int nivell, int preuCompra, int preuVenta, int raresa) {

	this->_tipusItem = tipusItem;
	this->_nom = nom;
	this->_nivell = nivell;
	this->_preuCompra = preuCompra;
	this->_preuVenta = preuVenta;
	this->_raresa = raresa;
}
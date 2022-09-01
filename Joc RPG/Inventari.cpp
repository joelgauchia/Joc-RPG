#include "Inventari.h"
#include <iostream>

using namespace std;

Inventari::Inventari() {

	this->_capacitat = 5;
	this->_nombreItems = 0;
	this->_vectorItems = new Item * [_capacitat];
	inicialitza();
}

Inventari::Inventari(const Inventari& i) {

	copia(i);
}

Inventari::~Inventari() {

	for (size_t i = 0; i < this->_nombreItems; i++) {
		delete this->_vectorItems[i];
	}
	delete[] _vectorItems;
}

Item& Inventari::operator[] (const int index) {
	
	if (index < 0 or index >= this->_nombreItems) throw("Mal index");

	return *this->_vectorItems[index];
}

void Inventari::operator=(const Inventari& i) {

	for (size_t i = 0; i < this->_nombreItems; i++) {
		delete this->_vectorItems[i];
	}
	delete[] _vectorItems;

	this->_capacitat = i._capacitat;
	this->_nombreItems = i._nombreItems;
	this->_vectorItems = new Item * [this->_capacitat];

	for (int k = 0; k < this->_nombreItems; k++) {
		this->_vectorItems[k] = i._vectorItems[k]->clone();
	}
	inicialitza(this->_nombreItems);
}

void Inventari::expandeix() {

	this->_capacitat *= 2;

	Item** temporal = new Item * [this->_capacitat];

	for (size_t i = 0; i < this->_nombreItems; i++) {
		temporal[i] = this->_vectorItems[i];
	}

	delete[] this->_vectorItems;

	this->_vectorItems = temporal;
	this->inicialitza(this->_nombreItems);
}

void Inventari::inicialitza(const int n) {
	
	for (size_t i = n; i < _capacitat; i++) {
		_vectorItems[i] = nullptr;
	}
}

void Inventari::afegirItem(const Item& item) {

	if (this->_nombreItems >= this->_capacitat) {
		expandeix();
	}
	this->_vectorItems[this->_nombreItems++] = item.clone();
}

void Inventari::esborraItem(int index) {

	if (index < 0 or index >= this->_nombreItems) throw("Fora de rang de l'inventari!");

	delete this->_vectorItems[index];
	this->_vectorItems[index] = this->_vectorItems[this->_nombreItems - 1];
	this->_vectorItems[--this->_nombreItems] = nullptr;
}

void Inventari::copia(const Inventari& i) {

	this->_capacitat = i._capacitat;
	this->_nombreItems = i._nombreItems;
	this->_vectorItems = new Item * [this->_capacitat];

	for (int k = 0; k < this->_nombreItems; k++) {
		this->_vectorItems[k] = i._vectorItems[k]->clone();
	}
	inicialitza(this->_nombreItems);
}


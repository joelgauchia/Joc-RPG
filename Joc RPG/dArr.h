#pragma once

template<typename T>
class dArr {

public:
	dArr(unsigned tamany = 5);
	dArr(const dArr& obj);
	~dArr();

	T& operator[] (const unsigned index);
	void operator = (const dArr& obj);

	unsigned maxCap();
	unsigned tamany();
	void afegeix(const T element);
	void elimina(const unsigned index, bool ordered = false);
	void allibera();

private: 
	unsigned _cap;
	unsigned _initialCap;
	unsigned _nElem;
	T** _arr;

	void expandeix();
	void inicialitza(unsigned de);
};

template<typename T>
dArr<T>::dArr(unsigned tamany) {

	this->_initialCap = tamany;
	this->_cap = tamany;
	this->_nElem = 0;

	this->_arr = new T * [this->_cap];

	inicialitza(0);
}

template<typename T>
dArr<T>::dArr(const dArr& obj) {

	this->_initialCap = obj._initialCap;
	this->_cap = obj._cap;
	this->_nElem = obj._nElem;

	this->_arr = new T * [this->_cap];

	for (size_t i = 0; i < this->_nElem; i++) {
		this->_arr[i] = new T(*obj._arr[i]);
	}

	inicialitza(0);
}

template<typename T>
dArr<T>::~dArr() {
	
	for (size_t i = 0; i < this->_nElem; i++) {
		delete this->_arr[i];
	}
	delete[] _arr;
}

template<typename T>
T& dArr<T>::operator[] (const unsigned index) {

	if (index < 0 or index >= this->_nElem) throw ("L'index esta fora de rang!");

	return *this->_arr[index];
}

template<typename T>
void dArr<T>::operator= (const dArr& obj) {

	for (size_t i = 0; i < this->_nElem; i++) delete this->_arr[i];

	delete[] _arr;

	this->_initialCap = obj._initialCap;
	this->_cap = obj._cap;
	this->_nElem = obj._nElem;

	this->_arr = new T*[this->_cap];

	for (size_t i = 0; i < this->_nElem; i++) {
		this->_arr[i] = new T(*obj._arr[i]);
	}

	this->inicialitza(0);
}

template<typename T>
void dArr<T>::expandeix() {

	this->_cap *= 2;
	T** tempArr = new T * [this->_cap];
	
	for (size_t i = 0; i < this->_nElem; i++) {
		tempArr[i] = this->_arr[i];
	}

	delete[] _arr;
	
	this->_arr = tempArr;

	inicialitza(this->_nElem);
}

template<typename T>
void dArr<T>::inicialitza(unsigned de) {

	for (size_t i = de; i < this->_cap; i++) {
		this->_arr[i] = nullptr;
	}
}

template<typename T>
unsigned dArr<T>::maxCap() {

	return this->_cap;
}

template<typename T>
unsigned dArr<T>::tamany() {

	return this->_nElem;
}

template<typename T>
void dArr<T>::afegeix(const T element) {

	if (this->_nElem >= this->_cap) this->expandeix();

	this->_arr[this->_nElem++] = new T(element);
}

template<typename T>
void dArr<T>::elimina(const unsigned index, bool ordenat) {

	if (index < 0 or index >= this->_nElem) throw "Fora de rang!";

	if (ordenat) {
		delete this->_arr[index];

		for (size_t i = 0; i < this->_nElem - 1; i++) {
			this->_arr[i] = this->_arr[i + 1];
		}
		this->_arr[--this->_nElem] = nullptr;
	}
	else {
		delete this->_arr[index];

		this->_arr[index] = this->_arr[this->_nElem - 1];
		this->_arr[--this->_nElem] = nullptr;
	}
}

template<typename T>
void dArr<T>::allibera() {

	for (size_t i = 0; i < this->_nElem; i++) {
		delete this->_arr[i];
	}

	this->_nElem = 0;
	inicialitza(0);
}


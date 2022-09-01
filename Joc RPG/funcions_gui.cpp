#include "funcions_gui.h"

const string gui::titolMenu(const string titol) {

	stringstream ss;

	ss << "\n" << " == [[ " << titol << " ]] == " << "\n" << "\n";

	return ss.str();
}

const string gui::titolMenu2(const string titol) {

	stringstream ss;

	ss << " - " << titol << " - " << "\n" << "\n";

	return ss.str();
}

const string gui::divisorMenu(const unsigned quantitat, const char caracter) {

	stringstream ss;

	ss << string(quantitat, caracter) << "\n";
	return ss.str();
}

const string gui::itemMenu(const unsigned index, const string text) {

	stringstream ss;

	ss << "- " << "(" << index << ") " << text << "\n";

	return ss.str();
}

const string gui::barraProgres(const int valorMin, const int valorMax, const int llargadaMaxima, const char simbolBuit, const char simbolPle) {
	
	stringstream ss;
	
	double percent = static_cast<double>(valorMin) / valorMax;
	int simbolsPlens = llargadaMaxima * percent; // quants simbols plens hi hauran
	int simbolsBuits = llargadaMaxima - simbolsPlens; // quants simbols buits hi hauran

	if (simbolsPlens < 0) simbolsPlens = 0;
	else if (simbolsPlens > valorMax) simbolsPlens = valorMax;
	if (simbolsBuits < 0) simbolsBuits = 0;
	else if (simbolsBuits > valorMax) simbolsBuits = valorMax;

	//ss << percent << " " << simbolsPlens << " " << simbolsBuits << endl;
	ss << " |" << string(simbolsPlens, simbolPle) << string(simbolsBuits, simbolBuit) << "| ";

	return ss.str();
}

const string gui::alerta(const string text) {

	stringstream ss;

	ss << "\n" << "    - (*) " << text << "\n";

	return ss.str();
}

const string gui::error(const string text) {

	stringstream ss;

	ss << "\n" << "    - (!) " <<  text << "\n";

	return ss.str();
}
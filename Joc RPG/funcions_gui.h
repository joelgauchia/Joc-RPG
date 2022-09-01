#pragma once

#include <sstream>
#include <string>

using namespace std;

namespace gui {

	const string titolMenu(const string titol);
	const string titolMenu2(const string titol);
	const string divisorMenu(const unsigned quantitat = 30, const char caracter = '-');
	const string itemMenu(const unsigned index, const string text);
	const string barraProgres(const int valorMin, const int valorMax, const int llargadaMaxima, const char simbolBuit, const char simbolPle);
	const string alerta(const string text);
	const string error (const string text);
}


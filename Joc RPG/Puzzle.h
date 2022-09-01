#ifndef	PUZZLE_H
#define PUZZLE_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Puzzle {

public:
	Puzzle(string fitxer);

	string aString();

	bool respostaCorrecta(const int& resposta_usuari) const;
	inline bool getTamany() const { return this->_nRespostes; }

private:
	string _pregunta;
	vector<string> _respostes;
	int _respostaCorrecta;
	int _nRespostes;
};
#endif //puzzle_h


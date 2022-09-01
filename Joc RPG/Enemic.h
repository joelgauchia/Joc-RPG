#ifndef ENEMIC_H
#define ENEMIC_H

#include <string>

using namespace std;

class Enemic {

public:
	Enemic(int nivell = 0);

	void repMal(int mal);
	int fesMal() const;
	int guanyaExp() const;
	int taxaGemas() const;

	inline bool estaViu() { return this->_vida > 0; }
	inline bool defensa() { return this->_defensa; }
	inline bool precisio() { return this->_precisio; }
	inline bool getVida() { return this->_vida; }
	inline bool getVidaMax() { return this->_vidaMax; }

	void mostraEnemic() const;
	string mostraNivelliVida() const;

private:
	int _nivell;
	int _vida;
	int _vidaMax;
	int _malMin;
	int _malMax;
	float _percentatgeDrop;
	int _defensa;
	int _precisio;
};
#endif //Enemic_h


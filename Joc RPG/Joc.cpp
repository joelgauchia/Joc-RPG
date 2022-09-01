#include "Joc.h"

Joc::Joc() {
	_opcio = 0;
	_jugadorActual = 0;
	_fitxer = "personatges.txt";
	_acabat = false;
}

void Joc::menuJoc() {
	
	system("pause");
	system("CLS");

	if (this->_personatges[_jugadorActual].estaViu()) {

		stringstream menu_str;
		
		menu_str << gui::titolMenu("MENU DE JOC");

		if (this->_personatges[_jugadorActual].potPujarNivell()) {
			menu_str << gui::alerta("Pujar de nivell disponible!");
		}

		menu_str << gui::divisorMenu(30, '-');
		menu_str << " = Personatge actiu: " << this->_personatges[_jugadorActual].getBarraMenu() << endl;

		menu_str << gui::itemMenu(0, "Sortir");
		menu_str << gui::itemMenu(1, "Aventura");
		menu_str << gui::itemMenu(2, "Puja de nivell");
		menu_str << gui::itemMenu(3, "Descansar"); 
		menu_str << gui::itemMenu(4, "Info del personatge"); 
		menu_str << gui::itemMenu(5, "Crea personatge");
		menu_str << gui::itemMenu(6, "Selecciona personatge"); 
		menu_str << gui::itemMenu(7, "Guarda personatge");
		menu_str << gui::itemMenu(8, "Carrega personatge"); 
	
		getOpcio(this->_opcio, menu_str.str(), 1);

		switch (_opcio) {

		case 0: // Sortir
			this->_acabat = true;
			guardarPersonatges();
			break;
		case 1: // Aventura
			aventura();
			break;
		case 2: // Puja nivell
			levelUpPersonatge();
			break;
		case 3: // Descansar
			descansar();
			break;
		case 4: // Menu personatges
			menuPersonatges();
			break;
		case 5: // crea perso
			cin.ignore();
			crearNouPersonatge();
			guardarPersonatges();
			break;
		case 6: // selecciona person
			seleccionaPersonatge();
			break;
		case 7: // guarda perso
			guardarPersonatges();
			break;
		case 8: // carrega perso
			carregarPersonatges();
			break;
		default:
			cout << " - ERROR: OPCIO NO EXISTENT!" << endl << endl;
			break;
		}
	}

	else {

		stringstream menu_str;

		gui::titolMenu("Has mort... Carregar partida?");
		gui::itemMenu(0, "Si");
		gui::itemMenu(1, "No");
	
		getOpcio(_opcio, menu_str.str(), 1);

		if (this->_opcio == 0) carregarPersonatges();
		else _acabat = true;
	}
}

bool Joc::acabat() const {
	return this->_acabat;
}

void Joc::inicialitzarJoc() {

	ifstream in;
	in.open("personatges.txt");

	Arma::initNoms();
	Armadura::initNoms();

	if (in.is_open()) carregarPersonatges();
	else {
		crearNouPersonatge();
		guardarPersonatges();
	}
	in.close();
}

void Joc::crearNouPersonatge() {
	
	string nom;
	cout << "Nom del personatge:" << endl;
	getline(cin, nom);

	for (size_t i = 0; i < this->_personatges.size(); i++) {
		while (nom == this->_personatges[i].nom()) {
			cout << gui::error("Ja existeix el personatge!");
			system("pause");
			cout << "Nom del personatge: " << endl;
			getline(cin, nom);
		}
	}
	_personatges.push_back(Personatge(nom));
	_jugadorActual = _personatges.size() - 1;

	cout << "S'ha creat el personatge!" << endl << endl;
}

void Joc::levelUpPersonatge() {

	if (this->_personatges[_jugadorActual].potPujarNivell()) {

		this->_personatges[_jugadorActual].pujaNivell();
		stringstream menu_str;

		cout << gui::titolMenu("Tens punts de stats per repartir!");
		cout << gui::titolMenu2("Stat a millorar");
		cout << gui::itemMenu(0, "Forca");
		cout << gui::itemMenu(1, "Vitalitat");
		cout << gui::itemMenu(2, "Saviesa");
		cout << gui::itemMenu(3, "Astucia");
		
		getOpcio(_opcio, menu_str.str(), 1);

		while (_opcio > 3 or _opcio < 0) {
			cout << gui::error("Stat inexistent!");
			getOpcio(_opcio, menu_str.str(), 1);
		}
		
		this->_personatges[_jugadorActual].afegiraStat(this->_opcio, 1);
	}
	else cout << endl << " - EXP insuficient!" << endl << endl;
}

void Joc::menuPersonatges(){

	do {
		system("CLS");
		cout << gui::titolMenu("Menu de personatges");

		cout << gui::divisorMenu();

		_personatges[_jugadorActual].mostraPersonatge();

		cout << "= MENU =" << endl;
		cout << gui::itemMenu(0, "Torna enrere");
		cout << gui::itemMenu(1, "Mostra inventari");
		cout << gui::itemMenu(2, "Equipa item");
		cout << endl;

		cout << "Tria una opcio:" << endl;
		cin >> this->_opcio;

		while (cin.fail() or this->_opcio < 0 or this->_opcio > 2) {
			cout << "Mal input" << endl;
			cin.clear();
			cin.ignore(100, '\n');

			cout << "= MENU =" << endl;
			cout << "0: Torna" << endl;
			cout << "1: Mostra inventari " << endl;
			cout << "2: Equipa item" << endl << endl;

			cout << endl << "Tria una opcio:" << endl;
			cin >> _opcio;
		}
		cin.ignore(100, '\n');
		cout << endl;

		switch (this->_opcio) {
		case 1:
			cout << _personatges[_jugadorActual].InvaString();
			break;
		case 2:
			if (this->_personatges[_jugadorActual].getTamanyInventari() == 0) cout << " - No hi han items per equipar!" << endl;
			else {
				cout << _personatges[_jugadorActual].InvaString();

				cout << "Item index:" << endl;
				cin >> this->_opcio;

				while (cin.fail() or this->_opcio < 0 or this->_opcio >= this->_personatges[_jugadorActual].getTamanyInventari()) {
					cout << "Mal input" << endl;
					cin.clear();
					cin.ignore(100, '\n');

					cout << endl << "Item index:" << endl;
					cin >> _opcio;
				}
				cin.ignore(100, '\n');
				cout << endl;
				_personatges[_jugadorActual].equiparItem(_opcio);
			}
		default:
			break;
		}

		if (this->_opcio > 0) {
			cout << "ENTER per continuar..." << endl;
			cin.get();
		}
	
	} while (this->_opcio > 0);
}

void Joc::guardarPersonatges() {

	ofstream out(_fitxer);

	if (out.is_open()) {

		for (size_t i = 0; i < _personatges.size(); i++) {
			out << _personatges[i].aString() << "\n";
			out <<_personatges[i].InvaStringGuarda() << "\n";
		}
		cout << " - Personatge guardat!" << endl;
	}
	out.close();
}

void Joc::carregarPersonatges() {

	ifstream in(this->_fitxer);

	this->_personatges.clear();

	string nom = " ";
	int distanciaViatjada = 0;
	int gemas = 0;
	int nivell = 0;
	int exp = 0;
	int forca = 0;
	int vitalitat = 0;
	int saviesa = 0;
	int astucia = 0;
	int vida = 0;
	int stamina = 0;
	int stats = 0;

	//Item
	int tipusItem = 0;
	int defensa = 0;
	int tipus = 0;
	int malMin = 0;
	int malMax = 0;
	//nom
	//nivell
	int preuCompra = 0;
	int preuVenta = 0;
	int raresa = 0;

	Inventari tempItems;

	string linia = "";
	stringstream str;

	if (in.is_open()) {
		while (getline(in, linia)) {

			str.str(linia);
			str >> nom;
			str >> distanciaViatjada;
			str >> gemas;
			str >> nivell;
			str >> exp;
			str >> forca;
			str >> vitalitat;
			str >> saviesa;
			str >> astucia;
			str >> vida;
			str >> stamina;
			str >> stats;

			//Personatge
			Personatge temp(nom, distanciaViatjada, gemas, nivell, exp, forca, vitalitat, saviesa, astucia, vida, stamina, stats);
			
			//Arma
			str >> tipusItem >> nom >> nivell >> raresa >> preuCompra >> preuVenta >> malMin >> malMax;
			Arma arma(malMin, malMax, nom, nivell, preuCompra, preuVenta, raresa);
			
			//Armadura
			str >> tipusItem >> nom >> nivell >> raresa >> preuCompra >> preuVenta >> defensa >> tipus;
			Armadura a_casc(tipusItem, defensa, nom, nivell, preuCompra, preuVenta, raresa);
			str >> tipusItem >> nom >> nivell >> raresa >> preuCompra >> preuVenta >> defensa >> tipus;
			Armadura a_pechera(tipusItem, defensa, nom, nivell, preuCompra, preuVenta, raresa);
			str >> tipusItem >> nom >> nivell >> raresa >> preuCompra >> preuVenta >> defensa >> tipus;
			Armadura a_pantalons(tipusItem, defensa, nom, nivell, preuCompra, preuVenta, raresa);
			str >> tipusItem >> nom >> nivell >> raresa >> preuCompra >> preuVenta >> defensa >> tipus;
			Armadura a_botes(tipusItem, defensa, nom, nivell, preuCompra, preuVenta, raresa);

			temp.setArma(arma);
			temp.setArmaduraCasc(a_casc);
			temp.setArmaduraPechera(a_pechera);
			temp.setArmaduraPantalons(a_pantalons);
			temp.setArmaduraBotes(a_botes);
			
			//Items
			str.clear();
			linia.clear();
			getline(in, linia);

			str.str(linia);

			while (str >> tipusItem >> nom >> nivell >> raresa >> preuCompra >> preuVenta >> malMin >> malMax) {
				temp.afegirItem(Arma(malMin, malMax, nom, nivell, preuCompra, preuVenta, raresa));
			}

			str.clear();
			linia.clear();
			getline(in, linia);

			while (str >> tipusItem >> nom >> nivell >> raresa >> preuCompra >> preuVenta >> defensa >> tipus) {
				temp.afegirItem(Armadura(tipus, defensa, nom, nivell, preuCompra, preuVenta, raresa));
			}

			this->_personatges.push_back(Personatge(temp));
			cout << "Personatge " << temp.nom() << " carregat!" << endl;

			str.clear();
		}
	}
	in.close();

	if (this->_personatges.size() <= 0) {
		throw "ERROR! No s'han carregat personatges o fitxer buit!";
	}
}

void Joc::seleccionaPersonatge() {

	cout << "Selecciona el personatge:" << endl << endl;
	for (size_t i = 0; i < this->_personatges.size(); i++) {
		cout << "Index: " << i << " - "<< this->_personatges[i].nom() << " Nivell: " << this->_personatges[i].nivell() << endl;
	}

	cout << endl << "Quin vols seleccionar?:" << endl;
	cin >> this->_opcio;

	while (cin.fail() or this->_opcio >= this->_personatges.size()) {

		cout << "Input incorrecte!" << endl;
		cin.clear();
		cin.ignore(100, '\n');

		cout << "Selecciona el personatge:" << endl;
		cin >> this->_opcio;
	}

	cin.ignore(100, '\n');
	cout << endl;

	this->_jugadorActual = this->_opcio;

	cout << this->_personatges[this->_jugadorActual].nom() << " seleccionat!" << endl;
}

void Joc::aventura() {

	this->_personatges[_jugadorActual].moure();

	Event e;
	e.generaEvent(this->_personatges[_jugadorActual], this->_enemics);
}

void Joc::descansar() {

	int costDescans = _personatges[_jugadorActual].getVidaMax() - _personatges[_jugadorActual].getVida();
	cout << "Descansar" << endl << endl;
	cout << "Descanar et costara: " << costDescans << endl << endl;
	cout << "Les teves gemas: " << _personatges[_jugadorActual].getGemas() << endl;
	cout << "La teva vida: " << _personatges[_jugadorActual].getVida() << " / " << _personatges[_jugadorActual].getVidaMax() << endl << endl;

	if (_personatges[_jugadorActual].getGemas() < costDescans) cout << "Gemas insuficients, no pots descansar!" << endl << endl;
	else if (_personatges[_jugadorActual].getVida() >= _personatges[_jugadorActual].getVidaMax()) cout << "Ja tens la vida al maxim!" << endl << endl;
	else {
		cout << "Vols descansar? (0) Si, (1) No..." << endl << endl;
		cin >> this->_opcio;

		while (cin.fail() or this->_opcio < 0 or this->_opcio > 1) {

			cout << "Input incorrecte!" << endl;
			cin.clear();
			cin.ignore(100, '\n');

			cout << "Vols descansar? (0) Si, (1) No..." << endl << endl;
			cin >> this->_opcio;
		}

		cin.ignore(100, '\n');
		cout << endl;

		if (this->_opcio == 0) {
			_personatges[_jugadorActual].reiniciaVida();
			_personatges[_jugadorActual].pagaGemas(costDescans);
		}
		else cout << "Potser en una altra ocasio!" << endl << endl;
	}
}
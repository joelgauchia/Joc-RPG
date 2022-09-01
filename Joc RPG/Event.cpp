#include "Event.h"
#include <iostream>

int Event::_nombreEvents = 4;

using namespace std;

Event::Event() {

}

void Event::generaEvent(Personatge &personatge, dArr<Enemic>& enemics) {

	int i = rand() % Event::_nombreEvents;
	
	switch (i) {
	case 0:
		//Enemic
		lluitaEnemic(personatge, enemics);
		break;

	case 1:
		//Puzzle
		resolPuzzle(personatge);
		break;

	case 2:
		//Tenda
		entraTenda(personatge);
		break;

	default:
		break;
	}
}

void Event::lluitaEnemic(Personatge& personatge, dArr<Enemic>& enemics) {

	bool tornPersonatge = false;
	int opcio = 0;

	//Tira moneda pel torn
	int tiraMoneda = rand() % 2 + 1;

	if (tiraMoneda == 1) tornPersonatge = true;
	else tornPersonatge = false;

	//Condicions per acabar
	bool escapa = false;
	bool jugadorDerrotat = false;
	bool enemicDerrotat = false;

	//Enemics
	enemics.allibera(); // neteja els enemics
	int nEnemics = rand() % 5 + 1;

	for (size_t i = 0; i < nEnemics; i++) {
		enemics.afegeix(Enemic(personatge.nivell() + rand() % 3));
	}

	//Variables de batalla
	int tiradaCombat = 0;
	int tiradaCombatJugador = 0;
	int tiradaCombatEnemic = 0;
	int mal = 0;
	int guanyaExp = 0;
	int guanyaGemas = 0;
	int precisioJugador = 0;
	int defensaJugador = 0;
	int totalJugador = 0;
	int precisioEnemic = 0;
	int defensaEnemic = 0;
	int totalEnemic = 0;
	int totalCombat = 0;

	while (not escapa and not jugadorDerrotat and not enemicDerrotat) {
		
		if (tornPersonatge and not jugadorDerrotat) {
			
			//Menu
			system("CLS");
			stringstream menu_str;

			menu_str << gui::titolMenu("Menu de batalla");
			menu_str << " - Torn del jugador" << endl << endl;
			menu_str << personatge.getBarraMenu() << endl;

			menu_str << "HP: " << personatge.getVida() << " / " << personatge.getVidaMax() << gui::barraProgres(personatge.getVida(), personatge.getVidaMax(), 10, '-', '=') << endl << endl;
			menu_str << gui::itemMenu(0, "Escapa") << endl;
			menu_str << gui::itemMenu(1, "Ataca") << endl;
			menu_str << gui::itemMenu(2, "Utilitza item") << endl << endl;

			getOpcio(opcio, menu_str.str(), 1);

			// Mou
			switch (opcio) {
			case 0: // escapa
				escapa = true;
				break;
			case 1: // ataca

				system("CLS");

				//Selecciona enemic
				menu_str.clear();

				menu_str << " = Selecciona enemic:" << endl << endl;

				for (size_t i = 0; i < enemics.tamany(); i++) {
					menu_str << gui::itemMenu(i, enemics[i].mostraNivelliVida());
				}

				getOpcio(opcio, menu_str.str(), 1);

				// tirada d'atac
				totalCombat = enemics[opcio].defensa() + personatge.getPrecisio();
				totalEnemic = enemics[opcio].defensa() / (double)totalCombat * 100;
				totalJugador = personatge.getPrecisio() / (double)totalCombat * 100;
				tiradaCombatJugador = rand() % totalJugador + 1;
				tiradaCombatEnemic = rand() % totalEnemic + 1;

				menu_str << string(30, '-') << endl;
				menu_str << " | Total combat: " << totalCombat << endl;
				menu_str << " | Percentatge enemic: " << totalEnemic << endl;
				menu_str << " | Percentatge jugador: " << totalJugador << endl;
				menu_str << " | Tirada jugador:	" << tiradaCombatJugador << endl;
				menu_str << " | Tirada enemic: " << tiradaCombatEnemic << endl;
				menu_str << string(30, '-') << endl << endl;
					
				if (tiradaCombatJugador > tiradaCombatEnemic) { // encerta
					
					mal = personatge.getMal();
					enemics[opcio].repMal(mal);

					cout << " - Encert: " << mal << "!" << endl << endl;
					//cout << " - Vida enemic: " << enemics[opcio].getVida() << " / " << enemics[opcio].getVidaMax() << endl << endl;
				
					if (not enemics[opcio].estaViu()) {

						cout << " - [ Enemic derrotat! ] - " << endl;
						guanyaExp = enemics[opcio].guanyaExp();
						personatge.guanya_exp(guanyaExp);
						guanyaGemas = rand() % enemics[opcio].taxaGemas();
						personatge.guanya_gemas(guanyaGemas);
						cout << " - EXP obtinguda: " << guanyaExp << endl;
						cout << " - Gemas obtingudes: " << guanyaGemas << endl << endl;

						// Drop aleatori
						int drop = rand() % 100 + 1;
						int raresa = -1;

						if (drop > 20) {
							raresa = 0; // comu
							drop = rand() % 100 + 1;
							if (drop > 30) {
								raresa = 1; // poc comu
								drop = rand() % 100 + 1;
								if (drop > 50) {
									raresa = 2; // rara
									drop = rand() % 100 + 1;
									if (drop > 70) {
										raresa = 3; // llegendari
										drop = rand() % 100 + 1;
										if (drop > 90) {
											raresa = 4; // mitica
										}
									}
								}
							}
						}
						if (raresa >= 0) {
							drop = rand() % 100 + 1;
							
							if (drop > 50) {
								Arma tempA(personatge.nivell(), raresa);
								personatge.afegirItem(tempA);
								cout << " - Drop d'Arma, consulta-la a l'inventari!" << endl;
							}
							else {
								Armadura tempAm(personatge.nivell(), raresa);
								personatge.afegirItem(tempAm);
								cout << " - Drop d'Armadura, consulta-la a l'inventari!" << endl;
							}
						}

						enemics.elimina(opcio);
					}
				}
				else { // falla
					cout << " - Fallat!" << endl << endl;
				}
				system("pause");
				break;

			case 2: // item

				system("CLS");

				menu_str.clear();

				menu_str << gui::titolMenu2("Utilitza item");
				menu_str << gui::itemMenu(0, "Enrere");
				menu_str << gui::itemMenu(1, "Item curatiu");

				getOpcio(opcio, menu_str.str(), 1);

				switch (opcio) {
				case 0:
					gui::alerta("Tornant al menu...");
					system("pause");
					break;
				case 1:
					personatge.reiniciaVida();
					system("pause");
					break;
				default:
					gui::error("Opcio inexistent!");
					system("pause");
					break;
				}

				break;
			default:
				break;
			}

			// Deixa torn
			tornPersonatge = false;
			cout << endl;
			//system("pause");
		}

		else if (not tornPersonatge and not escapa and not enemicDerrotat) {

			system("CLS");
			
			cout << gui::titolMenu("Menu de batalla");
			cout << " - Torn de l'enemic" << endl << endl;
			
			int index_enemic = rand() % enemics.tamany();
			Enemic* enemic = &enemics[index_enemic];

			// Atac enemic
			cout << " - Enemic: " << index_enemic << endl << endl;

			// Tirada atac
			totalCombat = enemic->precisio() + personatge.getDefensa() + personatge.getDefensaAfegida();
			totalEnemic = enemic->precisio() / (double)totalCombat * 100;
			totalJugador = (personatge.getDefensa() + personatge.getDefensaAfegida()) / (double)totalCombat * 100;
			tiradaCombatJugador = rand() % totalJugador + 1;
			tiradaCombatEnemic = rand() % totalEnemic + 1;

			cout << string(30, '-') << endl;
			cout  << " | Total combat: " << totalCombat << endl;
			cout << " | Percentatge enemic: " << totalEnemic << endl;
			cout << " | Percentatge jugador: " << totalJugador << endl;
			cout << " | Tirada jugador:	" << tiradaCombatJugador << endl;
			cout << " | Tirada enemic: " << tiradaCombatEnemic << endl;
			cout << string(30, '-') << endl << endl;

			if (tiradaCombatJugador < tiradaCombatEnemic) {

				mal = enemic->fesMal();
				personatge.rebreMal(mal);

				cout << " - Encert: " << mal << "!" << endl << endl;
				cout << " - Vida jugador: " << personatge.getVida() << " / " << personatge.getVidaMax() << endl << endl;

				if (not personatge.estaViu()) {
					cout << " - [ Has estat derrotat! ] -" << endl;
					jugadorDerrotat = true;
				}
			}
			else cout << " - Fallat! " << endl;

			// Finalitza torn
			tornPersonatge = true;
			cout << endl;
			system("pause");
		}


		//Condicions
		if (not personatge.estaViu()) { 
			
			jugadorDerrotat = true; 
		}
		else if (enemics.tamany() <= 0) { 
			
			enemicDerrotat = true; 
		}
	}
}

void Event::resolPuzzle(Personatge& personatge) {

	bool completat = false;
	int resposta_usuari = 0;
	int intents = 3;
	int guanyaExp = (intents * personatge.nivell() * (rand() % 10 + 1));
	int guanyaGemas = (intents * personatge.nivell() * (rand() % 10 + 1));
	Puzzle puzzle("2.txt");

	cout << gui::titolMenu("Benvingut al Quiz");

	while (not completat and intents > 0) {
		
		cout << "Intents: " << intents << endl << endl;
		intents--;
		cout << puzzle.aString() << endl;

		cout << "Entra la teva resposta: ";
		cin >> resposta_usuari;

		while (cin.fail()) {
			cout << "Mal input" << endl;
			cin.clear();
			cin.ignore(100, '\n');

			cout << endl << "Entra la teva resposta: ";
			cin >> resposta_usuari;
		}
		cin.ignore(100, '\n');
		cout << endl;

		if (puzzle.respostaCorrecta(resposta_usuari)) {
			completat = true;

			personatge.guanya_exp(guanyaExp);
			cout << "Has guanyat " << guanyaExp << " EXP!" << endl << endl;
			cout << "Has guanyat " << guanyaGemas << " Gemas!" << endl << endl;
		}
		else if (resposta_usuari > (puzzle.getTamany()+1)) cout << " - Resposta no existent, un intent menys per listo!" << endl;
		else cout << " - Resposta incorrecte!" << endl;
	}

	if (completat) {
		cout << " - Enhorabona, has encertat!" << endl << endl;
	}
	else cout << "GAME OVER!" << endl << endl; // POSAR QUE ACABI LA PARTIDA
}

void Event::entraTenda(Personatge& personatge) {

	int opcio = 0;
	bool comprant = true;
	Inventari merchInv;
	string inv;

	int nItems = rand() % 20 + 10;
	bool random = false;

	for (size_t i = 0; i < nItems; i++) {

		random = rand() % 2;

		if (random > 0)
			merchInv.afegirItem(Arma(personatge.nivell() + rand() % 5, rand() % 4));
		else
			merchInv.afegirItem(Armadura(personatge.nivell() + rand() % 5, rand() % 4));
	}

	while (comprant) {

		system("CLS");

		cout << "= Menu de la Tenda =" << endl << endl;
		cout << "0: Surt" << endl;
		cout << "1: Compra" << endl;
		cout << "2: Ven" << endl;

		cout << "Tria una opcio: " << endl;
		cin >> opcio;

		while (cin.fail() or opcio > 3 or opcio < 0) {

			system("CLS");

			cout << "Input incorrecte!" << endl;
			cin.clear();
			cin.ignore(100, '\n');

			cout << "= Menu de la Tenda =" << endl << endl;
			cout << "0: Surt" << endl;
			cout << "1: Compra" << endl;
			cout << "2: Ven" << endl;
			
			cout << "Tria una opcio:" << endl;
			cin >> opcio;
		}

		cin.ignore(100, '\n');
		cout << endl;

		// Tenda
		switch (opcio) {
		case 0: // Surt
			comprant = false;
			break;
		case 1: // Compra

			cout << "= Menu compra =" << endl << endl;
			cout << "Gemas: " << personatge.getGemas() << endl << endl;

			inv.clear();

			for (size_t i = 0; i < merchInv.tamany(); i++) {
				inv += to_string(i) + ": " + merchInv[i].toString() + "\n - Preu:" + to_string(merchInv[i].preuCompra()) + "\n";
			}
			cout << inv << endl;

			cout << "Gemas: " << personatge.getGemas() << endl;
			cout << "Tria un item: " << endl;
			cin >> opcio;

			while (cin.fail() or opcio > merchInv.tamany() or opcio < -1) {

				system("CLS");

				cout << "Input incorrecte!" << endl;
				cin.clear();
				cin.ignore(100, '\n');

				cout << "Gemas: " << personatge.getGemas() << endl;
				cout << "Tria un item (-1 per cancelar):" << endl;
				cin >> opcio;
			}
			cin.ignore(100, '\n');
			cout << endl;
			
			if (opcio == -1) {
				cout << "Cancelat..." << endl << endl;
			}

			else if (personatge.getGemas() >= merchInv[opcio].preuCompra()) {
				personatge.pagaGemas(merchInv[opcio].preuCompra());
				personatge.afegirItem(merchInv[opcio]);
				cout << "S'ha comprat l'item " << merchInv[opcio].nom() << " -" << merchInv[opcio].preuCompra() << endl;
				merchInv.esborraItem(opcio);
			}
			else cout << "No et pots permetre l'item!" << endl;
			break;

		case 2: // Ven

			cout << personatge.InvaString(true) << endl;
			
			cout << "= Menu venta =" << endl << endl;
			cout << "- Gemas: " << personatge.getGemas() << endl << endl;

			if (personatge.getTamanyInventari() > 0) {

				cout << "Gemas: " << personatge.getGemas() << endl;
				cout << "Tria un item (-1 per cancelar):" << endl;
				cin >> opcio;

				while (cin.fail() or opcio > personatge.getTamanyInventari() or opcio < -1) {

					system("CLS");

					cout << "Input incorrecte!" << endl;
					cin.clear();
					cin.ignore(100, '\n');

					cout << "Gemas: " << personatge.getGemas() << endl;
					cout << "Tria un item (-1 per cancelar):" << endl;
					cin >> opcio;
				}
				cin.ignore(100, '\n');
				cout << endl;

				if (opcio == -1) cout << "Cancelat..." << endl;
				else {
					personatge.guanya_gemas(personatge.getItem(opcio).preuVenta());
					cout << "Item venut!" << endl;
					cout << "Gemas obtingudes: " << personatge.getItem(opcio).preuVenta() << endl << endl;
					personatge.borraItem(opcio);
				}
			}
			else {
				cout << "L'inventari esta buit!" << endl;
			}
			break;

		default:
			break;
		}
		cout << "ENTER per continuar..." << endl;
		cin.get();
	}
	cout << "Has sortit de la tenda! " << endl << endl;
}
#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <Windows.h>
#include "Personatge.h"
#include "Puzzle.h"
#include "Enemic.h"
#include "dArr.h"
#include "funcions_gui.h"
#include "funcions.h"

using namespace std;	

class Event {

public:
	Event();
	void generaEvent(Personatge& personatge, dArr<Enemic>& enemics);

	//tipus events
	void lluitaEnemic(Personatge& personatge, dArr<Enemic>& enemics);
	void resolPuzzle(Personatge& personatge);
	void entraTenda(Personatge& personatge);

	static int _nombreEvents;

private:
	
};
#endif //event_h

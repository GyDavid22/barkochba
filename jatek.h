#ifndef JATEK_H_INCLUDED
#define JATEK_H_INCLUDED

#include "adatszerkezet.hpp"
#include "valasz.h"
#include "kerdes.h"

#include "memtrace.h"

class Jatek
{
	Binarisfa<Kerdes>* k;
	Lancoltlista<Valasz>* v;
	bool utolsovalasz;

	Jatek() : k(NULL), v(NULL), utolsovalasz(false) {  } /* nem lehetséges, a beolvasó függvény külön van, a feladatkiírás pedig csak a jatek.h-ra terjed ki */
	Jatek(Jatek &masik) : k(NULL), v(NULL), utolsovalasz(false) {  }
public:
	Jatek(Binarisfa<Kerdes>* kerdesek, Lancoltlista<Valasz>* valaszok) : k(kerdesek), v(valaszok), utolsovalasz(false) {  }
	void jatekmenet();
	void firstrun();
	void randomtipp();
	bool rakerdez();
};

#endif // JATEK_H_INCLUDED

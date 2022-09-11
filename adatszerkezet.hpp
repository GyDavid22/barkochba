#ifndef ADATSZERKEZET_HPP_INCLUDED
#define ADATSZERKEZET_HPP_INCLUDED

#include "memtrace.h"

template <class T>
class Binarisfa
{
	struct Elem
	{
		T adat;
		Elem* bal;
		Elem* jobb;
		Elem* szulo;
		Elem(T beszurando) : adat(beszurando), bal(NULL), jobb(NULL), szulo(NULL) { }
	};
	Elem* gyoker, * jelenlegi;
	size_t elemszam;
	void felszabadit(Elem* innen);
public:
	Binarisfa() : elemszam(0) { jelenlegi = gyoker = NULL; }
	Binarisfa(T* beszurando) : elemszam(1) { jelenlegi = gyoker = new Elem(*beszurando); delete beszurando; }
	~Binarisfa() { felszabadit(gyoker); }

	void gyokerbeallit(T* erre);
	void beszur(T* ezt, bool balt_e);
	void lep(bool balra);
	void kovetkezo();
	void fel() { if (jelenlegi->szulo != NULL) jelenlegi = jelenlegi->szulo; }
	T* getadat() { return &jelenlegi->adat; } /* musz�j pointert visszaadni, mert ezt a k�s�bbiekben lehet, hogy m�dos�tan�nk */
	void visszagyokerhez() { jelenlegi = gyoker; }
	bool vaneaga();
	bool vane(bool bal_e);
	size_t getelemszam() { return elemszam; }
};

template <class T>
class Lancoltlista
{
	struct Elem
	{
		T adat;
		Elem* kovetkezo;
		Elem* elozo;
		Elem() : kovetkezo(NULL), elozo(NULL) { }
		Elem(T input, Elem* eloz) :  adat(input), kovetkezo(NULL), elozo(eloz) { }
	};
	Elem* elso, * jelenlegi;
	size_t listahossz;
public:
	Lancoltlista() : listahossz(0) { jelenlegi = elso = new Elem(); elso->kovetkezo = new Elem(); elso->kovetkezo->elozo = elso; }
	~Lancoltlista();

	void lep();
	void visszaallit();
	T lekerdez();
	void hozzaad(T* ezt);
	size_t getlistahossz() { return listahossz; }
	void torol();
	T operator[](size_t index);
};



template <class T>
void Binarisfa<T>::gyokerbeallit(T* erre)
{
	if (gyoker != NULL)
		delete gyoker;
	gyoker = new Elem(*erre);
	delete erre;
	if (jelenlegi == NULL)
	{
		jelenlegi = gyoker;
		++elemszam;
	}
}

template <class T>
void Binarisfa<T>::felszabadit(Elem* innen)
{
	if (innen == NULL)
		return;
	felszabadit(innen->bal);
	felszabadit(innen->jobb);
	delete innen;
	--elemszam;
}

template <class T>
void Binarisfa<T>::beszur(T* ezt, bool balt_e)
{
	const char* errmessage = "Gy�k�r nincs be�ll�tva; el�bb azt kell be�ll�tani!";
	try
	{
		if (elemszam == 0)
		{
			throw errmessage;
		}
		if (balt_e)
		{
			if (jelenlegi->bal != NULL)
				felszabadit(jelenlegi->bal);
			jelenlegi->bal = new Elem(*ezt);
			jelenlegi->bal->szulo = jelenlegi;
		}
		else
		{
			if (jelenlegi->jobb != NULL)
				felszabadit(jelenlegi->jobb);
			jelenlegi->jobb = new Elem(*ezt);
			jelenlegi->jobb->szulo = jelenlegi;
		}
		++elemszam;
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		exit(EXIT_FAILURE);
	}
	delete ezt;
}

template <class T>
void Binarisfa<T>::lep(bool balra)
{
	if (vane(balra)) /* ha nem l�tezik az elem, nem l�p�nk oda */
	{
		if (balra)
		{
			jelenlegi = jelenlegi->bal;
		}
		else
		{
			jelenlegi = jelenlegi->jobb;
		}
	}
}

template <class T>
void Binarisfa<T>::kovetkezo()
{
	if (jelenlegi->bal != NULL) /* ha van bal �g, oda l�p�nk */
	{
		jelenlegi = jelenlegi->bal;
		return;
	}
	else if (jelenlegi->jobb != NULL) /* ha nincs, jobbra l�p�nk */
	{
		jelenlegi = jelenlegi->jobb;
		return;
	}
	while (jelenlegi->szulo != NULL) /* levelek lekezel�se, a feljebb l�pked�s miatt akkor �ll meg, ha a gy�k�rhez jutottunk, mert ann�l feljebb nincs, bej�rtuk a f�t, mehet el�r�l */
	{
		if (jelenlegi->szulo->jobb != NULL && jelenlegi->szulo->jobb != jelenlegi) /* ha a sz�l� elem jobb oldali eleme nem azonos a jelenlegivel, oda l�p�nk (bal oldali lev�lben vagyunk) */
		{
			jelenlegi = jelenlegi->szulo->jobb;
			return;
		}
		else if (jelenlegi->szulo != NULL) /* ha a sz�l� jobb oldali eleme egyezik a jelenlegivel, eggyel feljebb kell keresg�ln�nk a jobb oldalt (jobb oldali lev�lben vagyunk, a keres�snek nincs v�ge, mert ezt az elemet m�r megtal�ltuk) */
		{
			jelenlegi = jelenlegi->szulo;
		}
	}
}

template <class T>
bool Binarisfa<T>::vaneaga()
{
	if (jelenlegi == NULL)
		return false;
	return (vane(true) || vane(false));
}

template <class T>
bool Binarisfa<T>::vane(bool bal_e)
{
	if (jelenlegi == NULL)
		return false;
	if (bal_e)
		return jelenlegi->bal != NULL;
	return jelenlegi->jobb != NULL;
}



template <class T>
Lancoltlista<T>::~Lancoltlista()
{
	Elem* temp = elso;
	Elem* mozgo = elso;
	while (mozgo != NULL)
	{
		temp = temp->kovetkezo;
		delete mozgo;
		mozgo = temp;
	}
}

template <class T>
void Lancoltlista<T>::hozzaad(T* ezt)
{
	Elem* mozgo = elso;
	while (mozgo->kovetkezo->kovetkezo != NULL)
		mozgo = mozgo->kovetkezo;
	Elem* temp = new Elem(*ezt, mozgo);
	temp->kovetkezo = mozgo->kovetkezo;
	mozgo->kovetkezo->elozo = temp;
	mozgo->kovetkezo = temp;
	if (listahossz == 0)
	{
		jelenlegi = elso->kovetkezo;
	}
	++listahossz;
	delete ezt;
}

template <class T>
void Lancoltlista<T>::torol()
{
	const char* errmessage = "Hiba: a lista �res!";
	try
	{
		if (listahossz <= 0)
		{
			throw errmessage;
		}
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		exit(EXIT_FAILURE);
	}
	jelenlegi->elozo->kovetkezo = jelenlegi->kovetkezo;
	jelenlegi->kovetkezo->elozo = jelenlegi->elozo;
	Elem* temp;
	if (jelenlegi->kovetkezo->kovetkezo != NULL) /* str�zsa miatt vizsg�lunk */
	{
		temp = jelenlegi->kovetkezo;
	}
	else
	{
		temp = jelenlegi->elozo;
	}
	delete jelenlegi;
	jelenlegi = temp;
	--listahossz;
}

template <class T>
T Lancoltlista<T>::operator[](size_t index)
{
	try
	{
		if (index < 0 || index >= this->getlistahossz())
		{
			throw "Hib�s index!";
		}
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		exit(EXIT_FAILURE);
	}
	Elem* mozgo = elso->kovetkezo;
	for (size_t i = 0; i < index; ++i)
	{
		mozgo = mozgo->kovetkezo;
	}
	return mozgo->adat;
}

template <class T>
void Lancoltlista<T>::lep()
{
	const char* errmessage = "Hiba: a lista �res";
	try
	{
		if (listahossz <= 0)
		{
			throw errmessage;
		}
		if (jelenlegi->kovetkezo->kovetkezo == NULL)
		{
			visszaallit();
		}
		else
		{
			jelenlegi = jelenlegi->kovetkezo;
		}
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		exit(EXIT_FAILURE);
	}
}

template <class T>
void Lancoltlista<T>::visszaallit()
{
	const char* errmessage = "Hiba: a lista �res";
	try
	{
		if (listahossz > 0)
		{
			jelenlegi = elso->kovetkezo;
		}
		else
		{
			throw errmessage;
		}
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		exit(EXIT_FAILURE);
	}
}

template <class T>
T Lancoltlista<T>::lekerdez()
{
	const char* errmessage = "Hiba: a lista �res";
	try
	{
		if (listahossz <= 0)
		{
			throw errmessage;
		}
		return jelenlegi->adat;
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		exit(EXIT_FAILURE);
	}
}

#endif // ADATSZERKEZET_HPP_INCLUDED

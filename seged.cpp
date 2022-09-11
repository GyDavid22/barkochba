#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "adatszerkezet.hpp"
#include "kerdes.h"
#include "valasz.h"
#include "seged.h"
#include "string.h"

#include "memtrace.h"

void mentes(Binarisfa<Kerdes>* kerdesek, Lancoltlista<Valasz>* valaszok)
{
	ofstream db;
	db.open("kerdesek.txt");
	kerdesek->visszagyokerhez();
	for (size_t i = 0; i < kerdesek->getelemszam(); i++)
	{
		db << "KERSZ\t" << kerdesek->getadat()->getkerdes() << "\n";
		db << "IGAID\t" << kerdesek->getadat()->getid(true) << "\n";
		db << "HAMID\t" << kerdesek->getadat()->getid(false) << "\n";
		if (!kerdesek->vane(true))
		{
			db << "LNULL\n";
		}
		if (!kerdesek->vane(false))
		{
			db << "RNULL\n";
		}
		kerdesek->kovetkezo();
	}
	db.close();

	db.open("valaszok.txt");
	valaszok->visszaallit();
	for (size_t i = 0; i < valaszok->getlistahossz(); i++)
	{
		db << valaszok->lekerdez().getvalasz() << "\t" << valaszok->lekerdez().getid() << "\n";
		valaszok->lep();
	}
	db.close();
}

void visszaolvas(Binarisfa<Kerdes>* kerdesek, Lancoltlista<Valasz>* valaszok)
{
	ifstream beolv;
	size_t pos;
	string sor; /* elker�lhetetlen, a getline csak az eredeti stringgel m�k�dik */
	beolv.open("valaszok.txt"); /* v�laszok beolvas�s�nak kezdete */
	if (beolv.good())
	{
		sor = "0";
		getline(beolv, sor);
		while ((!beolv.eof()) && sor != "")
		{
			pos = sor.find("\t");
			if (pos == string::npos)
			{
				valaszok->hozzaad(new Valasz(sor.c_str()));
			}
			else
			{
				valaszok->hozzaad(new Valasz(sor.substr(0, pos).c_str(), sor.substr(pos + 1).c_str()));
			}
			getline(beolv, sor);
		}
		beolv.close();
	}

	beolv.open("kerdesek.txt"); /* k�rd�sek beolvas�s�nak kezdete, el�sz�r egy rugalmasabb, de ideiglenes t�rol�ba */
	if (beolv.good())
	{
		Lancoltlista<String> tempdata;
		sor = "null";
		getline(beolv, sor);
		while ((!beolv.eof()) && sor != "")
		{
			tempdata.hozzaad(new String(sor.c_str()));
			getline(beolv, sor);
		}
		beolv.close();

		if (tempdata.getlistahossz() > 0)
		{
			/* gy�k�r be�ll�t�sa (el�k�sz�t�s) */
			string temp = tempdata.lekerdez().c_str();
			kerdesek->gyokerbeallit(new Kerdes(temp.substr(6).c_str()));
			tempdata.torol();

			/* a fa marad�k r�sz�nek el��ll�t�sa */
			string id = "BXCpFOtnCMJwCVplCtvhn6KDjC9aTsPHbcIachm4day9dY6j15"; /* random gener�lt 50 hossz� karaktersorozat, nem a legszebb, de valahogy meg kell jel�lni azt, hogy hova t�r�nk vissza, sajnos a Lancoltlista oszt�ly nem m�k�d�tt "virtu�lis stack"-k�nt" */
			bool lnull = false;
			bool rnull = false;
			while (tempdata.getlistahossz() > 0)
			{
				temp = tempdata.lekerdez().c_str();
				tempdata.torol();

				if (temp.substr(0, 5) == "IGAID")
				{
					kerdesek->getadat()->setid(true, temp.substr(6).c_str());
				}
				else if (temp.substr(0, 5) == "HAMID")
				{
					kerdesek->getadat()->setid(false, temp.substr(6).c_str());
				}
				else if (temp.substr(0, 5) == "LNULL")
				{
					lnull = true;
				}
				else if (temp.substr(0, 5) == "RNULL")
				{
					rnull = true;
				}
				else if (temp.substr(0, 5) == "KERSZ") /* eddig azt jegyezt�k fel, hogy az adott elemnek milyen tulajdons�gai vannak, a l�trehoz�s most j�n */
				{
					if (!lnull && !rnull)
					{
						kerdesek->beszur(new Kerdes(id.c_str()), false); /* ide visszat�r�nk, megjel�lj�k (el�gaz�s van) */
					}
					if (!lnull)
					{
						kerdesek->beszur(new Kerdes(temp.substr(6).c_str()), true);
						kerdesek->lep(true);
					}
					else if (!rnull)
					{
						kerdesek->beszur(new Kerdes(temp.substr(6).c_str()), false);
						kerdesek->lep(false);
					}
					else /* lev�lhez jutottunk, megkeress�k legk�zelebbi megjel�lt elemet */
					{
						while (kerdesek->getadat()->getkerdes() != id)
						{
							kerdesek->fel();
							if (kerdesek->vane(false))
							{
								kerdesek->lep(false);
								if (kerdesek->getadat()->getkerdes() != id)
								{
									kerdesek->fel();
								}
							}
						}
						kerdesek->fel();
						kerdesek->beszur(new Kerdes(temp.substr(6).c_str()), false);
						kerdesek->lep(false);
					}
					lnull = rnull = false;
				}
			}
		}
	}
}
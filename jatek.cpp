#include <stdlib.h>
#include <string>

#include "jatek.h"
#include "seged.h"
#include "adatszerkezet.hpp"
#include "valasz.h"
#include "kerdes.h"
#include "string.h"

#include "memtrace.h"

using namespace std;

void Jatek::jatekmenet()
{
	bool kilephet = false;
	utolsovalasz = false;
	k->visszagyokerhez();
	while (!kilephet)
	{
		cout << k->getadat()->getkerdes() << endl;
		utolsovalasz = rakerdez();
		if (k->vane(!utolsovalasz))
		{
			k->lep(!utolsovalasz);
		}
		else
		{
			String temp = k->getadat()->getid(utolsovalasz);
			String temp2;
			bool megvan = false;
			size_t i = 0;
			while (i < v->getlistahossz() && !megvan)
			{
				v->lep();
				if ((temp2 = v->lekerdez().getid()) == temp)
				{
					megvan = true;
				}
				++i;
			}
			if (megvan)
			{
				cout << "Gondolkozom... Ez " << v->lekerdez().getvalasz() << "?" << endl;
				bool valasz = rakerdez();
				if (valasz)
				{
					cout << "Nyertem! Nyomj meg egy gombot a f�men�be val� visszal�p�shez!";
					cin.get();
				}
				else
				{
					cout << "Mire gondolt�l? (�kezet n�lk�l!) ";
					string input = "";
					getline(cin, input);
					bool megvan = false;
					size_t i = 0;
					while (i < v->getlistahossz() && !megvan) /* megkeress�k, h�tha m�r szerepel */
					{
						v->lep();
						string temp;
						if ((temp = v->lekerdez().getvalasz()) == input)
							megvan = true;
						++i;
					}
					if (!megvan) /* m�g nem szerepel, felvessz�k */
						v->hozzaad(new Valasz(input.c_str()));
					cout << "Adj meg egy k�rd�st ehhez a fogalomhoz! (�kezet n�lk�l!) ";
					string input2;
					getline(cin, input2);
					k->beszur(new Kerdes(input2.c_str()), !utolsovalasz);
					k->lep(!utolsovalasz);
					cout << "Mi a v�lasz erre a k�rd�sre ennek a fogalomnak az eset�ben?" << endl;
					bool valasz = rakerdez();
					megvan = false;
					i = 0;
					String temp;
					while (i < v->getlistahossz() && !megvan) /* sajnos meg kell keresni, mert nem ugrik oda egyb�l */
					{
						if ((temp = v->lekerdez().getvalasz()) == input)
						{
							megvan = true;
							k->getadat()->setid(valasz, v->lekerdez().getid());
						}
						v->lep();
						++i;
					}
					k->fel();
					String atrakando = k->getadat()->getid(utolsovalasz); /* kicsit �trendezz�k az ID-ket a f�ban, mert a felette l�v�nek is lejjebb kell ker�lie */
					k->getadat()->setid(utolsovalasz, "");
					k->lep(!utolsovalasz);
					k->getadat()->setid(!valasz, atrakando.c_str());
				}
			}
			else
			{
				randomtipp();
			}

			kilephet = true;
		}
	}
}

void Jatek::firstrun()
{
	string input;
	if (v->getlistahossz() == 0)
	{
		cout << "M�g nincs egy fogalom sem a j�t�kban. Add meg az els�t (�kezet n�lk�l!): ";
		getline(cin, input);
		v->hozzaad(new Valasz(input.c_str()));
	}
	if (k->getelemszam() == 0)
	{
		cout << "M�g nincs egy k�rd�s sem a j�t�kban. Add meg az els�t (�kezet n�lk�l!): ";
		getline(cin, input);
		k->gyokerbeallit(new Kerdes(input.c_str()));
	}
}

void Jatek::randomtipp()
{
	size_t random = rand() % v->getlistahossz();
	cout << "Gondolkozom... Ez " << (*v)[random].getvalasz() << "?" << endl;
	bool ezaz = rakerdez();
	if (ezaz)
	{
		cout << "Nyertem! Nyomj meg egy gombot a f�men�be val� visszal�p�shez!";
		k->getadat()->setid(utolsovalasz, (*v)[random].getid());
		cin.get();
	}
	else
	{
		cout << "Mire gondolt�l? (�kezet n�lk�l!) ";
		string input = "";
		getline(cin, input);
		bool megvan = false;
		size_t i = 0;
		while (i < v->getlistahossz() && !megvan) /* megkeress�k, h�tha m�r szerepel */
		{
			v->lep();
			string temp;
			if ((temp = v->lekerdez().getvalasz()) == input)
			{
				megvan = true;
				k->getadat()->setid(utolsovalasz, v->lekerdez().getid());
			}
			++i;
		}
		if (!megvan) /* m�g nem szerepel, felvessz�k */
		{
			v->hozzaad(new Valasz(input.c_str()));
			megvan = false;
			i = 0;
			while (i < v->getlistahossz() && !megvan) /* sajnos megint meg kell keresni, mert nem ugrik oda egyb�l */
			{
				v->lep();
				string temp;
				if ((temp = v->lekerdez().getvalasz()) == input)
				{
					megvan = true;
					k->getadat()->setid(utolsovalasz, v->lekerdez().getid());
				}
			}
		}
	}
}

bool Jatek::rakerdez()
{
	bool valasz = false;
	cout << " 1) Igen" << endl
		<< " 2) Nem" << endl;
	bool ok = false;
	int input2 = 0;
	while (!ok)
	{
		ok = true;
		input2 = 0;
		cin >> input2;
		cin.get();
		switch (input2)
		{
		case 1:
			valasz = true;
			break;
		case 2:
			valasz = false;
			break;
		default:
			ok = false;
			break;
		}
	}
	return valasz;
}
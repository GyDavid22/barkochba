#include <iostream>
#include <stdlib.h>
#include "time.h"

using namespace std;

#include "adatszerkezet.hpp"
#include "valasz.h"
#include "kerdes.h"
#include "seged.h"
#include "jatek.h"

#include "memtrace.h"

int main()
{
    setlocale(LC_ALL, "HUN"); /* magyar karakterek */
    srand(time(0)); /* random gener�l�s el�k�sz�t�se */

    Lancoltlista<Valasz>* valaszok = new Lancoltlista<Valasz>();
    Binarisfa<Kerdes>* kerdesek = new Binarisfa<Kerdes>();
    visszaolvas(kerdesek, valaszok);
    Jatek jatek(kerdesek, valaszok);
    if (valaszok->getlistahossz() == 0 || kerdesek->getelemszam() == 0)
    {
        jatek.firstrun();
    }

    bool run = true;
    int valasz = 0;
    while (run)
    {
        system("cls"); /* olvastam, hogy nem a legbiztons�gosabb, de jobb megold�st nem tudok */
        cout << "�dv�z�l a barkochba! V�lassz egyet az al�bbi men�pontokb�l!" << endl
            << " 1) J�t�k" << endl
            << " 2) N�vjegy" << endl
            << " 3) Kil�p�s" << endl;
        valasz = 0;
        cin >> valasz;
        cin.get();
        switch (valasz)
        {
        case 1:
            system("cls");
            jatek.jatekmenet();
            mentes(kerdesek, valaszok); /* jobb ilyenkor menteni, mert ha az user nem a 3-as men�ponttal l�p ki, nem lesznek elmentve a v�ltoz�sok */
            break;
        case 2:
            system("cls");
            cout << "Barkochba 1.1" << endl
                << "K�sz�tette: Gyenes D�vid, 2021" << endl
                << "K�sz�lt a BME m�rn�kinformatikus BSc k�p�s�hez, A programoz�s alapjai 2. nev� t�rgy nagy h�zi feladatak�nt, C++-ban." << endl
                << "A men�be val� visszal�p�shez nyomd meg az entert!";
            cin.get();
            break;
        case 3:
            run = false;
            break;
        default:
            break;
        }
    }
    delete kerdesek;
    delete valaszok;
    return 0;
}

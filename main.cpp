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
    srand(time(0)); /* random generálás elõkészítése */

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
        system("cls"); /* olvastam, hogy nem a legbiztonságosabb, de jobb megoldást nem tudok */
        cout << "Üdvözöl a barkochba! Válassz egyet az alábbi menüpontokból!" << endl
            << " 1) Játék" << endl
            << " 2) Névjegy" << endl
            << " 3) Kilépés" << endl;
        valasz = 0;
        cin >> valasz;
        cin.get();
        switch (valasz)
        {
        case 1:
            system("cls");
            jatek.jatekmenet();
            mentes(kerdesek, valaszok); /* jobb ilyenkor menteni, mert ha az user nem a 3-as menüponttal lép ki, nem lesznek elmentve a változások */
            break;
        case 2:
            system("cls");
            cout << "Barkochba 1.1" << endl
                << "Készítette: Gyenes Dávid, 2021" << endl
                << "Készült a BME mérnökinformatikus BSc képéséhez, A programozás alapjai 2. nevû tárgy nagy házi feladataként, C++-ban." << endl
                << "A menübe való visszalépéshez nyomd meg az entert!";
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

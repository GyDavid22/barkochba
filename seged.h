#ifndef SEGED_H_INCLUDED
#define SEGED_H_INCLUDED

#include "adatszerkezet.hpp"
#include "kerdes.h"
#include "valasz.h"

#include "memtrace.h"

void mentes(Binarisfa<Kerdes>* ezt, Lancoltlista<Valasz>* valaszok);
void visszaolvas(Binarisfa<Kerdes>* kerdesek, Lancoltlista<Valasz>* valaszok);

#endif // SEGED_H_INCLUDED


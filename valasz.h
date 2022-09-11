#ifndef VALASZ_H_INCLUDED
#define VALASZ_H_INCLUDED

#include "string.h"
#include "adatszerkezet.hpp"

#include "memtrace.h"

class Valasz
{
    String valasz;
    String id;
    const int idhossz = 50;
public:
    Valasz() { }
    Valasz(const char* val);
    Valasz(const char* val, const char* id2) : valasz(val), id(id2) { }
    Valasz(const Valasz& masik) : valasz(masik.valasz), id(masik.id) { }
    ~Valasz() { };

    const char* getvalasz() { return valasz.c_str(); }
    const char* getid() { return id.c_str(); }
    void genid();
    Valasz& operator=(Valasz& rhs);
};

#endif // VALASZ_H_INCLUDED

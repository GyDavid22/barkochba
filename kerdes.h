#ifndef KERDES_H_INCLUDED
#define KERDES_H_INCLUDED

#include "string.h"
#include "valasz.h"

#include "memtrace.h"

class Kerdes
{
    String kerdes;
    String igazvalaszid;
    String hamisvalaszid;
public:
    Kerdes() { };
    Kerdes(const char* szoveg);
    Kerdes(const char* szoveg, const char* id, bool igaz_e);
    Kerdes(const char* szoveg, const char* igazid, const char* hamisid);
    ~Kerdes() { }

    bool idegyezik(Valasz &ezzel, bool igaz_e);
    const char* getkerdes() { return Kerdes::kerdes.c_str(); }
    const char* getid(bool igazt_e) { if (igazt_e) return Kerdes::igazvalaszid.c_str(); return Kerdes::hamisvalaszid.c_str(); }
    void setid(bool igazt_e, const char* erre) { if (igazt_e) { igazvalaszid = erre; } else { hamisvalaszid = erre; } }
};

#endif // KERDES_H_INCLUDED

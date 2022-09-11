#include "kerdes.h"
#include "adatszerkezet.hpp"

#include "memtrace.h"

Kerdes::Kerdes(const char* szoveg)
{
    this->kerdes = szoveg;
    setid(true, "");
    setid(false, "");
}

bool Kerdes::idegyezik(Valasz &ezzel, bool igaz_e)
{
    return this->getid(igaz_e) == ezzel.getid();
}

Kerdes::Kerdes(const char* szoveg, const char* id, bool igaz_e)
{
    setid(igaz_e, id);
    setid(!igaz_e, "");
    this->kerdes = szoveg;
}

Kerdes::Kerdes(const char* szoveg, const char* igazid, const char* hamisid)
{
    setid(true, igazid);
    setid(false, hamisid);
    this->kerdes = szoveg;
}

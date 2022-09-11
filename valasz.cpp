#include <string>
#include "valasz.h"
#include "seged.h"

#include "memtrace.h"

Valasz::Valasz(const char* val)
{
	valasz = val;
	genid();
}

void Valasz::genid()
{
	/* 32-től 126-ig kell menni */
	const int min = 32;
	const int max = 126;
	char* temp = new char[idhossz + 1];
	for (int i = 0; i < idhossz; ++i)
	{
		temp[i] = min + rand() % ((max + 1) - min);
	}
	temp[idhossz] = '\0';
	this->id = temp;
	delete[] temp;
}

Valasz& Valasz::operator=(Valasz& rhs)
{
	if (this == &rhs)
		return *this;
	valasz = rhs.getvalasz();
	id = rhs.getid();
	return *this;
}

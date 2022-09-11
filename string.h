#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <string>

#include "memtrace.h"

class String {
    char *pData;
    size_t len;
public:
    String() :pData(0), len(0) { pData = new char[1]; pData[0] = '\0'; }
    size_t size() const { return len; }
    const char* c_str() const { return pData;}
    ~String() { delete[] pData; }
    String(const char betu);
    String(const char* string);
    String& operator=(const String &rhs);
    const char& operator[](unsigned int index) const;
    String(const String& original);
    bool operator==(const String &rhs);
    String(const std::string &rhs) : String(rhs.c_str()) { }
};

std::ostream& operator<<(std::ostream& os, const String& s0);

#endif

#include <iostream>
#include <cstring>

#include "string.h"

#include "memtrace.h"

String::String(const char betu)
{
    len = 1;
    pData = new char[len + 1];
    pData[0] = betu;
    pData[1] = '\0';
}

String::String(const char* string)
{
    len = 0;
    while (string[len] != '\0')
    {
        len++;
    }
    pData = new char[len + 1];
    for (size_t i = 0; i < len; i++)
    {
        pData[i] = string[i];
    }
    pData[len] = '\0';
}

String::String(const String& original)
{
    this->len = original.len;
    this->pData = new char[this->len + 1];
    for (size_t i = 0; i < this->len; i++)
    {
        this->pData[i] = original[i];
    }
    this->pData[this->len] = '\0';
}

String& String::operator=(const String& rhs)
{
    if (&rhs != this)
    {
        delete[] this->pData;
        this->len = rhs.len;
        this->pData = new char[this->len + 1];
        for (size_t i = 0; i < this->len; i++)
        {
            this->pData[i] = rhs[i];
        }
        this->pData[this->len] = '\0';
    }
    return *this;
}

const char& String::operator[](unsigned int index) const
{
    if (index < 0 || index >= len)
    {
        throw "rossz index";
    }
    else
    {
        return pData[index];
    }
}

bool String::operator==(const String &rhs)
{
    if (this->size() != rhs.size())
    {
        return false;
    }
    for (size_t i = 0; i < this->size(); ++i)
    {
        if (this->c_str()[i] != rhs.c_str()[i])
        {
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const String& s0)
{
    return os << s0.c_str();
}
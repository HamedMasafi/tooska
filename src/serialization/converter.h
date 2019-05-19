#ifndef CONVERTER_H
#define CONVERTER_H

#include "../global.h"

TOOSKA_BEGIN_NAMESPACE(serialization)


template<typename T>
class converter
{
public:
    void read(T &t)
    {}
};

template<typename T>
void read(T &t, const std::string &value);

template<>
void read(int &n, const std::string &s);

template<>
void read(float &f, const std::string &s);

template<>
void read(long &l, const std::string &s);

template<>
void read(bool &b, const std::string &s);

template<>
void read(double &d, const std::string &s);

template<>
void read(std::string &d, const std::string &s);

TOOSKA_END_NAMESPACE

#endif // CONVERTER_H

#include <iostream>

#include "converter.h"

TOOSKA_BEGIN_NAMESPACE(serialization)

//converter()
//{

//}

template<typename T>
void read(T &t, const std::string &value)
{
    (void)t;
    (void)value;
}

template<>
void read<int>(int &n, const std::string &s)
{
    try {
        std::size_t i;
        int b = std::stoi(s, &i);
        if (i == s.length())
            n = b;
    } catch (std::exception ex) {
        std::cout << "invalid int from " << s << std::endl;
    }
}

template<>
void read(float &f, const std::string &s)
{
    try {
        std::size_t i;
        float b = std::stof(s, &i);
        if (i == s.length())
            f = b;
    } catch (std::exception ex) {
    }
}

template<>
void read(long &l, const std::string &s)
{
    try {
        std::size_t i;
        long b = std::stol(s, &i);
        if (i == s.length())
            l = b;
    } catch (std::exception ex) {
    }
}

template<>
void read(bool &b, const std::string &s)
{
    if (s == "true")
        b = true;
    else if (s == "false")
        b = false;
}

template<>
void read(double &d, const std::string &s)
{
    try {
        std::size_t i;
        double b = std::stod(s, &i);
        if (i == s.length())
            d = b;
    } catch (std::exception ex) {
    }
}
template<>
void read(std::string &r, const std::string &s)
{
    r = s;
}

TOOSKA_END_NAMESPACE


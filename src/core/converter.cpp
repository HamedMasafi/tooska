#include <iostream>

#include "converter.h"

TOOSKA_BEGIN_NAMESPACE(core)

namespace converter {

template<typename T>
void read(T &t, const std::string &value)
{
    (void)t;
    (void)value;
}

template<>
void read<int>(int &n, const std::string &s)
{
    n = std::atoi(s.c_str());
//    try {
//        std::size_t i;
//        int b = std::stoi(s, &i);
//        if (i == s.length())
//            n = b;
//    } catch (std::exception ex) {
//        std::cout << "invalid int from " << s << std::endl;
//    }
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



template<typename T>
void write(const T &t, std::string &value)
{

}

template<>
void write(const int &n, std::string &s)
{
    s = std::to_string(n);
}

template<>
void write(const float &f, std::string &s)
{
    s = std::to_string(f);
}

template<>
void write(const long &l, std::string &s)
{
    s = std::to_string(l);
}

template<>
void write(const bool &b, std::string &s)
{
    s = std::to_string(b);
}

template<>
void write(const double &d, std::string &s)
{
    s = std::to_string(d);
}

template<>
void write(const std::string &d, std::string &s)
{
    s = d;
}
}

TOOSKA_END_NAMESPACE

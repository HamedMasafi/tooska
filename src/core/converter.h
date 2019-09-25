#ifndef CONVERTER_H
#define CONVERTER_H

#include "../global.h"
#include <iostream>

TOOSKA_BEGIN_NAMESPACE(core)

namespace converter
{
template <class T,
         std::enable_if_t<std::is_integral<T>::value, int> = 0
         >
T from_string(const std::string &s)
{
    try {
        std::size_t i;
        int b = std::stoi(s, &i);
        if (i == s.length())
            return b;
    } catch (std::exception ex) {
        std::cout << "invalid int from " << s << std::endl;
    }
}

template <class T,
         std::enable_if_t<std::is_floating_point<T>::value, int> = 0
         >
T from_string(const std::string &s)
{
    try {
        std::size_t i;
        float b = std::stof(s, &i);
        if (i == s.length())
            return b;
    } catch (std::exception ex) {
    }
}

template <class T, typename std::enable_if<std::is_base_of<std::string, T>::value>::type* = nullptr>
T from_string(const std::string &s)
{
    return s;
}

//read
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

//write
template<typename T>
void write(const T &t, std::string &value);

template<>
void write(const int &n, std::string &s);

template<>
void write(const int &n, std::string &s);

template<>
void write(const float &f, std::string &s);

template<>
void write(const long &l, std::string &s);

template<>
void write(const bool &b, std::string &s);

template<>
void write(const double &d, std::string &s);

template<>
void write(const std::string &d, std::string &s);

TOOSKA_END_NAMESPACE

}

#endif // CONVERTER_H

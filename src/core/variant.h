#ifndef VARIANT_H
#define VARIANT_H

#define FOR_EACH_TYPES(x,s) \
    x(char) \
    x(char16_t) \
    x(char32_t) \
    x(short) \
    x(int) \
    x(long) \
    x(long long) \
    x(unsigned int) \
    x(unsigned long) \
    x(unsigned long long) \
    x(std::string) \
    x(long double) \
    x(double)

#include "../global.h"
#include <string>

TOOSKA_BEGIN_NAMESPACE(core)

class variant
{
    union {
        long long n;
        double d;
    } _data;

public:
    enum type_t {
        char_t,
        char16_t_t,
        char32_t_t,
        short_t,
        int_t,
        long_t,
        long_long_t,
        unsigned_int_t,
        unsigned_long_t,
        unsigned_long_long_t,
        string_t,
        long_double_t,
        double_t
    };

    variant();
#define x(type) variant(const type &val);
    FOR_EACH_TYPES(x,)
#undef x
};

TOOSKA_END_NAMESPACE

#endif // VARIANT_H

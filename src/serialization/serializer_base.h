#ifndef SERIALIZER_BASE_H
#define SERIALIZER_BASE_H

#include <string>
#include "../global.h"
#include "../json/json_object.h"
#include "../json/json_value.h"
#include "serializable.h"
#include "../core/converter.h"
#include "serializable.h"

#define FOR_EACH_TYPES(x) \
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
    x(std::wstring) \
    x(long double) \
    x(double)

TOOSKA_BEGIN_NAMESPACE(serialization)

class serializer_base
{
public:
    enum mode_t {
        Unset,
        Deserialize,
        Serialize
    } mode;

    serializer_base(mode_t mode) : mode(mode)
    {}

#define x(type) void set(const std::string &name, const type &value) {}
    FOR_EACH_TYPES(x)
#undef x

    void set(const std::string &name, serializable *object)
    {}
};

template<class N>
class serializer : public serializer_base
{
public:
    serializer() : serializer_base(Unset)
    {}
};

TOOSKA_END_NAMESPACE

#endif // SERIALIZER_BASE_H

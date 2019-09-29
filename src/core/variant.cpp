#include "variant.h"

TOOSKA_BEGIN_NAMESPACE(core)

variant::variant()
{
    _type = invalid;
}

#define x(type, name) variant::variant(const type &value) { \
  _data.name##_t = value; \
  _type = name##_t; \
}
FOR_EACH_TYPES(x)
#undef x

variant::variant(const char *data)
{
    s = data;
    _type = string_t;
}

variant::variant(const std::string &value)
{
    s = value;
    _type = string_t;
}

//variant::variant(const variant &other)
//{
//    _data = other._data;
//    s = other.s;
//    _type = other._type;
//}

//variant::variant(variant &&other)
//{
//    _data = std::move(other._data);
//    s = std::move(other.s);
//    _type = std::move(other._type);
//}

TOOSKA_END_NAMESPACE

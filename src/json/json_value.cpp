#include "json_value.h"
#include "json_object.h"
#include "json_array.h"
#include "../core/string_renderer.h"
#include "../core/string_helper.h"

#include <algorithm>

TOOSKA_BEGIN_NAMESPACE(json)

value::value() : _type(type_t::invalid)
{ }

value::value(const bool &b) : _b(b), _type(type_t::bool_t)
{ }

value::value(const int &n) : _n(n), _type(type_t::int_t)
{ }

value::value(const float &f) : _f(f), _type(type_t::float_t)
{ }

value::value(const std::string &value) : _s(value), _type(type_t::string_t)
{ }

value::~value()
{

}

value::type_t value::type() const
{
    return _type;
}

json_array *value::to_array()
{
    if (_type == type_t::array_t)
        return dynamic_cast<json_array*>(this);
    else
        return nullptr;
}

json_object *value::to_object()
{
    if (_type == type_t::object_t)
        return dynamic_cast<json_object*>(this);
    else
        return nullptr;
}

std::string value::to_string() const
{
    return _s;
}

float value::to_float() const
{
    return _f;
}

bool value::to_bool() const
{
    return _b;
}

int value::to_int() const
{
    return _n;
}

void value::render(core::string_renderer &r)
{
    auto val = _s;
//    bool single_cotation = false;
//    bool double_cotation = false;
//    std::for_each(val.begin(), val.end(), [&](int ch){
//        if (ch == '\'')
//            single_cotation = true;
//        if (ch == '"')
//            double_cotation = true;
//    });

//    if (single_cotation && double_cotation)
        core::string_helper::replace(val, "\"", "\\\"");

    switch (_type) {
    case type_t::string_t:
        r.append("\"");
        r.append(val);
        r.append("\"");
        break;

    case type_t::invalid:
        r.append("null");
        break;

    case type_t::bool_t:
        r.append(_b ? "true" : "false");
        break;

    case type_t::int_t:
        r.append(std::to_string(_n));
        break;

    case type_t::float_t:
        r.append(std::to_string(_f));
        break;

    default:
        r.append("INVALID");
    }
}

TOOSKA_END_NAMESPACE

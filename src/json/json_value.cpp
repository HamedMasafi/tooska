#include "json_value.h"
#include "json_object.h"
#include "json_array.h"
#include "../core/string_renderer.h"
#include "../core/string_helper.h"

#include <algorithm>

TOOSKA_BEGIN_NAMESPACE(json)

json_value::json_value() : _type(type_t::invalid)
{ }

json_value::json_value(const bool &b) : _b(b), _type(type_t::bool_t)
{ }

json_value::json_value(const int &n) : _n(n), _type(type_t::int_t)
{ }

json_value::json_value(const float &f) : _f(f), _type(type_t::float_t)
{ }

json_value::json_value(const std::string &value) : _s(value), _type(type_t::string_t)
{ }

json_value::~json_value()
{

}

json_value::type_t json_value::type() const
{
    return _type;
}

json_array *json_value::to_array()
{
    if (_type == type_t::array_t)
        return dynamic_cast<json_array*>(this);
    else
        return nullptr;
}

json_object *json_value::to_object()
{
    if (_type == type_t::object_t)
        return dynamic_cast<json_object*>(this);
    else
        return nullptr;
}

std::string json_value::to_string() const
{
    return _s;
}

float json_value::to_float() const
{
    return _f;
}

bool json_value::to_bool() const
{
    return _b;
}

int json_value::to_int() const
{
    return _n;
}

void json_value::render(core::string_renderer &r)
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

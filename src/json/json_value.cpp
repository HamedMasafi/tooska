#include "json_value.h"
#include "json_object.h"
#include "json_array.h"
#include "../core/string_renderer.h"
#include "../core/string_helper.h"

#include <algorithm>

TOOSKA_BEGIN_NAMESPACE(json)

value::value() : _type(type_t::invalid), _data()
{ }

value::value(const tooska::core::variant &value) : _data(value)
{
    if (value.is_integral())
        _type = type_t::int_t;
    else if (value.is_floating_point())
        _type = type_t::float_t;
    else if (value.type() == tooska::core::variant::string_t)
        _type = type_t::string_t;
    else
        _type = type_t::invalid;
}

value::~value()
{

}

value::type_t value::type() const
{
    return _type;
}

array *value::to_array()
{
    if (_type == type_t::array_t)
        return dynamic_cast<array*>(this);
    else
        return nullptr;
}

object *value::to_object()
{
    if (_type == type_t::object_t)
        return dynamic_cast<object*>(this);
    else
        return nullptr;
}

std::string value::to_string() const
{
    return _data.to_string();
}

float value::to_float() const
{
    return _data.to_float();
}

bool value::to_bool() const
{
    return _data.to_bool();
}

int value::to_int() const
{
    return _data.to_int();
}

void value::render(core::string_renderer &r)
{
//    auto val = _s;
//    core::string_helper::replace(val, "\"", "\\\"");

    switch (_data.type()) {
    case tooska::core::variant::invalid:
        r.append("null");
        break;
    case tooska::core::variant::string_t:
        r.append("\"");
        r.append(_data.to_string());
        r.append("\"");
        break;
    default:
        r.append(_data.to_string());
        break;
    }
}

tooska::core::variant value::data() const
{
    return _data;
}

TOOSKA_END_NAMESPACE


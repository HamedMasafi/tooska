#include "json_value.h"
#include "json_object.h"
#include "json_array.h"
#include "../core/string_renderer.h"
#include "../core/string_helper.h"
#include "json_value_data.h"

#include <algorithm>

TOOSKA_BEGIN_NAMESPACE(json)

json_value::json_value(const json_value &other)
{
    _data = other._data;
}

json_value::json_value(json_value &&other)
{
    _data = std::move(other._data);
}

json_value::json_value() : _data(new json_value_data)
{ }

json_value::json_value(const bool &b) : _data(new json_value_data(b))
{ }

json_value::json_value(const int &n) : _data(new json_value_data(n))
{ }

json_value::json_value(const float &f) : _data(new json_value_data(f))
{ }

json_value::json_value(const std::string &value) : _data(new json_value_data(value))
{ }

json_value::json_value(const char *value)
    : _data(new json_value_data(std::string(value)))
{

}

json_value::~json_value()
{
//    delete _data;
}

json_value &json_value::operator =(const json_value &other)
{
    _data = other._data;
    return *this;
}

json_value::type_t json_value::type() const
{
    return _data->type;
}

json_array json_value::to_array() const
{
    if (_data->type == type_t::array_t)
        return json_array(static_cast<json_array_data*>(_data));
//                static_cast<json_array&>(*this);
    else
        return json_array();
}

json_object json_value::to_object() const
{
    if (_data->type == type_t::object_t)
        return json_object(static_cast<json_object_data*>(_data));
    else
        return json_object();
}

json_value json_value::null()
{
    json_value v;
    v._data->type = type_t::null_t;
    return v;
}

bool json_value::is_valid() const
{
    return _data->type != type_t::invalid;
}

std::string json_value::to_string() const
{
    return _data->_s;
}

float json_value::to_float() const
{
    return _data->_data.f;
}

bool json_value::to_bool() const
{
    return _data->_data.b;
}

int json_value::to_int() const
{
    return _data->_data.n;
}

void json_value::render(core::string_renderer &r) const
{
    _data->render(r);
//    auto val = _data->_s;

//    core::string_helper::replace(val, "\"", "\\\"");

//    switch (_data->type) {
//    case type_t::string_t:
//        r.append("\"");
//        r.append(val);
//        r.append("\"");
//        break;

//    case type_t::invalid:
//        r.append("null");
//        break;

//    case type_t::bool_t:
//        r.append(_data->_data.b ? "true" : "false");
//        break;

//    case type_t::int_t:
//        r.append(std::to_string(_data->_data.n));
//        break;

//    case type_t::float_t:
//        r.append(std::to_string(_data->_data.f));
//        break;

//    default:
//        r.append("INVALID");
//    }
}

TOOSKA_END_NAMESPACE

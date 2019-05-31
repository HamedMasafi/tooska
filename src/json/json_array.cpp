#include <algorithm>

#include "json_array.h"
#include "json_value.h"
#include "json_value_data.h"
#include "../core/string_renderer.h"

TOOSKA_BEGIN_NAMESPACE(json)

json_array::json_array(json_array_data *data) : _array_data(data)
{
}

json_array::json_array() : json_value(), _array_data(new json_array_data)
{
    json_value::_data = _array_data;
}

json_array::json_array(const json_array &other)
{
    _array_data = other._array_data;
    json_value::_data = _array_data;
}

json_array::json_array(json_array &&other)
{
    _array_data = std::move(other._array_data);
    json_value::_data = _array_data;
}

json_array &json_array::operator =(const json_array &other)
{
    _array_data = other._array_data;
    json_value::_data = _array_data;
    return *this;
}

json_array::~json_array()
{
    //    delete _array_data;
}

void json_array::add(json_value v)
{
    _array_data->values.push_back(v);
}

json_value json_array::at(const size_t &pos) const
{
    return _array_data->values.at(pos);
}

const json_value json_array::operator[](const size_t &i) const
{
    return _array_data->values[i];
}

json_value json_array::operator[](const size_t &i)
{
    return _array_data->values[i];
}

//void json_array::render(core::string_renderer &r) const
//{
//    if (!_array_data->values.size()) {
//        r.append("[]");
//        return;
//    }

//    bool is_simple = std::all_of(_array_data->values.begin(), _array_data->values.end(), [](json_value v){
//            auto t = v.type();
//            return t == type_t::int_t || t == type_t::float_t || t == type_t::string_t;
//    });
//    r.append("[");
//    if (!is_simple) {
//        r.new_line();
//        r.indent();
//    }
//    auto count = _array_data->values.size();
//    for (auto i = _array_data->values.begin(); i != _array_data->values.end(); ++i) {
//        (*i).render(r);

//        if (--count) {
//            r.append(",");
//            r.space();
//        }

//        if (!is_simple)
//            r.new_line();
//    }
//    if (!is_simple) {
//        r.new_line();
//        r.unindent();
//    }
//    r.append("]");
//}

void json_array::for_each(const std::function<void (json_value )> &callback)
{
    std::for_each(_array_data->values.begin(), _array_data->values.end(), callback);
}

TOOSKA_END_NAMESPACE


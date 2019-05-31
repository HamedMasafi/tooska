#include <algorithm>
#include <iostream>

#include "json_object.h"
#include "json_value.h"
#include "json_value_data.h"
#include "../core/string_renderer.h"

TOOSKA_BEGIN_NAMESPACE(json)

json_object::json_object(json_object_data *data) : _object_data(data)
{
    json_value::_data = _object_data;
}

json_object::json_object() : json_value (), _object_data(new json_object_data)
{
    json_value::_data = _object_data;
}

json_object::json_object(const json_object &other)
{
    _object_data = other._object_data;
    json_value::_data = _object_data;
}

json_object::json_object(json_object &&other)
{
    _object_data = std::move(other._object_data);
    json_value::_data = _object_data;
}

json_object::json_object(std::initializer_list<std::pair<std::string, json_value> > args)
{
    std::initializer_list<std::pair<std::string, json_value> >::const_iterator i;
    for (i = args.begin(); i != args.end(); ++i) {
        insert(i->first, i->second);
    }
}

json_object::~json_object()
{

}

json_object &json_object::operator =(const json_object &other)
{
    _object_data = other._object_data;
    json_value::_data = _object_data;
    return *this;
}

void json_object::insert(const std::string &name, const json_value &value)
{
    _object_data->values[name] = value;
}

void json_object::insert(const std::string &name, json_value &&value)
{
    _object_data->values[name] = std::move(value);
}

bool json_object::has_key(const std::string &key) const
{
    return _object_data->values.find(key) != _object_data->values.end();
}

json_value json_object::get(const std::string &name)
{
    return _object_data->values[name];
}

json_value json_object::operator[](const std::string &name)
{
    return _object_data->values[name];
}

//void json_object::render(core::string_renderer &r) const
//{

//    auto count = _object_data->values.size();

//    bool is_simple = count < 3 && std::all_of(_object_data->values.begin(), _object_data->values.end(), [](std::map<std::string, json_value>::const_reference it){
//        auto t = it.second.type();
//        return t == type_t::int_t || t == type_t::float_t || t == type_t::string_t;
//    });

//    r.append("{");
//    if (!is_simple) {
//        r.new_line();
//        r.indent();
//    }
//    for (auto i = _object_data->values.cbegin(); i != _object_data->values.cend(); ++i) {
//        r.append("\"");
//        r.append((*i).first);
//        r.append("\":");
//        r.space();
//        (*i).second.render(r);

//        if (--count)
//            r.append(",");

//        if (!is_simple)
//            r.new_line();
//    }

//    if (!is_simple) {
//        r.new_line();
//        r.unindent();
//    }
//    r.append("}");
//}

TOOSKA_END_NAMESPACE

#include <algorithm>
#include <iostream>

#include "json_object.h"
#include "json_value.h"
#include "../core/string_renderer.h"

TOOSKA_BEGIN_NAMESPACE(json)

object::object() : value ()
{
    _type = type_t::object_t;
}

object::object(std::initializer_list<std::pair<std::string, value> > args)
{
    _type = type_t::object_t;
    std::initializer_list<std::pair<std::string, value> >::const_iterator i;
    for (i = args.begin(); i != args.end(); ++i) {
//        insert(i->first, &i->second);
    }
}

object::~object()
{

}

void object::insert(const std::string &name, value *value)
{
    _values[name] = value;
}

bool object::has_key(const std::string &name)
{
    return _values.find(name) != _values.end();
}

value *object::get(const std::string &name)
{
    return _values[name];
}

value *object::operator[](const std::string &name)
{
    return _values[name];
}

void object::render(core::string_renderer &r)
{

    auto count = _values.size();

    bool is_simple = std::all_of(_values.begin(), _values.end(), [](std::map<std::string, value*>::const_reference it){
            auto t = it.second->type();
            return t == type_t::int_t || t == type_t::float_t || t == type_t::string_t;
}) && count < 3;

    r.append("{");
    if (!is_simple) {
        r.new_line();
        r.indent();
    }
    for (auto i = _values.cbegin(); i != _values.cend(); ++i) {
        r.append("\"");
        r.append((*i).first);
        r.append("\":");
        r.space();
        (*i).second->render(r);

        if (--count)
            r.append(",");

        if (!is_simple)
            r.new_line();
    }

    if (!is_simple) {
        r.new_line();
        r.unindent();
    }
    r.append("}");
}

TOOSKA_END_NAMESPACE

#include <algorithm>

#include "json_array.h"
#include "json_value.h"
#include "../core/string_renderer.h"

TOOSKA_BEGIN_NAMESPACE(json)

array::array() : value()
{
    _type = type_t::array_t;
}

array::~array()
{

}

void array::add(value *v)
{
    _values.push_back(v);
}

value *array::at(const size_t &pos) const
{
    return _values.at(pos);
}

const value *array::operator[](const size_t &i) const
{
    return _values[i];
}

value *array::operator[](const size_t &i)
{
    return _values[i];
}

void array::render(core::string_renderer &r)
{
    if (!_values.size()) {
        r.append("[]");
        return;
    }

    bool is_simple = std::all_of(_values.begin(), _values.end(), [](value *v){
            auto t = v->type();
            return t == type_t::int_t || t == type_t::float_t || t == type_t::string_t;
    });
    r.append("[");
    if (!is_simple) {
        r.new_line();
        r.indent();
    }
    auto count = _values.size();
    for (auto i = _values.begin(); i != _values.end(); ++i) {
        (*i)->render(r);

        if (--count) {
            r.append(",");
            r.space();
        }

        if (!is_simple)
            r.new_line();
    }
    if (!is_simple) {
        r.new_line();
        r.unindent();
    }
    r.append("]");
}

void array::for_each(const std::function<void (value *)> &callback)
{
    std::for_each(_values.begin(), _values.end(), callback);
}

TOOSKA_END_NAMESPACE

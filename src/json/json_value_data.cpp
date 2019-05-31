#include <algorithm>
#include "json_value_data.h"
#include "../core/string_renderer.h"
#include "../core/string_helper.h"

TOOSKA_BEGIN_NAMESPACE(json)

json_value_data::json_value_data() : type(json_value::type_t::invalid)
{}



json_value_data::json_value_data(json_value::type_t type) : type(type)
{}



json_value_data::json_value_data(const bool &b) : type(json_value::type_t::bool_t)
{
    _data.b = b;
}



json_value_data::json_value_data(const int &n) : type(json_value::type_t::int_t)
{
    _data.n = n;
}



json_value_data::json_value_data(const float &f) : type(json_value::type_t::float_t)
{
    _data.f = f;
}



json_value_data::json_value_data(const std::string &value)
    : type(json_value::type_t::string_t), _s(value)
{}



void json_value_data::render(core::string_renderer &r)
{
    auto val = _s;

    core::string_helper::replace(val, "\"", "\\\"");

    switch (type) {
    case json_value::type_t::string_t:
        r.append("\"");
        r.append(val);
        r.append("\"");
        break;

    case json_value::type_t::null_t:
        r.append("null");
        break;

    case json_value::type_t::bool_t:
        r.append(_data.b ? "true" : "false");
        break;

    case json_value::type_t::int_t:
        r.append(std::to_string(_data.n));
        break;

    case json_value::type_t::float_t:
        r.append(std::to_string(_data.f));
        break;

    default:
        r.append("INVALID");
    }
}



json_object_data::json_object_data() : json_value_data(json_value::type_t::object_t)
{}



void json_object_data::render(core::string_renderer &r)
{
    auto count = values.size();

    bool is_simple = count < 3 && std::all_of(values.begin(), values.end(), [](std::map<std::string, json_value>::const_reference it){
            auto t = it.second.type();
            return t == json_value::type_t::int_t
            || t == json_value::type_t::float_t
            || t == json_value::type_t::string_t;
});

    r.append("{");
    if (!is_simple) {
        r.new_line();
        r.indent();
    }
    for (auto i = values.cbegin(); i != values.cend(); ++i) {
        r.append("\"");
        r.append((*i).first);
        r.append("\":");
        r.space();
        (*i).second.render(r);

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



json_array_data::json_array_data() : json_value_data(json_value::type_t::array_t)
{}



void json_array_data::render(core::string_renderer &r)
{
    if (!values.size()) {
        r.append("[]");
        return;
    }

    bool is_simple = std::all_of(values.begin(), values.end(), [](json_value v){
            auto t = v.type();
            return t == json_value::type_t::int_t
            || t == json_value::type_t::float_t
            || t == json_value::type_t::string_t;
});
    r.append("[");
    if (!is_simple) {
        r.new_line();
        r.indent();
    }
    auto count = values.size();
    for (auto i = values.begin(); i != values.end(); ++i) {
        (*i).render(r);

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

TOOSKA_END_NAMESPACE

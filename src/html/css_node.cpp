#include "css_node.h"
#include "css_p.h"

#include <algorithm>
#include "../core/string_renderer.h"

TOOSKA_BEGIN_NAMESPACE(html)

css_node::css_node() : _data(new css_node_data)
{

}

css_node::css_node(const css_node &other)
{
    _data = other._data;
}

css_node::css_node(css_node &&other)
{
    _data = std::move(other._data);
}

css_node &css_node::operator =(const css_node &other)
{
    delete _data;
    _data = other._data;
    return *this;
}

void css_node::add_rule(const std::string &name, const std::string &value)
{
    _data->rules[name] = value;
}

std::string css_node::to_string(print_type type) const
{
    std::string ret;

    for (auto it = _data->rules.begin(); it != _data->rules.end(); ++it) {
        if (type == print_type::formatted)
            ret.append("\n    ");

        if (ret.size() && type == print_type::compact)
            ret.append(";");

        if (type == print_type::formatted) {
            ret.append(it->first + ": " + it->second);
            ret.append(";");
        } else {
            ret.append(it->first + ":" + it->second);
        }
    }
    std::string selectors;
    for (std::string s : _data->selectors) {
        if (selectors.size())
            selectors.append(", ");
        selectors.append(s);
    }

    if (type == print_type::formatted)
        ret.append("\n");
    return selectors + "{" + ret + "}";
}

void css_node::append(core::string_renderer &r)
{
    bool f = true;
    for (std::string s : _data->selectors) {
        if (!f)
            r.append(", ");
        f = false;
        r.append(s);
    }
    r.append(" {");
    r.indent();
    for (auto it = _data->rules.begin(); it != _data->rules.end(); ++it) {
        r.new_line();
        r.append(it->first);
        r.append(":");
        r.space();
        r.append(it->second);
        r.append(";");
    }
    r.unindent();
    r.new_line();
    r.append("}");
    r.new_line();
}

void css_node::inline_append(core::string_renderer &r)
{
    for (auto it = _data->rules.begin(); it != _data->rules.end(); ++it) {
        r.append(it->first);
        r.append(":");
        r.append(it->second);
        r.append(";");
    }
}

std::string css_node_vector::to_string(print_type type) const
{
    core::string_renderer r(type);
    for (auto i = cbegin(); i != cend(); ++i)
        (*i)->append(r);
    return r.to_string();
}

void css_node::set_attr(const std::string &name, const std::string &value)
{
    _data->rules[name] = value;
}

void css_node::add_selector(const std::string &name)
{
    _data->selectors.push_back(name);
}

bool css_node::has_selector(const std::string &name)
{
    return std::any_of(_data->selectors.begin(), _data->selectors.end(), [=](std::string &s){
       return s == name;
    });
}

std::vector<std::string> css_node::selectors() const {
    return _data->selectors;
}

TOOSKA_END_NAMESPACE

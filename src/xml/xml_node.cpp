#include <iostream>

#include "xml_node.h"

#include "../core/string_helper.h"

TOOSKA_BEGIN_NAMESPACE(xml)

node::node(): tooska::core::node_t<node>(nullptr),
      tooska::core::doc_node_base(std::string()),
      _has_close_tag(true)
{

}

node::node(const std::string &name, node *parent) : tooska::core::node_t<node>(parent),
      tooska::core::doc_node_base(name),
      _has_close_tag(true)
{
}

void node::internal_find(std::vector<std::string> rules, tooska::core::nodes_vector<node> &ret)
{
    if (name() == rules.at(0)) {
        if (rules.capacity() == 1)
            ret.push_back(this);

        if (rules.capacity() > 1) {
            rules.erase(rules.begin());
            for (auto ch: _childs)
                static_cast<node*>(ch)->internal_find(rules, ret);
        }
    }
}

tooska::core::nodes_vector<node> node::find(std::string rule)
{
    auto rules = tooska::core::string_helper::split(rule, '/');
    rules.insert(rules.begin(), name());
    tooska::core::nodes_vector<node> r;
    internal_find(rules, r);
    return r;
}

void node::set_name(const std::string &name)
{
    auto parts = tooska::core::string_helper::split(name, ':');
    if (parts.size() == 2) {
        _namespace = parts[0];
        _name = parts[1];
    } else {
        _name = name;
    }
}

std::string node::to_string(print_type type)
{
    core::string_renderer r(type);
    append(r);
    return r.to_string();
}

void node::append(core::string_renderer &r)
{
    auto is_formed = _attributes.size() || _childs.size();
    r.new_line();
    append_begin_tag(r);
    if (_has_close_tag)
        r.indent();
    if (is_formed)
        r.new_line();
    append_inner(r);
    r.append(inner_text());
    if (_has_close_tag)
        r.unindent();
    if (is_formed)
        r.new_line();
    append_end_tag(r);
    r.new_line();
}

void node::append_begin_tag(core::string_renderer &r)
{

    r.append("<");
    if (_namespace != std::string()) {
        r.append(_namespace);
        r.append(":");
    }
    r.append(name());
    std::map<std::string, std::string>::iterator it;
    for(it = _attributes.begin(); it != _attributes.end(); ++it)
        r.append(" " + it->first + "=\"" + it->second + "\"");

    if (_has_close_tag)
        r.append(">");
    else
        r.append(" />");
}

void node::append_inner(core::string_renderer &r)
{
    for (auto child : _childs)
        child->append(r);
}

void node::append_end_tag(core::string_renderer &r)
{
    if (_has_close_tag) {
        r.append("</" + name() + ">");
    }
}

TOOSKA_END_NAMESPACE

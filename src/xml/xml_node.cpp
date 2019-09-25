#include <iostream>

#include "xml_node.h"

#include "../core/string_helper.h"

TOOSKA_BEGIN_NAMESPACE(xml)

node::node(const std::string &name, node *parent) : tooska::core::node_t<node>(parent),
      tooska::core::doc_node_base(name),
      has_close_tag(true)
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

TOOSKA_END_NAMESPACE

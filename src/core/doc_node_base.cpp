#include "doc_node_base.h"

#include "string_helper.h"

TOOSKA_BEGIN_NAMESPACE(core)

doc_node_base::doc_node_base(std::string name)
{
    set_name(name);
}

std::string doc_node_base::attr(const std::string &name)
{
    return _attributes[name];
}

void doc_node_base::set_attr(const std::string &name, const std::string &value)
{
    auto n = name;
    core::string_helper::tolower(n);
    _attributes[n] = value;
}

bool doc_node_base::has_attr(const std::string &name)
{
    return _attributes.find(name) != _attributes.end();
}

void doc_node_base::set_name(const std::string &name)
{
    this->_name = name;
}

std::string doc_node_base::name() const
{
    return _name;
}

std::map<std::string, std::string> doc_node_base::attributes() const
{
    return _attributes;
}

std::string doc_node_base::inner_text() const
{
    return _inner_text;
}

void doc_node_base::set_inner_text(const std::string &inner_text)
{
    _inner_text = inner_text;
}

TOOSKA_END_NAMESPACE

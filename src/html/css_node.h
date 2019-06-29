#ifndef CSSRULES_H
#define CSSRULES_H

#include "../global.h"
#include <map>
#include <string>
#include <vector>

TOOSKA_BEGIN_NAMESPACE(core)
class string_renderer;
TOOSKA_END_NAMESPACE

TOOSKA_BEGIN_NAMESPACE(html)

class css_node
{
    std::vector<std::string> _selectors;
    std::map<std::string, std::string> _rules;
public:
    css_node();
    void add_rule(const std::string &name, const std::string &value);
    void set_attr(const std::string &name, const std::string &value);
    void add_selector(const std::string &name);
    bool has_selector(const std::string &name);
    void clear();
    std::vector<std::string> selectors() const {
        return _selectors;
    }
    std::string to_string(print_type type = print_type::compact) const;
    void append(core::string_renderer &r);
    void inline_append(core::string_renderer &r);

    friend class html_tag;
};

class css_node_vector : public std::vector<css_node*>
{
public:
    std::string to_string(print_type type = print_type::compact) const;
};

TOOSKA_END_NAMESPACE

#endif // CSSRULES_H

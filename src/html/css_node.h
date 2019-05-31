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

struct css_node_data;
class css_node
{
    css_node_data *_data;

public:
    css_node();
    css_node(const css_node &other);
    css_node(css_node &&other);
    css_node &operator =(const css_node &other);

    void add_rule(const std::string &name, const std::string &value);
    void set_attr(const std::string &name, const std::string &value);
    void add_selector(const std::string &name);
    bool has_selector(const std::string &name);
    std::vector<std::string> selectors() const;

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

#include "css_document.h"
#include "../core/string_renderer.h"
#include <wctype.h>
#include <iostream>
#include <algorithm>

TOOSKA_BEGIN_NAMESPACE(html)

std::vector<css_node *> css_document::nodes() const
{
    return _nodes;
}

int css_document::token(int n)
{
    return isprint(n) && n != '{' && n != '}' && n != ':' && n != ';' && n != ',';
}

css_document::css_document()
{
//    _literals.push_back(new literal_t{"'", "'", "\\'", false, false});
    _literals.push_back(new literal_t{"/*", "*/", "", false, false});

    _check_fns.push_back(&css_document::token);
}

void css_document::parse()
{
    bool inside_block = false;
    css_node *last_node = new css_node;

    for (size_t i = 0; i < _tokens.size(); ++i) {
        auto token = _tokens.at(i);
        if (token == "{") {
            inside_block = true;
            continue;
        }
        if (token == "}") {
            inside_block = false;
            _nodes.push_back(last_node);
            last_node = new css_node;
            continue;
        }
        if (inside_block) {
            auto colon = _tokens.at(i + 1);
            auto value = _tokens.at(i + 2);
            auto semi_colon = _tokens.at(i + 3);
            last_node->set_attr(token, value);
//            i += 3;
            while (_tokens.at(i) != ";" && _tokens.at(i) != "}")
                ++i;

            continue;
        } else {
            if (token != ",")
                last_node->add_selector(token);
        }
    }
}

css_document::~css_document()
{

}

std::vector<css_node *> css_document::find_contains_selector(const std::string &selector)
{
    std::vector<css_node *> ret;
    for (css_node *node : _nodes)
        if (node->has_selector(selector))
            ret.push_back(node);
    return ret;
}

std::vector<css_node *> css_document::find_match_selector(const std::string &selector)
{
    std::vector<css_node *> ret;

    for (css_node *node : _nodes)
        if (node->selectors().size() == 1 && node->has_selector(selector))
            ret.push_back(node);
    return ret;
}

std::map<std::string, std::string> css_document::parse_block()
{
    size_t i = 0;
    std::map<std::string, std::string> ret;

    while (true) {
        if (_tokens.size() < i + 3)
            break;
        auto name = _tokens.at(i);
        auto colon = _tokens.at(i + 1);
        auto value = _tokens.at(i + 2);

        if (_tokens.size() > i + 3 && _tokens.at(i + 3) != ";") {
            _error_message = "Unecpected token: " + _tokens.at(i + 3);
            break;
        }
        ret[name] = value;
        i += 4;
    }

    return ret;
}

std::string css_document::to_string(print_type type) const
{
    core::string_renderer r(type);
    for (auto i = _nodes.cbegin(); i != _nodes.cend(); ++i)
        (*i)->append(r);
    return r.to_string();
}

void css_document::add_node(css_node *node)
{
    _nodes.push_back(node);
}

void css_document::clear()
{
    std::for_each(_nodes.begin(), _nodes.end(), [](css_node *node){
        delete node;
    });
    _nodes.clear();
}

TOOSKA_END_NAMESPACE


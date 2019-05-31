#ifndef HTML_P_H
#define HTML_P_H

#include "../global.h"
#include <vector>
#include <map>
#include <string>
#include "css_document.h"

TOOSKA_BEGIN_NAMESPACE(html)

class html_tag;
class html_node;
class css_node;

struct html_node_data
{
    html_tag *_parent;

};

struct text_node_data : public html_node_data
{
    std::string _text;
};

struct html_tag_data : public html_node_data
{
    std::map<std::string, std::string> _attributes;
    std::vector<html_node *> _childs;
    bool _has_close_tag;
    css_node *_css;
};

struct style_tag_data : public html_node_data
{
    css_document rules;
};

TOOSKA_END_NAMESPACE

#endif // HTML_P_H

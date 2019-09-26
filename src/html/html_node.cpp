#include "css_document.h"
#include "css_node.h"
#include "html_node.h"
#include "query_parser.h"
#include "../core/string_helper.h"
#include "../core/token_parser.h"
#include "../core/string_renderer.h"

#include <iostream>
#include <algorithm>

TOOSKA_BEGIN_NAMESPACE(html)

bool html_tag::hasCloseTag() const
{
    return _has_close_tag;
}

void html_tag::setHasCloseTag(bool hasCloseTag)
{
    _has_close_tag = hasCloseTag;
}

std::vector<html_node *> html_tag::childs() const
{
    return _childs;
}

std::string html_tag::to_string(print_type type)
{
    core::string_renderer r(type);
    append(r);
    return r.to_string();
}

void html_tag::append(core::string_renderer &r)
{
    r.new_line();
    append_begin_tag(r);
    if (_has_close_tag)
        r.indent();
    r.new_line();
    append_inner_html(r);
    if (_has_close_tag)
        r.unindent();
    append_end_tag(r);
    r.new_line();
}

void html_tag::append_begin_tag(core::string_renderer &r)
{
    r.append("<" + name);
    std::map<std::string, std::string>::iterator it;
    for(it = _attributes.begin(); it != _attributes.end(); ++it)
        r.append(" " + it->first + "=\"" + it->second + "\"");

    if (_css->_rules.size()) {
        r.space();
        r.append("style=\"");
        _css->inline_append(r);
        r.append("\"");
    }

    if (_classes.size()) {
        r.space();
        r.append("class=\"");
        for (size_t i = 0; i < _classes.size(); i++) {
            if (i)
                r.space();
            r.append(_classes.at(i));
        }
        r.append("\"");
    }

    if (_has_close_tag)
        r.append(">");
    else
        r.append(" />");
}

void html_tag::append_inner_html(core::string_renderer &r)
{
    for (auto child : _childs)
        child->append(r);
}

void html_tag::append_end_tag(core::string_renderer &r)
{
    if (_has_close_tag) {
        r.new_line();
        r.append("</" + name + ">");
    }
}

html_tag::html_tag() : html_node (), _css(new css_node)
{

}

html_tag::~html_tag()
{
    for (html_node *child : _childs) {
        child->set_parent(nullptr);
        delete child;
    }
    _childs.clear();
}

std::string html_tag::id()
{
    return _attributes["id"];
}

std::string html_tag::attr(const std::string &name)
{
    return _attributes[name];
}

bool html_tag::has_attr(const std::string &name)
{
    return _attributes.find(name) != _attributes.end();
}

std::string html_tag::data(const std::string &name)
{
    return attr("data-" + name);
}

void html_tag::set_attr(const std::string &name, const std::string &value)
{
    auto n = name;
    core::string_helper::tolower(n);
    if (n == "style") {
        css_document p;
        p.set_text(value);
        auto rules = p.parse_block();
        _css->_rules = rules;
        return;

    } else if (n == "class") {
        _classes = core::string_helper::split(value, ' ');
        return;
    }

    _attributes[n] = value;
}

void html_tag::remove_attr(const std::string &name)
{
    if (name == "style") {
        _css->clear();
        return;
    } else if (name == "class") {
        _classes.clear();
        return;
    }

    auto i = _attributes.find(name);
    if (i != _attributes.end())
        _attributes.erase(i, i);
}

void html_tag::add_class(const std::string &name)
{
    if (std::find(_classes.begin(), _classes.end(), name) == _classes.end())
        _classes.push_back(name);
}

void html_tag::remove_class(const std::string &name)
{
    _classes.erase(std::remove(_classes.begin(), _classes.end(), name),
                   _classes.end());
}

bool html_tag::has_class(const std::string &name) const
{
    return (std::find(_classes.begin(), _classes.end(), name) != _classes.end());
}

void html_tag::add_child(html_node *child)
{
    _childs.push_back(child);
    child->set_parent(this);
}

void html_tag::remove_child(html_node *child)
{
    _childs.erase(std::remove(_childs.begin(), _childs.end(), child), _childs.end());
}

std::string html_tag::outter_html()
{
    std::string html = "<" + name;
    std::map<std::string, std::string>::iterator it;
    for(it = _attributes.begin(); it != _attributes.end(); ++it)
        html.append(" " + it->first + "=\"" + it->second + "\"");

    if (_classes.size()) {
        html.append(" class=\"");
        std::vector<std::string>::iterator classes_it;
        for (classes_it = _classes.begin(); classes_it != _classes.end(); ++classes_it) {
            if (classes_it != _classes.begin())
                html.append(" ");
            html.append(*classes_it);
        }
        html.append("\"");
    }
    if (_has_close_tag)
        html.append(">");
    else
        html.append(" />");

    html.append(inner_html());

    if (_has_close_tag)
        html.append("</" + name + ">");

    return html;
}

std::string html_tag::inner_html() const
{
    std::string html;
    std::vector<html_node*>::const_iterator i;
    for (i = _childs.cbegin(); i != _childs.cend(); ++i)
        html.append((*i)->outter_html());

    return html;
}

std::string html_tag::inner_text() const
{
    std::string html;
    std::vector<html_node*>::const_iterator i;
    for (i = _childs.cbegin(); i != _childs.cend(); ++i) {
        std::string buffer = (*i)->inner_text();
//        trim(buffer);
        if (buffer != "") {
            if (buffer.substr(buffer.length() - 1, 1) != " ")
                buffer.append(" ");
            html.append(buffer);
        }
    }

    return html;
}

html_node::html_node() : _parent(nullptr)
{

}

html_node::~html_node()
{
    if (_parent)
        _parent->remove_child(this);
}

html_tag *html_node::parent() const
{
    return _parent;
}

void html_node::set_parent(html_tag *parent)
{
    _parent = parent;
}

html_tag *html_node::to_tag()
{
    return dynamic_cast<html_tag*>(this);
}

text_node::text_node() : html_node ()
{

}

std::string text_node::get_text() const
{
    return _text;
}

void text_node::set_text(const std::string &text)
{
    _text = text;
    core::string_helper::replace(_text, "\r", "");
    core::string_helper::replace(_text, "\n", "");
}

std::string text_node::outter_html()
{
    return _text;
}

std::string text_node::inner_text() const
{

    return  _text;
}

html_tag_vector html_tag::find(const std::string &query)
{
    query_parser qp;
    qp.set_text(query);
    qp.tag = this;
    return qp.search();
}

html_tag_vector html_tag::find(std::function<bool (html_tag *)> &check)
{
    html_tag_vector ret;
    std::function<void(html_node*)> ch = [&](html_node *node){
        auto tag = node->to_tag();
        if (!tag)
            return;

        if (check(tag))
            ret.push_back(tag);

        auto childs = tag->childs();
        for (auto i = childs.begin(); i != childs.end(); ++i) {
            ch(*i);
        }
    };
    ch(this);
    return ret;
}

void text_node::append(core::string_renderer &r)
{
    r.append(_text);
}

//css_doc style_tag::rules() const
//{
//    return _rules;
//}

//void style_tag::setRules(const css_doc &rules)
//{
//    _rules = rules;
//}

std::string style_tag::inner_html() const
{
    if (rules.nodes().size())
        return std::string();
    else
        return rules.to_string();
}

void style_tag::append(core::string_renderer &r)
{
    r.append("<style>");
    r.indent();
    r.new_line();
    auto nodes = rules.nodes();
    if (nodes.size())
        for (auto i = nodes.cbegin(); i != nodes.cend(); ++i) {
            (*i)->append(r);
            r.new_line();
        }
    r.unindent();
    r.append("</style>");
    r.new_line();
}

style_tag::style_tag() : html_tag()
{

}

void style_tag::add_child(html_node *child)
{
    text_node *tn = dynamic_cast<text_node*>(child);
    if (tn) {
        rules.set_text(tn->get_text());
    } else {
        std::cout << "Appending non-text node to style tag was not allowed";
    }
}

std::map<std::string, std::string> html_tag::attributes() const
{
    return _attributes;
}

void html_tag::remove()
{
    _parent->remove_child(this);
    std::for_each(_childs.begin(), _childs.end(), [](html_node *child){
        delete child;
    });
}

void html_tag::unwrap()
{
    _parent->remove_child(this);
    std::for_each(_childs.begin(), _childs.end(), [this](html_node *child){
//        _parent->add_child(child);
    });
}

void html_tag::unwrap_child(html_tag *child)
{
//    auto i = _childs
}

TOOSKA_END_NAMESPACE

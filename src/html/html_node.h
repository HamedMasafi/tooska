#ifndef HTMLTAG_H
#define HTMLTAG_H

#include "../global.h"
#include "css_node.h"
#include "css_document.h"
#include "html_tag_vector.h"
#include <string>
#include <vector>

TOOSKA_BEGIN_NAMESPACE(core)
class string_renderer;
TOOSKA_END_NAMESPACE

TOOSKA_BEGIN_NAMESPACE(html)
class css_node;
class html_tag;
class html_node
{
    html_tag *_parent;

public:
    html_node();
    virtual ~html_node();

    html_tag *parent() const;
    void set_parent(html_tag *parent);
    virtual std::string outter_html()
    {
        return  "";
    }
    virtual std::string inner_text() const
    {
        return  "";
    }

    html_tag *to_tag();

protected:
    virtual void append(core::string_renderer &r) = 0;

    friend class html_document;
    friend class html_tag;
};

class text_node : public html_node
{

    std::string _text;

public:
    text_node();
    std::string get_text() const;
    void set_text(const std::string &get_text);
    std::string outter_html() override;
    std::string inner_text() const override;

private:
    void append(core::string_renderer &r) override;

    friend class html_document;
};

class html_tag : public html_node
{

    std::map<std::string, std::string> _attributes;
    std::vector<html_node *> _childs;
    bool _has_close_tag;
    css_node *_css;

public:
    std::vector<std::string> _classes;
    std::string name;

    html_tag();
    virtual ~html_tag() override;

    std::string id();
    std::string attr(const std::string &name);
    bool has_attr(const std::string &name);
    std::string data(const std::string &name);
    void set_attr(const std::string &name, const std::string &value);
    void remove_attr(const std::string &name);
    void add_class(const std::string &name);
    void remove_class(const std::string &name);
    bool has_class(const std::string &name) const;

    virtual void add_child(html_node *child);
    void remove_child(html_node *child);

    std::string outter_html() override;
    virtual std::string inner_html() const;
    std::string inner_text() const override;
//    std::string name() const;
//    void setName(const std::string &name);
    bool hasCloseTag() const;
    void setHasCloseTag(bool hasCloseTag);
    std::vector<html_node *> childs() const;
    html_tag_vector find(const std::string &query);
    html_tag_vector find(std::function<bool(html_tag*)> &check);

    std::string to_string(print_type type = print_type::compact);
    void remove();
    void unwrap();
    void unwrap_child(html_tag *child);

    std::map<std::string, std::string> attributes() const;

private:
    void append(core::string_renderer &r) override;
    void append_begin_tag(core::string_renderer &r);
    void append_inner_html(core::string_renderer &r);
    void append_end_tag(core::string_renderer &r);

    friend class html_document;
};

class style_tag : public html_tag
{

public:
    css_document rules;
    style_tag();

    void add_child(html_node *child) override;
//    css_doc rules() const;
//    void setRules(const css_doc &rules);

    std::string inner_html() const override;

private:
    void append(core::string_renderer &r) override;
};

TOOSKA_END_NAMESPACE

#endif // HTMLTAG_H

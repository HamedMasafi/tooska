#ifndef HTML_WRITER_H
#define HTML_WRITER_H

#include <string>
#include <stack>

#include "../global.h"
#include "html_node.h"

TOOSKA_BEGIN_NAMESPACE(html)

class html_writer
{
    std::stack<html_tag*> _tags;
    html_tag *_html_tag;

public:
    html_writer();

    void begin_tag(const std::string &tag_name);
    void begin_tag(const core::html_tag_type &tag_type);
    void write_text(const std::string &text_node);
    void set_attr(const std::string &name, const std::string &value);
    void add_class(const std::string &name);

    void close_tag();

    std::string to_string(const print_type &fmt = print_type::compact) const;
};

TOOSKA_END_NAMESPACE

#endif // HTML_WRITER_H

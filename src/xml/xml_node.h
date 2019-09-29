#ifndef XML_NODE_H
#define XML_NODE_H

#include "../global.h"
#include "../core/tree.h"
#include "../core/doc_node_base.h"
#include "../core/nodes_vector.h"
#include "../core/string_renderer.h"
#include <string>

TOOSKA_BEGIN_NAMESPACE(xml)

class node : public tooska::core::node_t<node>, public tooska::core::doc_node_base
{
    std::string _namespace;

public:
    node();
    node(const std::string &name, node *parent = nullptr);
    bool _has_close_tag;

    tooska::core::nodes_vector<node> find(std::string rule);
    void set_name(const std::string &name) override;
    std::string to_string(print_type type = print_type::compact);

private:
    void append(core::string_renderer &r);
    void append_begin_tag(core::string_renderer &r);
    void append_inner(core::string_renderer &r);
    void append_end_tag(core::string_renderer &r);

    void internal_find(std::vector<std::string> rules, tooska::core::nodes_vector<node> &ret);

    friend class xml_document;
};

TOOSKA_END_NAMESPACE

#endif // XML_NODE_H

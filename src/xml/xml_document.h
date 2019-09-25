#ifndef XML_DOCUMENT_H
#define XML_DOCUMENT_H

#include "../core/token_parser.h"
#include "../core/tree.h"

TOOSKA_BEGIN_NAMESPACE(xml)

class node;
class xml_document : public core::token_parser
{
//    tooska::core::tree<node> _root_node;
    node *_root_node;
    node *_doctype;

public:
    xml_document();
    ~xml_document();
    node *root_node() const;

    std::vector<node*> find(const std::string &rule);
    node *doctype() const;

private:
    static int token(int n);

protected:
    void parse();
    node *parse_tag_begin(const std::string &close_char = "/");
};

TOOSKA_END_NAMESPACE

#endif // XML_DOCUMENT_H

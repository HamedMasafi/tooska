#ifndef JSON_DOCUMENT_H
#define JSON_DOCUMENT_H

#include "../core/token_parser.h"

TOOSKA_BEGIN_NAMESPACE(json)

class json_object;
class json_array;
class value;
class json_document : public core::token_parser
{
    static int token(int n);
    value *_root;

public:
    json_document();
    json_document(json_array *root);
    json_document(json_object *root);

    std::string to_string(print_type type = print_type::compact) const;
    value *find(const std::string &path);

    bool is_array() const;
    bool is_object() const;
    json_object *to_object();
    json_array *to_array();

protected:
    void parse();

private:
    void init();
    value *parse_value();
    value *parse_value(const std::string &token);
    json_object *parse_object();
    json_array *parse_array();
};

TOOSKA_END_NAMESPACE

#endif // JSON_DOCUMENT_H

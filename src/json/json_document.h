#ifndef JSON_DOCUMENT_H
#define JSON_DOCUMENT_H

#include "../core/token_parser.h"

TOOSKA_BEGIN_NAMESPACE(json)

class object;
class array;
class value;
class document : public core::token_parser
{
    static int token(int n);
    value *_root;

public:
    document();
    document(array *root);
    document(object *root);

    std::string to_string(print_type type = print_type::compact) const;
    value *find(const std::string &path);

    bool is_array() const;
    bool is_object() const;
    object *to_object();
    array *to_array();

protected:
    void parse();

private:
    void init();
    value *parse_value();
    value *parse_value(const std::string &token);
    object *parse_object();
    array *parse_array();
};

TOOSKA_END_NAMESPACE

#endif // JSON_DOCUMENT_H

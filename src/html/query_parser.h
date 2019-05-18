#ifndef QUERY_PARSER_H
#define QUERY_PARSER_H

#include "html_tag_vector.h"
#include "../core/token_parser.h"

#include <string>
#include <vector>

TOOSKA_BEGIN_NAMESPACE(html)

class html_tag;
class query_parser : public core::token_parser
{
    struct query_rule_t{
        std::string id;
        std::string tag_name;
        std::vector<std::string> classes;
        std::string attr_name;
        std::string attr_value;
        bool is_child;

        bool is_valid() const;
        bool check(html_tag *tag) const;

        query_rule_t();
    };
    std::vector<std::vector<query_rule_t*>> rules;
public:
    query_parser();
    html_tag_vector results;

    void parse();
    void parse_attrs(size_t &i, query_rule_t *rule);
    void parse_child_selector(size_t &i, query_rule_t *rule);

    html_tag *tag;
    html_tag_vector search();
    void search(html_tag_vector &result, html_tag *tag,
                size_t rule_id,
                std::vector<query_rule_t *> rules,
                bool rescue = true);
private:
    static int token(int n);
};

TOOSKA_END_NAMESPACE

#endif // QUERY_PARSER_H

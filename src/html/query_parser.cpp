#include "html_node.h"
#include "query_parser.h"

#include <iostream>
#include <wctype.h>
#include <algorithm>
#include <string>

TOOSKA_BEGIN_NAMESPACE(html)

int query_parser::token(int n)
{
    return isalpha(n) || isdigit(n) || n == '-';
}

query_parser::query_parser() : core::token_parser()
{
    _literals.push_back(new literal_t{"\"", "\"", "\\\"", false, true});

    _check_fns.push_back(&query_parser::token);
}

void query_parser::parse()
{
    query_rule_t *last_rule = new query_rule_t;

    std::vector<query_rule_t*> rl;
    for (size_t i = 0; i < _tokens.size(); ++i) {
        auto t = _tokens.at(i);

        if (t == ",") {
            rl.push_back(last_rule);
            rules.push_back(rl);
            rl.clear();
            last_rule = new query_rule_t;
            continue;
        }

        if (t == ":") {
            parse_child_selector(i, last_rule);
        }

        if (t == ".") {
            ++i;
            last_rule->classes.push_back(_tokens.at(i));
            continue;
        }
        if (t == "#") {
            ++i;
            last_rule->id = _tokens.at(i);
            continue;
        }
        if (t == ">") {
            rl.push_back(last_rule);
            last_rule = new query_rule_t;
            last_rule->is_child = true;
            ++i;
            last_rule->tag_name = _tokens.at(i);
            continue;
        }

        if (t == "[") {
            parse_attrs(i, last_rule);
            continue;
        }

        if (last_rule->is_valid())
            rl.push_back(last_rule);
        last_rule = new query_rule_t;
        last_rule->is_child = false;
        last_rule->tag_name = t;

    }
    rl.push_back(last_rule);

    rules.push_back(rl);

//    int i = 0;
//    std::for_each(rules.begin(), rules.end(), [&i](std::vector<query_rule_t*> rl){
//        std::cout << "RULE: " << (++i) << std::endl;
//        std::for_each(rl.begin(), rl.end(), [](query_rule_t *r){
//            std::cout << std::endl
//                      << "   id:" << r->id << std::endl
//                      << "   tag name: " << r->tag_name << std::endl
//                      << "   is child: " << (r->is_child ? "true" : "false") << std::endl
//                      << "   attr name: " << r->attr_name << std::endl
//                      << "   attr value: " << r->attr_value << std::endl
//                      << "   classes:" << std::endl;
//            std::for_each(r->classes.begin(), r->classes.end(), [](std::string cls){
//               std::cout << "      - " << cls << std::endl;
//            });
//        });
//        });
}

void query_parser::parse_attrs(size_t &i, query_rule_t *rule)
{
    std::string name, value, op;
    /*
     name       0
     <op>
     =          1
     value      2
    */
    int step = 0;
    for (; i < _tokens.size(); ++i) {
        auto t = _tokens.at(i);

        if (t == "]")
            break;

        if (t == "[")
            continue;

        switch (step) {
        case 0:
            if (name.empty())
                name = t;
            else
                op = t;
            step++;
            continue;

        case 1:
            if (t != "=") {
                return; // there is a error
            }
            step++;
            continue;

        case 2:
            value = t;
        }
    }

    rule->attr_name = name;
    rule->attr_value = value;
}

void query_parser::parse_child_selector(size_t &i, query_parser::query_rule_t *rule)
{
    ++i;
    /*
     :
     :nth-last-child
     (
     n
     )
     */
    for (; i < _tokens.size(); ++i) {
        auto t = _tokens.at(i);

        if (t == ")")
            break;

    }
}

html_tag_vector query_parser::search()
{
    html_tag_vector tags;
    for (auto l : rules) {
        size_t i = 0;
        search(tags, tag, i, l);
    }
    return tags;
}

void query_parser::search(html_tag_vector &result, html_tag *tag, size_t rule_id, std::vector<query_rule_t *> rules, bool rescue)
{
    if (rule_id >= rules.size()) {
        return;
    }

    auto rule = rules.at(rule_id);
    if (rule->check(tag))
        rule_id++;
//        return;

    if (rule_id == rules.size()) {
        result.push_back(tag);
        return;
    }


    if (rescue)
        for (auto child : tag->childs()) {
            auto t = dynamic_cast<html_tag*>(child);
            if (t)
                search(result, t, rule_id, rules, !rule->is_child);
        }
}

bool query_parser::query_rule_t::is_valid() const {
    return id.size() || tag_name.size() || classes.size();
}

bool query_parser::query_rule_t::check(html_tag *tag) const
{
    if (!tag)
        return false;

    if (id.size() && tag->id() != id)
        return false;

    if (tag_name.size() && tag->name != tag_name)
        return false;

    if (classes.size())
        for (auto cls : classes) {
            if (std::none_of(tag->_classes.begin(), tag->_classes.end(), [=](std::string c){
                return c == cls;
            })){
                return false;
            }
        }

    if (!attr_name.empty()) {
        bool ok = attr_value.empty()
                ? tag->has_attr(attr_name)
                : tag->attr(attr_name) != attr_value;

        if (!ok)
            return false;
    }

    return true;
}

query_parser::query_rule_t::query_rule_t() : is_child(false)
{

}

TOOSKA_END_NAMESPACE

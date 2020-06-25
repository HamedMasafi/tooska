#include "html_node.h"
#include "query_parser.h"
#include "core/string_helper.h"

#include <iostream>
#include <wctype.h>
#include <algorithm>
#include <string>

TOOSKA_BEGIN_NAMESPACE(html)

int query_parser::token(int n)
{
    return isalpha(n) || isdigit(n) || n == '-' || n == '_';
}

int query_parser::space(int n)
{
    return isspace(n);
}

query_parser::query_parser() : core::token_parser()
{
    _literals.push_back(new literal_t{"\"", "\"", "\\\"", false, true});

    _check_fns.push_back(&query_parser::token);
    _check_fns.push_back(&query_parser::space);
}

void query_parser::parse()
{
    rules_group_list().swap(_rules);

    query_rule_t *last_rule = new query_rule_t;
    rules_group rules_list;

    for (size_t i = 0; i < _tokens.size(); ++i) {
        auto t = _tokens.at(i);

        tooska::core::string_helper::trim(t);
        if (!t.size()) {
            if (last_rule->is_valid()) {
                rules_list.push_back(last_rule);
                last_rule = new query_rule_t;
            }
            continue;
        }

        if (t == ",") {
            rules_list.push_back(last_rule);
            _rules.push_back(rules_list);
            rules_list.clear();
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
            if (last_rule->is_valid())
                rules_list.push_back(last_rule);
            last_rule = new query_rule_t;
            last_rule->is_child = true;
            continue;
        }

        if (t == "[") {
            parse_attrs(i, last_rule);
            continue;
        }

        if (last_rule->is_valid())
            rules_list.push_back(last_rule);
        last_rule = new query_rule_t;
        last_rule->is_child = false;
        last_rule->tag_name = t;

    }
//    rl.push_back(last_rule);

    rules_list.push_back(last_rule);
    _rules.push_back(rules_list);
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
    for (auto l : _rules) {
        size_t i = 0;
        search(tags, tag, i, l);
    }
    return tags;
}

void query_parser::search(html_tag_vector &result, html_tag *tag, size_t rule_id, query_parser::rules_group rules, bool rescue)
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

query_parser::rules_group_list query_parser::rules() const
{
    return _rules;
}

TOOSKA_END_NAMESPACE

#include "xml_document.h"

#include "xml_node.h"
#include "../core/string_helper.h"

#include <stack>
#include <vector>
#include <wctype.h>
#include <algorithm>
#include <iostream>

using namespace std;

TOOSKA_BEGIN_NAMESPACE(xml)

int xml_document::token(int n)
{
    return isalnum(n) || isdigit(n) || n == '-' || n == ':';
}

xml_document::xml_document() : tooska::core::token_parser()
      , _doctype(nullptr), _root_node(nullptr)
{
    _literals.push_back(new literal_t{">", "<", "", true, true});
    _literals.push_back(new literal_t{"\"", "\"", "\\\"", true, true, false});
    _literals.push_back(new literal_t{"'", "'", "\\'", false, true, true});
    _literals.push_back(new literal_t{"!--", "-->", "", false, false});

    _check_fns.push_back(&xml_document::token);
}

void xml_document::parse()
{
//    size_t i = 0;

    stack<node *> stack;
    vector<node *> tags;
    _root_node = nullptr;

    if (_tokens.size() > 3 && next_token() == "<" && next_token(1) == "?") {
        take_token();
        take_token();
        _doctype = parse_tag_begin("?");
    }

    std::string dstr;

    string token;
    do {
        token = take_token();
        dstr += token;
        if (none_of(token.begin(), token.end(), &iswprint))
            //                   [](char n){return isprint(n);}))
            continue;

        if (token == "<") {
            auto nt = next_token();
            if (nt == "/") {
                if (!stack.size()) {
                    std::cerr << "Invalid document: " << nt
                              << std::endl;
                    return;
                } else {
//                    auto tag_expected = stack.top()->name();
//                    auto real_tag     = next_token(1);
                    stack.pop();
                    continue;
                }
            } else {
                auto tag = parse_tag_begin();
                if (tag) {
                    if (!_root_node)
                        _root_node = tag;

                    if (stack.size())
                        stack.top()->add_child(tag);

                    tags.push_back(tag);
                    if (tag->_has_close_tag)
                        stack.push(tag);
//                    else
//                        continue;
                } else {
                    std::cerr << _error_message << endl;
                }
            }
        }


        if (next_token(-1) == ">") {
            if (next_token() != "<") {
                std::string buffer;
                while (next_token() != "<")
                    buffer += take_token();

                auto text = core::string_helper::trim_copy(buffer);
                if (is_valid_token(text))
                    stack.top()->set_inner_text(text);
            }
        }
    } while (token != std::string());
}

node *xml_document::parse_tag_begin(const std::string &close_char)
{
    node *tag;
    string token;

    token = take_token();
    tag = new node(token);
    tag->set_name(token);
    tag->_has_close_tag = true;

    string name, value;
    int step = 0;
    /*
    name       0
    =          1
    "          2
    value      3
    "          4
    */
    if (token != ">") {
        do {
            token = take_token();

            if (token == std::string()) {
                _error_message = "Unexpected end of document, "
                                 + tag->name() + "  the nest token is: "
                                 + next_token() + next_token(1) + next_token(2)
                                 + next_token(3) + next_token(4) + next_token(5);
                delete tag;
                return nullptr;
            }

            if (token == close_char && next_token() == ">") {
                take_token();
                tag->_has_close_tag = false;
                return tag;
            }

            if (token == ">")
                break;

            switch (step) {
            case 2:
                if (token == "\"") {
                    step++;
                    continue;
                }
            case 4:
                step = 0;
                break;

            case 0:
                name = token;
                step++;
                break;

            case 1:
                if (token == "=")
                    step++;
                else {
                    _error_message = "Unexpected token: " + token
                                     + " in parsing " + tag->name();
                    print_invalid_token_message(token, "=");
                    delete tag;
                    return nullptr;
                }
                break;

            case 3:
                if (token == "\"") {
                    token = "";
                    step = 0;
                } else {
                    step++;
                }
                value = token;
                tag->set_attr(name, value);
                break;
            }

        } while (token != ">");
//        i--;
    }

    return tag;
}

node *xml_document::root_node() const
{
    return _root_node;
}

tooska::core::nodes_vector<node> xml_document::find(const string &rule)
{
    if (!_root_node)
        return tooska::core::nodes_vector<node>();

    auto rules = tooska::core::string_helper::split(rule, '/');
    tooska::core::nodes_vector<node> r;
    _root_node->internal_find(rules, r);
    return r;
}

node *xml_document::doctype() const
{
    return _doctype;
}

xml_document::~xml_document()
{
    delete _root_node;
    delete _doctype;
}

string xml_document::to_string(print_type type)
{
    core::string_renderer r(type);

    if (_doctype) {
        r.append("<?");
        auto attrs = _doctype->attributes();
        for(auto it = attrs.begin(); it != attrs.end(); ++it)
            r.append(" " + it->first + "=\"" + it->second + "\"");
        r.append("?>");
        r.new_line();
    }
    _root_node->append(r);
    return r.to_string();
}

TOOSKA_END_NAMESPACE

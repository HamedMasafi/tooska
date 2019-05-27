#include "html_document.h"
#include "html_node.h"
#include "query_parser.h"
#include "../core/string_helper.h"
#include "../core/string_renderer.h"

#include <stack>
#include <vector>
#include <wctype.h>
#include <algorithm>
#include <iostream>

using namespace std;

TOOSKA_BEGIN_NAMESPACE(html)

int html_document::token(int n)
{
    return
//            isprint(n) && n != '<';
            isalnum(n) || isdigit(n) || n == '-';
}

html_document::html_document() : token_parser(), _root_tag(nullptr)
{
    _literals.push_back(new literal_t{">",  "<",  "",     true,  true});
    _literals.push_back(new literal_t{"\"", "\"", "\\\"", false, true, true});
    _literals.push_back(new literal_t{"'",  "'",  "\\'",  false, true, true});
    _literals.push_back(new literal_t{"!--",  "-->",  "",     false,  false});

    _check_fns.push_back(&html_document::token);
//    _check_fns.push_back(&isdigit);
}

html_document::~html_document()
{
    delete _root_tag;
}

html_tag *html_document::root_tag() const {
    return _root_tag;
}

void html_document::parse()
{
//    size_t i = 0;

    stack<html_tag*> stack;
    vector<html_tag*> tags;
    _root_tag = nullptr;

    if (next_token(0) == "<" && next_token(1) == "!") {
        take_token();
        take_token();
        string token;
        do {
            token = take_token();
            if (token == ">")
                break;
            if (doctype.size())
                doctype.append(" ");
            doctype.append(token);
        } while (token != ">");
    }

    while (true) {
        string token = take_token();
        if (token == "\0")
            break;

        if (none_of(token.begin(), token.end(), &iswprint))
//                   [](char n){return isprint(n);}))
            continue;

        if (token == "<") {
            if (next_token() == "/") {
                if (!stack.size()) {
                    std::cerr << "Invalid document: " << next_token(1) << std::endl;
                    delete _root_tag;
                    return;
                } else {
                    take_token();

                    auto tag_expected = take_token();
                    auto real_tag = stack.top()->name;
//                    cout << " <=> " << tag_expected << "  ,  " << real_tag << std::endl;
                    stack.pop();
                    if (take_token() != ">")
                        std::cerr <<"********"<<std::endl;
                }
            } else {
                html_tag *tag = parse_tag_begin(_tokens);
                if (tag) {
                    if (!_root_tag)
                        _root_tag = tag;

                    if (stack.size()) {
                        tag->set_parent(stack.top());
                        stack.top()->add_child(tag);
                    }

                    tags.push_back(tag);
                    if (tag->hasCloseTag())
                        stack.push(tag);
                    else
//                        std::cout << tag->name << " has not close tag" << endl;
                    continue;
                } else {
                    std::cerr << _error_message << endl;
                }
            }
        }

        token = next_token(1);
        if (token == "<"){
//            if (next_token(1) != "<") {
                auto text = core::string_helper::trim_copy(next_token(0));
                if (any_of(text.begin(), text.end(), &iswprint)) {
                    if (!stack.size()) {
                        std::cout << "Invalid document:" << next_token(-2) << std::endl << text;
                        return;
                    }

                    text_node *textNode = new text_node;
                    textNode->set_text(text);
                    stack.top()->add_child(textNode);
                }
//            }
        }
    }
}

html_node *html_document::get_by_id(const string &id)
{
    auto tags = query("#" + id);
    if (tags.size())
        return tags.at(0);
    else
        return nullptr;
}

html_tag_vector html_document::get_by_tag_name(const string &tag_name)
{
    return query(tag_name);
}

html_tag_vector html_document::get_by_class_name(const string &class_name)
{
    return query("." + class_name);
}

html_tag_vector html_document::query(const string &q)
{
    if (!_root_tag)
        return html_tag_vector();

    query_parser qp;
    qp.set_text(q);
    qp.tag = _root_tag;
    return qp.search();
}

html_tag_vector html_document::find(std::function<bool (html_tag *)> &check)
{
    if (!_root_tag)
        return html_tag_vector();
    return _root_tag->find(check);
}

string html_document::to_string(print_type type) const
{
    core::string_renderer r(type);

    if (doctype.size()) {
        r.append("<!" + doctype + ">");
        r.new_line();
    }
    _root_tag->append(r);
    return r.to_string();
}

html_tag *html_document::parse_tag_begin(std::vector<string> &tokensList)
{
    html_tag *tag;
    string token = take_token();
    if (token == "<")
        return nullptr;
//std::cout << "tag name is " << token << std::endl;
//if (token == "/")
//    std::cout << "last is " << next_token(-2) << std::endl;

    if (token == "style")
        tag = new style_tag;
    else
        tag = new html_tag;

    tag->name = token;
    string name, value;
    int step = 0;
    /*

     name       0
     =          1
     "          -
     value      2
     "          -

     */
    if (token != ">") {
        do {
//            if (!token.size()) {
//                _error_message = "Unexpected end of document 2";
//                delete tag;
//                return nullptr;
//            }
            token = take_token();

            if (token == ">")
                break;

            if (token == "\"")
                continue;

            switch (step) {
            case 0:
                name = token;
                step++;
                break;

            case 1:
                if (token == "=")
                    step++;
                else {
//                    std::cout << "name = " << name << endl;
//                    std::cout << "error:" <<token << " =>" << tag->name<< endl;
                    _error_message = "Unexpected token: " + token + " in parsing " + tag->name;
                    print_invalid_token_message(token, "=");
                    std::cerr << "error; token is " << token << " in " << step << " step for" << tag->name << std::endl;
                    delete tag;
                    return nullptr;
                }
                break;

            case 2:
                step = 0;
                value = token;
                tag->set_attr(name, value);
                break;
            }
        } while (token != ">");
    }

    tag->setHasCloseTag(next_token(-2) != "/");

    return tag;
}

TOOSKA_END_NAMESPACE


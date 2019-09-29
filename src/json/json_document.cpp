
#include <algorithm>
#include <iostream>
#include <sstream>

#include "../core/string_helper.h"
#include "json_document.h"
#include "json_object.h"
#include "json_value.h"
#include "json_array.h"
#include "../core/string_renderer.h"

TOOSKA_BEGIN_NAMESPACE(json)

int document::token(int n)
{
    return isprint(n)
            && n != '{' && n != '}'
            && n != '[' && n != ']'
            && n != ':' && n != ';' && n != ',' && n != ' ';
}

document::document() : token_parser(), _root(nullptr)
{
    this->init();
}

document::document(array *root)
 : token_parser(), _root(root)
{
    init();
}

document::document(object *root)
 : token_parser(), _root(root)
{
    init();
}

std::string document::to_string(print_type type) const
{
    if (!_root)
        return "{}";

    core::string_renderer r(type);
    _root->render(r);
    return r.to_string();
}

value *document::find(const std::string &path)
{
    if (!_root)
        return nullptr;

    bool ok = std::all_of(path.begin(), path.end(), [](int n){
        return isalpha(n) || isdigit(n) || n == '.' || n == '_';
    });
    if (!ok) {
        std::cerr << "Invalid path: " << path << std::endl;
        return nullptr;
    }

    std::vector<std::string> strings;
    std::istringstream f(path);
    std::string s;

    auto get = [](const std::string &q, value *v) -> value* {
        auto arr = dynamic_cast<array*>(v);

        if (arr) {
            if (!core::string_helper::is_integer(q)) {
                std::cerr << "Invalid index: " << q << std::endl;
                return nullptr;
            }
            return arr->at(static_cast<size_t>(std::stoi(q)));
        }

        auto obj = dynamic_cast<object*>(v);

        if (obj)
            return obj->get(q);

        return nullptr;
    };
    value *v = _root;
    while (getline(f, s, '.')) {
        v = get(s, v);
        if (!v)
            return nullptr;
//        strings.push_back(s);
    }
    return v;
}

bool document::is_array() const
{
    if (!_root)
        return false;
    return _root->type() == value::type_t::array_t;
}

bool document::is_object() const
{
    if (!_root)
        return false;
    return _root->type() == value::type_t::object_t;
}

array *document::to_array()
{
    if (!_root)
        return nullptr;
    return _root->to_array();
}

object *document::to_object()
{
    if (!_root)
        return nullptr;
    return _root->to_object();
}

object *document::parse_object()
{
    object *obj = new object;
    value *value = nullptr;
    /*
     name       0
     :          1
     value      2
     ,          3
     */
    int step = 0;
    std::string name;
    bool exec_loop = true;
    while(exec_loop) {

        auto token = take_token();

        if (token.empty())
            break;

//        if (token == "}")
//            break;

        switch (step) {
        case 0: {
            std::string content;
            if (token == "\"" || token == "'") {
                auto begin_quote = token;
                name = take_token();
                auto close_quote = take_token();

                if (begin_quote != close_quote) {
                    print_invalid_token_message(close_quote, begin_quote);
                }
            } else {
                name = token;
            }
            step++;
            continue;
        }
        case 1:
            if (token != ":") {
                print_invalid_token_message(token, ":");
                delete obj;
                return nullptr;
            }

            step++;
            continue;

        case 2: {
            value = parse_value(token);
            step++;
            continue;
        }

        case 3:
            step = 0;
            obj->insert(name, value);

            if (token == "}")
                exec_loop = false;
            continue;
        }

    }
    return obj;
}

array *document::parse_array()
{
    int step = 0;
    auto arr = new array;
    while (true) {
        auto token = take_token();
        if (token.empty())
            break;

        if (token == "]")
            break;

        if (step == 1) {
            //token must be ,
            if (token != ",")
                print_invalid_token_message(token, ",");
            step = 0;
            continue;
        }
        auto tmp = parse_value(token);
        arr->add(tmp);
        step++;
    }
    return arr;
}

void document::parse()
{
    _root = parse_value();
}

void document::init()
{
    _literals.push_back(new literal_t{"/*", "*/", "", false, false});
    _literals.push_back(new literal_t{"'", "'", "", true, true});
    _literals.push_back(new literal_t{"\"", "\"", "\\\"", true, true});

    _check_fns.push_back(&document::token);
}

value *document::parse_value(const std::string &token)
{
    if (token == "{")
        return parse_object();

    if (token == "[")
        return parse_array();


    if (token == "\"" || token == "'") {
        auto begin_quote = token;
        auto content = take_token();
        auto close_quote = take_token();

        if (begin_quote != close_quote) {
            print_invalid_token_message(close_quote, begin_quote);
        }

        return new value(content);
    } else {
        value *v = nullptr;
        if (token == "null")
            v = new value();
        else if (token == "true" || token == "false")
            v = new value(token == "true");

        size_t idx = 0;
        if (!v) {
            try {
                int n = std::stoi(token, &idx);
                if (idx == token.length())
                    v = new value(n);
            } catch (std::exception ex) { }
        }

        if (!v) {
            try {
                float f = std::stof(token, &idx);
                if (idx == token.length())
                    v = new value(f);
            } catch (std::exception ex) { }
        }

        if (v) {
//            v->_s = token;
            return v;
        }

        print_invalid_token_message(token);
        return nullptr;
    }
}

value *document::parse_value()
{
    auto token = take_token();
    return parse_value(token);
}

TOOSKA_END_NAMESPACE

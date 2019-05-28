
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

int json_document::token(int n)
{
    return isprint(n)
            && n != '{' && n != '}'
            && n != '[' && n != ']'
            && n != ':' && n != ';' && n != ',' && n != ' ';
}

json_document::json_document() : token_parser(), _root()
{
    this->init();
}

json_document::json_document(json_array *root)
 : token_parser(), _root(root)
{
    init();
}

json_document::json_document(json_object *root)
 : token_parser(), _root(root)
{
    init();
}

std::string json_document::to_string(print_type type) const
{
    if (!_root.is_valid())
        return "{}";

    core::string_renderer r(type);
    _root.render(r);
    return r.to_string();
}

json_value json_document::find(const std::string &path)
{
    if (!_root.is_valid())
        return json_value();

    bool ok = std::all_of(path.begin(), path.end(), [](int n){
        return isalpha(n) || isdigit(n) || n == '.' || n == '_';
    });
    if (!ok) {
        std::cerr << "Invalid path: " << path << std::endl;
        return json_value();
    }

    std::vector<std::string> strings;
    std::istringstream f(path);
    std::string s;

    auto get = [](const std::string &q, json_value v) -> json_value {
        if (v.type() == json_value::type_t::array_t) {
            auto arr = v.to_array();

            if (!core::string_helper::is_integer(q)) {
                std::cerr << "Invalid index: " << q << std::endl;
                return json_value();
            }

            return arr.at(static_cast<size_t>(std::stoi(q)));
        }

        if (v.type() == json_value::type_t::object_t) {
            auto obj = v.to_object();

            return obj.get(q);
        }

        return json_value();
    };
    json_value v = _root;
    while (getline(f, s, '.')) {
        v = get(s, v);
        if (!v.is_valid())
            return json_value();
//        strings.push_back(s);
    }
    return v;
}

bool json_document::is_array() const
{
    if (!_root.is_valid())
        return false;
    return _root.type() == json_value::type_t::array_t;
}

bool json_document::is_object() const
{
    if (!_root.is_valid())
        return false;
    return _root.type() == json_value::type_t::object_t;
}

json_array json_document::to_array()
{
    return _root.to_array();
}

json_object json_document::to_object()
{
    return _root.to_object();
}

json_object json_document::parse_object()
{
    json_object obj;
    json_value value;
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
                return json_object();
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
            obj.insert(name, value);

            if (token == "}")
                exec_loop = false;
            continue;
        }

    }
    return obj;
}

json_array json_document::parse_array()
{
    int step = 0;
    json_array arr;
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
        arr.add(tmp);
        step++;
    }
    return arr;
}

void json_document::parse()
{
    _root = parse_value();
}

void json_document::init()
{
    _literals.push_back(new literal_t{"/*", "*/", "", false, false});
    _literals.push_back(new literal_t{"'", "'", "", true, true});
    _literals.push_back(new literal_t{"\"", "\"", "\\\"", true, true});

    _check_fns.push_back(&json_document::token);
}

json_value json_document::parse_value(const std::string &token)
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

        return json_value(content);
    } else {
        //TODO: set_int, set_bool...
        json_value v;
        if (token == "null")
            v = json_value();
        else if (token == "true" || token == "false")
            v = json_value(token == "true");

        size_t idx = 0;
        if (!v.is_valid()) {
            try {
                int n = std::stoi(token, &idx);
                if (idx == token.length())
                    v = json_value(n);
            } catch (std::exception ex) { }
        }

        if (!v.is_valid()) {
            try {
                float f = std::stof(token, &idx);
                if (idx == token.length())
                    v = json_value(f);
            } catch (std::exception ex) { }
        }

        if (v.is_valid()) {
            v._s = token;
            return v;
        }

        print_invalid_token_message(token);
        return json_value();
    }
}

json_value json_document::parse_value()
{
    auto token = take_token();
    return parse_value(token);
}

TOOSKA_END_NAMESPACE

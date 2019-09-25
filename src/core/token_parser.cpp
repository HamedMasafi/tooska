#include "token_parser.h"
#include "string_helper.h"

#include <wctype.h>
#include <cctype>
#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

TOOSKA_BEGIN_NAMESPACE(core)

token_parser::token_parser()
{
}

token_parser::~token_parser()
{

}

std::string token_parser::text() const
{
    return _text;
}

void token_parser::set_text(const std::string &text)
{
    _text = text;
    parse_tokens();
    parse();
}

std::vector<std::string> token_parser::tokens() const
{
    return _tokens;
}

void token_parser::print_invalid_token_message(const string &token, const string &expected)
{
    std::cout << "Invalid token '" << token << "'";
    if (!expected.empty())
        std::cout << ". Expected '" << expected << "'";
    std::cout << "." << std::endl;
}

std::vector<std::string> token_parser::parse_tokens()
{
    _tokens.clear();
    for (std::size_t i = 0; i < _text.length(); ++i) {
        std::string last_token;
        auto ch = static_cast<char>(_text.at(i));

        if (iscntrl(ch) || isspace(ch) || isblank(ch) || ch == '\n' || ch == '\r')
            continue;

        bool outer_continue = false;
        for (literal_t *literal : _literals) {
            string st = _text.substr(i, literal->begin.length());
            if (st == literal->begin) {
                last_token = read_until(_text, i, literal);

                if (literal->insert_content) {
                    if (literal->insert_begin_end)
                        _tokens.push_back(literal->begin);

                    if (is_valid_token(last_token))
                        _tokens.push_back(last_token);
                    else if (literal->insert_if_empty)
                        _tokens.push_back("");

                    if (literal->insert_begin_end)
                        _tokens.push_back(literal->end);
                }

                outer_continue = true;
                break;
            }
        }
        if (outer_continue)
            continue;

        for (auto &fn : _check_fns)
            if (fn(ch)) {
                last_token = read_until(_text, i, fn);
                if (last_token.length()) {
                    _tokens.push_back(last_token);
                    --i;
                    outer_continue = true;
                    break;
                }
            }
        if (outer_continue)
            continue;

        if (ispunct(ch)) {
            _tokens.push_back(_text.substr(i, 1));
        }
    }

    if (_tokens.at(_tokens.size() - 1) == "<")
        _tokens.pop_back();
//    std::cout << "====TOKENS====" << std::endl;
//    std::for_each(_tokens.begin(), _tokens.end(), [&](std::string token){
//       std::cout << token << std::endl;
//    });
//    std::cout << "==============" << _tokens.size() << std::endl;
    _token_it = _tokens.begin();
    return _tokens;
}

string token_parser::read_until(const string &text, size_t &i, std::function<int (int)> fn) const
{
    size_t start = i;
    while (text.length() > i  && fn(text.at(i))) {
        i++;
    }
    return text.substr(start, i - start);
}

string token_parser::read_until(const string &text, size_t &i, const literal_t *lt) const
{
    auto start = i;
    while (i < text.length() - lt->end.length()) {
        if (text.length() < i + lt->end.length())
            return string();

        auto s = text.substr(++i, lt->end.length());
        if (s == lt->end) {
            if (lt->ignore.empty())
                break;
            auto s2 = text.substr(i - lt->ignore.length() + 1, lt->ignore.length());
            if (s2 != lt->ignore)
                break;
        }
    }
    if (i == start)
        return string();
    i += lt->end.length() - 1;
    start += lt->begin.length();

    return text.substr(start, i - start - lt->end.length() + 1);
}

bool token_parser::is_valid_token(const string &token) const
{
    if (!token.length())
        return false;

    bool r = any_of(token.begin(), token.end(), [](char ch){
        return !iscntrl(ch);
    });
//    if (!r)
//        cout << token << " is not valid\n";
    return r;
}

string token_parser::take_token()
{
    if (_token_it == _tokens.end()) {
//        std::cout << "No token avaible" << std::endl;
        return std::string();
    }

    auto ret = *_token_it;

    ++_token_it;
    return ret;
}

string token_parser::next_token(int space)
{
    if (_token_it == _tokens.end() || (_token_it + space) == _tokens.end())
        return std::string();
    return *(_token_it + space);
}

string token_parser::put_token()
{
    --_token_it;
}

TOOSKA_END_NAMESPACE

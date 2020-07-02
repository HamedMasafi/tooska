#include "tokenizer_base.h"
#include "string_helper.h"

#include <wctype.h>
#include <cctype>
#include <iostream>
#include <stack>
#include <algorithm>
#include <array>

using namespace std;

TOOSKA_BEGIN_NAMESPACE(core)

namespace _private {
class string_buffer
{
    private:
    char* _data;
    size_t _index;
    size_t _size;

    public:
    string_buffer(const size_t &s) : _index(0)
    {
        _data = new char[s];
    }

    void push(char ch) {
        _data[_index++ % _size] = ch;
    }

    bool operator ==(const std::string &other) {
        if (other.size() != _size)
            return false;

        for (size_t i = 0; i < _size; ++i) {
            if (_data[(_index + i) % _size] != other.at(i))
                return false;
        }
        return true;
    }
};
}

tokenizer_base::tokenizer_base()
{
}

tokenizer_base::~tokenizer_base()
{

}

std::vector<std::string> tokenizer_base::tokens() const
{
    return _tokens;
}

void tokenizer_base::print_invalid_token_message(const string &token, const string &expected)
{
    std::cout << "Invalid token '" << token << "'";
    if (!expected.empty())
        std::cout << ". Expected '" << expected << "'";
    std::cout << "." << std::endl;
}

bool tokenizer_base::parse_tokens()
{
    _tokens.clear();
    char ch;

    while (get_char_from_buffer(&ch)) {
        std::string last_token;

        if (ignore(ch))
            continue;

        std::string s;
        s+=ch;
        auto literal = find_acceptable_literal(s);
        if (literal) {
            if (literal->insert_content) {
                if (literal->insert_begin_end)
                    _tokens.push_back(literal->begin);

                if (is_valid_token(last_token))
                    _tokens.push_back(last_token);
                else if (literal->insert_if_empty)
                    _tokens.push_back("");

                if (literal->insert_begin_end)
                    _tokens.push_back(literal->end);

                continue;
            }
        }
        bool outer_continue = false;
        if (outer_continue)
            continue;

        for (auto &fn : _check_fns)
            if (fn(ch)) {
                last_token = read_until(_text, fn);
                if (last_token.length()) {
                    _tokens.push_back(last_token);
                    outer_continue = true;
                    break;
                }
            }
        if (outer_continue)
            continue;

        if (ispunct(ch)) {
            _tokens.push_back(std::string(ch, 1));
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
    return true;
}

string tokenizer_base::read_until(const string &text, std::function<int (int)> fn)
{
    std::string s;
    char ch;
    while (get_char_from_buffer(&ch) && fn(ch)) {
        s += ch;
    }
    return s;
}

string tokenizer_base::read_until(const literal_t *lt)
{
    char ch;

    std::string ts;

    while (get_char_from_buffer(&ch)) {
        ts += ch;
//        se.push(ch);
        if (lt->ignore.size() && string_helper::ends_width(ts, lt->ignore)) {
            ts = ts.substr(0, ts.size() - lt->ignore.length() - 1);
            continue;
        }
        if (string_helper::ends_width(ts, lt->end))
            break;
    }

    return ts;
//            text.substr(start, i - start - lt->end.length() + 1);
    return "";
}

bool tokenizer_base::is_valid_token(const string &token)
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

string tokenizer_base::take_token()
{
    if (_token_it == _tokens.end()) {
//        std::cout << "No token avaible" << std::endl;
        return std::string();
    }

    auto ret = *_token_it;

    ++_token_it;
    return ret;
}

string tokenizer_base::next_token(int space)
{
    if (_token_it == _tokens.end() || (_token_it + space) == _tokens.end())
        return std::string();
    return *(_token_it + space);
}

string tokenizer_base::put_token()
{
    --_token_it;
}

string tokenizer_base::read_until(const size_t &len)
{
    std::string s;
    for (size_t c = 0; c < len; ++c) {
        char ch;
        if (!get_char_from_buffer(&ch))
            return std::string();
        s += ch;
    }
    return s;
}

tokenizer_base::token_t tokenizer_base::read_token()
{
    char ch;
//    get_char_from_buffer(&ch);

    std::string s;
//    s += ch;
    auto literal = find_acceptable_literal(s);
    if (literal) {
        if (literal->insert_content) {
            if (literal->insert_begin_end)
                _tokens.push_back(literal->begin);

            if (is_valid_token(s))
                _tokens.push_back(s);
            else if (literal->insert_if_empty)
                _tokens.push_back("");

            if (literal->insert_begin_end)
                _tokens.push_back(literal->end);
        }

        return token_t{1, s, literal};
    }

    s = "";
    auto code = find_acceptable_token(s);
    if (code) {
        return token_t{code, s, nullptr};
    }
    string_helper::trim(s);
    if (s.size())
        return token_t{99, s, nullptr};

    if (atend())
        return token_t{0, s, nullptr};

    return token_t{99, s, nullptr};
}

bool tokenizer_base::ignore(char ch)
{
    return (iscntrl(ch) || isspace(ch) || isblank(ch) || ch == '\n' || ch == '\r');
}

bool tokenizer_base::get_char_from_buffer(char *ch)
{
    if (_buffer.size()) {
        *ch = _buffer.back();
        _buffer.pop_back();
        return true;
    }
    return readchar(ch);
}

tokenizer_base::literal_t *tokenizer_base::find_acceptable_literal(std::string &s)
{
    char ch;
    size_t max{0};
    for (auto i = _literals.begin(); i < _literals.end(); ++i)
        max = std::max(max, (*i)->begin.size());

    while (get_char_from_buffer(&ch)) {
        literal_t *alt{nullptr};
        s += ch;
        int acceptable_count{0};
        for (auto i = _literals.begin(); i < _literals.end(); ++i) {
            std::string rem;
            auto ac = (*i)->match(s, rem);

            if (ac) {
                acceptable_count++;
                alt = *i;
            }
        }
        switch (acceptable_count) {
        case 0:
            for (size_t i = 0; i < s.size(); ++i)
                _buffer.push_back(s.at(i));

            return nullptr;

        case 1:
            s = read_until(alt);
            return alt;

        default:
            continue;
        }
    }
    _buffer.push_back(ch);
    return nullptr;
}

size_t tokenizer_base::find_acceptable_token(string &s)
{
    auto fnlist = _check_functions;
    char ch;
    size_t selected_fn{0};

    while (fnlist.size()) {
        get_char_from_buffer(&ch);
        s += ch;

        for (auto fn = fnlist.begin(); fn != fnlist.end(); ++fn) {
            if (!(*fn).second(ch)) {
                if (fn == fnlist.end())
                    break;
                else {
                    fnlist.erase(fn);
                    --fn;
                    continue;
                }
            }
        }

        if (fnlist.size() == 1)
            selected_fn = (*fnlist.begin()).first;
    }

    if (selected_fn) {
    } else {
        s.clear();
    }
    return selected_fn;

    s += ch;
    for (auto i = _check_functions.begin(); i != _check_functions.end(); ++i) {
        if ((*i).second(ch)) {
            do {
                get_char_from_buffer(&ch);
                s += ch;
            } while ((*i).second(ch));
            s = s.substr(0, s.size() - 1);
            _buffer.push_back(ch);
            return (*i).first;
        }
    }
    return 0;
}

void tokenizer_base::add_check_function(size_t code, tokenizer_base::char_check_cb cb)
{
    _check_functions[code] = cb;
}

void tokenizer_base::add_literal(tokenizer_base::literal_t *lt)
{
    _literals.push_back(lt);
}

TOOSKA_END_NAMESPACE

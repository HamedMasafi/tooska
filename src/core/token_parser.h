#ifndef TOKENPARSER_H
#define TOKENPARSER_H

#include "../global.h"
#include <functional>
#include <vector>
#include <list>

TOOSKA_BEGIN_NAMESPACE(core)

class token_parser
{
protected:
    struct comment_t {
        std::string begin;
        std::string end;
    };

    struct literal_t {
        std::string begin;
        std::string end;
        std::string ignore;
        bool insert_begin_end;
        bool insert_content;
    };

    std::string _error_message;
    std::vector<literal_t*> _literals;
    std::string _text;
//    std::vector<std::function<int(int)>> _check_fns;
    std::vector<int(*)(int)> _check_fns;
    std::vector<std::string> _tokens;
    std::vector<std::string>::iterator _token_it;

public:
    token_parser();
    virtual ~token_parser();

    std::string text() const;
    void set_text(const std::string &text);

    std::vector<std::string> tokens() const;

protected:
    void print_invalid_token_message(const std::string &token, const std::string &expected = std::string());
    std::vector<std::string> parse_tokens();
    virtual void parse() = 0;
    std::string read_until(const std::string &text, size_t &i, std::function<int(int)> fn) const;
    std::string read_until(const std::string &text, size_t &i, const literal_t *lt) const;
    bool is_valid_token(const std::string &token) const;
    std::string take_token();
};

TOOSKA_END_NAMESPACE

#endif // TOKENPARSER_H

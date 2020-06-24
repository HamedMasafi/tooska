#ifndef TOKENIZER_BASE_H
#define TOKENIZER_BASE_H

#include "../global.h"
#include <functional>
#include <vector>
#include <list>

TOOSKA_BEGIN_NAMESPACE(core)

class tokenizer_base
{
    public:
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
        bool insert_if_empty;

        literal_t(std::string begin, std::string end, std::string ignore,
                bool insert_begin_end, bool insert_content)
            : begin(begin), end(end), ignore(ignore),
              insert_begin_end(insert_begin_end),
              insert_content(insert_content),
              insert_if_empty(false)
        {}

        literal_t(std::string begin, std::string end, std::string ignore,
                bool insert_begin_end, bool insert_content, bool insert_if_empty)
            : begin(begin), end(end), ignore(ignore),
              insert_begin_end(insert_begin_end),
              insert_content(insert_content),
              insert_if_empty(insert_if_empty)
        {}
    };

    std::string _error_message;
    std::vector<literal_t*> _literals;
    std::string _text;

    std::vector<int(*)(int)> _check_fns;
    std::vector<std::string> _tokens;
    std::vector<std::string>::iterator _token_it;
    tokenizer_base();
    virtual ~tokenizer_base();

    bool parse_tokens();

    void print_invalid_token_message(const std::string &token, const std::string &expected = std::string());
    std::string read_until(const size_t &len);
    std::string read_until(const std::string &text, std::function<int(int)> fn);
    std::string read_until(const std::string &text, const literal_t *lt);
    bool is_valid_token(const std::string &token);
    std::string take_token();
    std::string next_token(int space = 0);
    std::string put_token();

    std::vector<std::string> tokens() const;

    std::string read_token();

protected:
    virtual bool ignore(char ch);
    virtual bool readchar(char *ch) = 0;
    bool get_char_from_buffer(char *ch);
};

TOOSKA_END_NAMESPACE

#endif // TOKENIZER_BASE_H

#ifndef TOKENIZER_BASE_H
#define TOKENIZER_BASE_H

#include "../global.h"
#include <functional>
#include <vector>
#include <list>
#include <map>

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

        bool acceptable(char ch) {
            return begin.size() && begin[0] == ch;
        }
        bool acceptable(const std::string &s) {
            return begin.size() >= s.size() && begin.substr(0, s.size()) == s;
        }
        bool match(const std::string &s, std::string &rem) {
            return s.size() >= begin.size() && s.substr(0, begin.size()) == begin;
        }
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

    typedef std::function<bool(char)> char_check_cb;
    class toekn_fn {
        char_check_cb cb;
        size_t min_len;
        ssize_t max_len;
    };

    struct token_t {
        size_t code;
        std::string token;
        literal_t *literal;
    };

    std::string _error_message;
    std::vector<literal_t*> _literals;
    std::vector<std::string> _tokens;
    std::vector<std::string>::iterator _token_it;
    std::map<size_t, char_check_cb> _check_functions;
    std::vector<char> _buffer;

    std::string _text;
    std::vector<int(*)(int)> _check_fns;

    tokenizer_base();
    virtual ~tokenizer_base();

    bool parse_tokens();

    void print_invalid_token_message(const std::string &token, const std::string &expected = std::string());
    std::string read_until(const size_t &len);
    std::string read_until(const std::string &text, std::function<int(int)> fn);
    std::string read_until(const literal_t *lt);
    bool is_valid_token(const std::string &token);
    std::string take_token();
    std::string next_token(int space = 0);
    std::string put_token();

    std::vector<std::string> tokens() const;

    token_t read_token();

    literal_t *find_acceptable_literal(std::string &s);
    size_t find_acceptable_token(std::string &s);

    void add_check_function(size_t code, char_check_cb cb);
    void add_literal(literal_t *lt);

protected:
    virtual bool ignore(char ch);
    virtual bool readchar(char *ch) = 0;
    virtual bool atend() = 0;
    bool get_char_from_buffer(char *ch);
};

TOOSKA_END_NAMESPACE

#endif // TOKENIZER_BASE_H

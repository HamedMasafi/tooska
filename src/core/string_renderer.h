#ifndef STRING_RENDERER_H
#define STRING_RENDERER_H

#include "../global.h"
#include <string>

TOOSKA_BEGIN_NAMESPACE(core)

class string_renderer
{
    std::string _buffer;
    print_type _type;
    size_t _level;

    enum class last_action {
        etc,
        new_line,
        space
    };
    last_action _last_action;

public:
    string_renderer(print_type type);
    void append(const std::string &buffer);
    void append(const std::string &&buffer);
    void append_line(const std::string &buffer);
    void append_line(const std::string &&buffer);
    void new_line();
    void double_new_line();
    void space();
    void indent();
    void unindent();
    std::string to_string() const;
    print_type type() const;
    void set_type(const print_type &type);
};

TOOSKA_END_NAMESPACE

#endif // STRING_RENDERER_H

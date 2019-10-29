#include "string_renderer.h"

#define INDENT_SIZE 4

TOOSKA_BEGIN_NAMESPACE(core)

string_renderer::string_renderer(print_type type) : _type(type), _level(0), _last_action(last_action::etc)
{

}

void string_renderer::append(const std::string &buffer)
{
    _last_action = last_action::etc;
    _buffer.append(buffer);
}

void string_renderer::append(const std::string &&buffer)
{
    _last_action = last_action::etc;
    _buffer.append(buffer);
}

void string_renderer::append_line(const std::string &buffer)
{
    append(buffer);
    new_line();
}

void string_renderer::append_line(const std::string &&buffer)
{
    append(buffer);
    new_line();
}

void string_renderer::new_line()
{
    if (_last_action == last_action::new_line)
        return;
    if (_type == print_type::formatted) {
        _last_action = last_action::new_line;
        _buffer.append("\n");
        for (unsigned long i = 0; i < INDENT_SIZE * _level; ++i)
            _buffer.append(" ");
    }
}

void string_renderer::double_new_line()
{
    if (_last_action == last_action::new_line)
        return;
    if (_type == print_type::formatted) {
        _last_action = last_action::new_line;
        _buffer.append("\n\n");
        for (unsigned long i = 0; i < INDENT_SIZE * _level; ++i)
            _buffer.append(" ");
    }
}

void string_renderer::space()
{
    if (_last_action == last_action::space)
        return;
    if (_type == print_type::formatted) {
        _last_action = last_action::space;
        _buffer.append(" ");
    }
}

void string_renderer::indent()
{
    _level++;

    if (_last_action == last_action::new_line)
        for (unsigned long i = 0; i < INDENT_SIZE; ++i)
            _buffer.append(" ");
}

void string_renderer::unindent()
{
    _level--;

    if (_last_action == last_action::new_line)
        _buffer.erase(_buffer.end() - INDENT_SIZE, _buffer.end());
}

std::string string_renderer::to_string() const
{
    return _buffer;
}

print_type string_renderer::type() const
{
    return _type;
}

void string_renderer::set_type(const print_type &type)
{
    _type = type;
}

TOOSKA_END_NAMESPACE

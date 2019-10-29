#include "soap_http_parser.h"
#include <iostream>
#include <core/string_helper.h>
#include <assert.h>

TOOSKA_BEGIN_NAMESPACE(soap)

soap_http_parser::soap_http_parser(const std::string &data)
    : _data(data)
{

}

void soap_http_parser::parse()
{
    _index = 0;
    auto line = read_until('\n');
    auto parts = tooska::core::string_helper::split(line, ' ');
    _method = parts.at(0);
    _path = parts.at(1);
    _version = parts.at(2);

    while ((line = read_until('\n')) != "\n") {
        std::string name, value;
        if (!read_name_value(line, name, value))
            break;
        _headers[name] = value;
    }

    auto i = std::stoi(_headers["Content-Length"]);
    auto body = _data.substr(_index, i);
    std::cout << "Content-Length:" << i << std::endl << body << std::endl;

    assert(_index + i == _data.size());
}




std::string soap_http_parser::read_until(const char &ch)
{
    std::string r;
    while (_index < _data.size()) {
        if (_data.at(_index) == ch)
            break;
        r += _data.at(_index++);
    }
    _index++;
    return r;
}

bool soap_http_parser::read_name_value(const std::string &line, std::string &name, std::string &value) const
{
    auto p = line.find(':');
    if (p == std::string::npos)
        return false;
    name = line.substr(0, p);
    if (line.at(p + 1) == ' ')
        ++p;

    if (line.at(p + 1) == '"')
        ++p;

    if (line.at(line.size() - 1) == '"')
        value = line.substr(p + 1, line.size() - p - 2);
    else
        value = line.substr(p + 1);

    return true;
}

std::string soap_http_parser::method() const
{
    return _method;
}

std::string soap_http_parser::path() const
{
    return _path;
}

std::string soap_http_parser::version() const
{
    return _version;
}

std::map<std::string, std::string> soap_http_parser::headers() const
{
    return _headers;
}

TOOSKA_END_NAMESPACE

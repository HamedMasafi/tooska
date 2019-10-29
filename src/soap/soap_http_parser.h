#ifndef SOAP_HTTP_PARSER_H
#define SOAP_HTTP_PARSER_H

#include "../global.h"
#include <string>
#include <map>

TOOSKA_BEGIN_NAMESPACE(soap)

class soap_http_parser
{
    std::string _data;
    size_t _index;
    std::string _method;
    std::string _path;
    std::string _version;
    std::map<std::string, std::string> _headers;

public:
    soap_http_parser(const std::string &data);
    void parse();

    std::string method() const;

    std::string path() const;

    std::string version() const;

    std::map<std::string, std::string> headers() const;

    private:
    std::string read_until(const char &ch);
    bool read_name_value(const std::string &line, std::string &name, std::string &value) const;
};

TOOSKA_END_NAMESPACE

#endif // SOAP_HTTP_PARSER_H

#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H

#include "../global.h"
#include <vector>
#include <map>

#include "variant.h"

TOOSKA_BEGIN_NAMESPACE(core)

class command_line_parser
{
public:
    struct arg {
        std::string short_name;
        std::string name;
        std::string descript;
    };
    std::vector<arg*> _args;
    std::map<arg*, tooska::core::variant> _values;

    command_line_parser(int argc, char **argv);

    arg *find(const std::string &name) const;
};

TOOSKA_END_NAMESPACE

#endif // COMMAND_LINE_PARSER_H

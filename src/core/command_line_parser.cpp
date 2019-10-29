#include "command_line_parser.h"
#include <iostream>

TOOSKA_BEGIN_NAMESPACE(core)

command_line_parser::command_line_parser(int argc, char **argv)
{
    for (int i = 0; i < argc; ++i) {
        std::string a_name(argv[i]);

        auto a = find(a_name);
        if (!a) {
            std::cout << "Invalid argumant: " << a_name << std::endl;
            continue;
        }
    }
}

command_line_parser::arg *command_line_parser::find(const std::string &name) const
{
    for (auto i = _args.begin(); i != _args.end(); ++i)
        if ((*i)->name == name || (*i)->short_name == name)
            return *i;
    return nullptr;
}

TOOSKA_END_NAMESPACE

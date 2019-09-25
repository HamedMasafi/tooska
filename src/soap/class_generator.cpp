#include <iostream>

#include "class_generator.h"

#include "wsdl_parser.h"
#include "../core/string_renderer.h"

TOOSKA_BEGIN_NAMESPACE(soap)

class_generator::class_generator(wsdl_parser *parser) : _parser(parser)
{

}

void class_generator::generate() const
{
    tooska::core::string_renderer r(tooska::print_type::formatted);
    auto services = _parser->services();
    for (auto ser: services) {
        r.append("class " + ser->name);
        r.new_line();
        r.append("{\npublic:");
        r.new_line();
        r.indent();

        for (auto port: ser->ports) {
            auto binding = _parser->find_binding(port->binding);

            if (!binding) {
                r.append("//No binding for " + port->binding + ";");
                r.new_line();
                continue;
            }

//            for (auto operation: binding->operations) {
//                auto input_message = _parser->find_message(operation->input);
//                auto output_message = _parser->find_message(operation->output);

//                r.append(output_message->name);
//                r.space();
//                r.append(binding->name);
//                r.space("(");
//                r.append(input_message->name);
//                r.append(");");
//                r.append(port->binding);
//                r.new_line();
//            }
        }
        r.unindent();
        r.append("};");
        r.new_line();
    }

    std::cout << r.to_string() << std::endl;
}

TOOSKA_END_NAMESPACE

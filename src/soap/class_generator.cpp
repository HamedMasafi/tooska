#include <iostream>

#include "class_generator.h"

#include "wsdl_parser.h"
#include "../core/string_renderer.h"
#include "../core/string_helper.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

// for windows mkdir
#ifdef _WIN32
#include <direct.h>
#endif

TOOSKA_BEGIN_NAMESPACE(soap)

class_generator::class_generator(wsdl_parser *parser, const std::string &dir_path)
    : _parser(parser), _path(dir_path)
{
    if (_path.size())
        _path += "/";
    mkdir(_path + "common");
    mkdir(_path + "client");
    mkdir(_path + "server");
}

void class_generator::generate() const
{
    for (auto s: _parser->services()) {
        generate_header("server", s->name, s, true);
        generate_header("client", s->name, s, false);
        generate_implement("client", s->name, s, false);
//        generate_implement("server", s->name, s, true);
    }
}

void class_generator::mkdir(const std::string &path)
{
#ifdef _WIN32
    _mkdir(path);
#else
#   if _POSIX_C_SOURCE
    ::mkdir(path.c_str(), 0755);
#   else
    ::mkdir(path, 0755); // not sure if this works on mac
#   endif
#endif
}

void class_generator::generate_header(const std::string &dir, const std::string &file_name, wsdl_parser::service_t *service, bool server) const
{
    tooska::core::string_renderer r(tooska::print_type::formatted);
    auto macro_name = file_name + ".h";
    tooska::core::string_helper::replace(macro_name, ".", "_");
    tooska::core::string_helper::toupper(macro_name);

    r.append_line("#ifndef " + macro_name);
    r.append_line("#define " + macro_name);
    r.new_line();

    for (wsdl_parser::element_t *e : _parser->elements())
        render_element(&r, e);

    r.new_line();

    r.append_line("class " + service->name);
    r.append_line("{\npublic:");
    r.indent();

    for (auto port : service->ports) {
        for (auto op : port->operations) {
            if (server)
                r.append("virtual ");

            render_return_type(&r, op->outout);

            r.space();
            r.append(op->name);
            r.append("(");

            render_params(&r, op->input);

            r.append(")");

            if (server)
                r.append(" = 0");

            r.append(";");

            r.new_line();
        }
    }

    if (server) {
        r.append_line("std::string process(const std::string &method_name, const std::string &body)");
        r.append("{");
        r.indent();
        r.new_line();
        r.append_line("tooska::serializer::soap_serializer serializer;");
        for (auto port : service->ports) {
            for (auto op : port->operations) {
                r.append_line("if (method_name == \"" + op->name + "\") {");
                r.indent();
                r.append("auto param_" + op->name + " = serializer.deserialize<");
                render_return_type(&r, op->outout);
                r.append_line(">(body);");

                r.append_line("auto ret_" + op->name + " = " + op->name + "(param_" + op->name + ");");
                r.append_line("return serializer.serialize(ret_" + op->name + ");");

                r.unindent();
                r.append_line("}");
            }
        }
        r.append_line("throw std::exception;");
        r.unindent();
        r.append_line("}");
    }

    r.unindent();
    r.append_line("};");
    r.new_line();
    r.append_line("#endif // " + macro_name);

    ofstream out;
    out.open(_path + dir + "/" + file_name + ".h");
    out << r.to_string();
    out.close();
}

void class_generator::generate_implement(const std::string &dir, const std::string &file_name, wsdl_parser::service_t *service, bool server) const
{
    tooska::core::string_renderer r(tooska::print_type::formatted);

    r.append_line("#include \"" + file_name + ".h\"");
    r.append_line("#include <tooska/soap/soap_client.h>");
    r.new_line();

    for (auto port : service->ports) {
        for (auto op : port->operations) {
            if (op->outout->element)
                r.append(op->outout->element->name);
            else
                r.append(op->outout->params.at(0)->type);
            r.space();
            r.append(file_name + "::" + op->name);
            r.append("(");

            render_params(&r, op->input);

            r.append_line(")");
            r.append("{");
            r.indent();
            r.new_line();
            r.append("return tooska::soap::client::invoke(\"" + op->name + "\"");
            for (auto t : op->input->params)
                r.append(", " + t->name);
//            r.append(").value<" + op->outout->params.at(0)->type + ">();");

            r.unindent();
            r.new_line();

            r.append_line("}");

            r.new_line();
        }
    }

    ofstream out;
    out.open(_path + dir + "/" + file_name + ".cpp");
    out << r.to_string();
    out.close();
}

void class_generator::render_return_type(tooska::core::string_renderer *r, tooska::soap::wsdl_parser::message_t *msg) const
{
    if (msg->element)
        r->append(msg->element->name);
    else
        r->append(msg->params.at(0)->type);
}

void class_generator::render_params(tooska::core::string_renderer *r, tooska::soap::wsdl_parser::message_t *msg) const
{
    if (msg->element) {
        r->append(msg->element->name + " param");
    } else {
        bool f = true;
        for (auto t : msg->params) {
            if (!f)
                r->append(", ");
            f = false;
            r->append(t->type);
            r->space();
            r->append(t->name);
        }
    }
}

void class_generator::render_element(tooska::core::string_renderer *r, wsdl_parser::element_t *e) const
{
    r->append_line("struct " + e->name + " : public tooska::serialization::serializable {");
    r->indent();
    for (auto t: e->params)
        r->append_line(t->type + " " + t->name + ";");

    r->append_line("");
    r->append_line("SERIALIZATION_BLOCK(" + e->name + ") {");
    r->indent();
    for (auto t: e->params)
        r->append_line("FIELD(" + t->name + ")");
    r->unindent();
    r->append_line("}");
    r->unindent();
    r->append_line("};\n");
}


TOOSKA_END_NAMESPACE

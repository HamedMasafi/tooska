#include <iostream>
#include "wsdl_parser.h"
#include "../xml/xml_document.h"
#include "../xml/xml_node.h"
#include "../html/html_node.h"
#include "../core/string_renderer.h"
#include "../core/string_helper.h"
#include <iostream>

TOOSKA_BEGIN_NAMESPACE(soap)

wsdl_parser::wsdl_parser()
{
    xml = new tooska::xml::xml_document;
}

void wsdl_parser::set_content(const std::string &wsdl)
{
    _wsdl = wsdl;
    xml->set_text(_wsdl);


    auto services = xml->find("definitions/service");
    for (auto s : services)
        read_service(s);

    auto bindings = xml->find("definitions/binding");
    for (auto b: bindings)
        read_binding(b);

    auto elements = xml->find("definitions/types/schema/element");
    for (auto el: elements)
        read_type(el);

    auto messages = xml->find("definitions/message");
    for (auto msg: messages)
        read_message(msg);

    _version_str = xml->doctype()->attr("version");
    if (_version_str == "1.0")
        _version = V_1_0;
    else if (_version_str == "1.1")
        _version = V_1_1;
    else if (_version_str == "1.2")
        _version = V_1_2;
    else if (_version_str == "2.0")
        _version = V_2_0;
    else
        _version = Unset;
}

bool wsdl_parser::read_type(tooska::xml::node *n)
{
    auto complexType = n->find("complexType/sequence");
    if (complexType.size() == 1) {
        auto t = new complex_type;
        t->name = n->attr("name");
        auto elements = complexType.first_or_null()->find("element");
        for (auto el: elements) {
            t->types[el->attr("name")] = el->attr("type");
        }
        _complex_types.push_back(t);
    }
    return true;
}

bool wsdl_parser::read_message(tooska::xml::node *n)
{
    auto part = n->find("part");
    if (part.size() != 1)
        return false;
    auto msg = new message;
    msg->name = n->attr("name");
    msg->part = part[0]->attr("name");
    msg->element = part[0]->attr("element");
    _messages.push_back(msg);
    return true;
}

void wsdl_parser::remove_namespace(std::string &str) const
{
    for (auto ns: _namespaces) {
        if (str.rfind(ns) == 0) {
            tooska::core::string_helper::replace(str, ns + ":", "");
            return;
        }
    }

}

std::string wsdl_parser::remove_namespace_copy(const std::string &str) const
{
    auto parts = tooska::core::string_helper::split(str, ':');
    if (parts.size() == 2)
        return parts[1];
    return str;
}

void wsdl_parser::read_service(tooska::xml::node *n)
{
    auto ser = new service;
    ser->name = n->attr("name");

    auto ports = n->find("port");
    for (auto p: ports) {
        auto sp = new service_port;
        sp->name = p->attr("name");
        sp->binding = remove_namespace_copy(p->attr("binding"));
        ser->ports.push_back(sp);
    }
    _services.push_back(ser);
}

void wsdl_parser::read_binding(tooska::xml::node *n)
{
    auto read_io = [](tooska::xml::node *io) -> binding_operation_io*{
        auto o = new binding_operation_io;
        auto body = io->find("body");
        o->encodingStyle = body[0]->attr("encodingStyle");
        o->namespace_s = body[0]->attr("namespace");
        o->use = body[0]->attr("use");
        return o;
    };
    auto bi = new binding;
    bi->name = n->attr("name");
    auto b = n->find("binding");
    if (b.size() != 1)
        return;
    bi->style = b[0]->attr("style");
    bi->transport = b[0]->attr("transport");

    auto operations = n->find("operation");
    for (auto op: operations) {
        auto prop = op->find("operation");

        auto operation = new binding_operation;
        operation->style = prop[0]->attr("style");
        operation->soapAction = prop[0]->attr("soapAction");

        operation->input = read_io(op->find("input")[0]);
        operation->output = read_io(op->find("output")[0]);

        bi->operations.push_back(operation);
    }

    _bindings.push_back(bi);
}

std::vector<wsdl_parser::binding *> wsdl_parser::bindings() const
{
    return _bindings;
}

std::vector<wsdl_parser::service *> wsdl_parser::services() const
{
    return _services;
}

wsdl_parser::binding *wsdl_parser::find_binding(const std::string &name) const
{
    for (auto b: _bindings) {
        if (b->name == name)
            return b;
        else
            std::cout << " not this " << b->name << std::endl;
    }
    return nullptr;
}

wsdl_parser::message *wsdl_parser::find_message(const std::string &name) const
{
    for (auto msg: _messages) {
        if (msg->name == name)
            return msg;
    }
    return nullptr;
}

wsdl_parser::version_t wsdl_parser::version() const
{
    return _version;
}

std::string wsdl_parser::version_str() const
{
    return _version_str;
}

wsdl_parser::~wsdl_parser()
{
    delete xml;
}

TOOSKA_END_NAMESPACE

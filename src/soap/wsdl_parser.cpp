#include "wsdl_parser.h"

#include "../core/string_helper.h"
#include "../core/string_renderer.h"
#include "../html/html_node.h"
#include "../xml/xml_document.h"
#include "../xml/xml_node.h"

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
        _services.push_back(read_service(s));

    auto bindings = xml->find("definitions/binding");
    for (auto b : bindings)
        read_binding(b);

    auto elements = xml->find("definitions/types/schema/element");
    for (auto el : elements)
        read_type(el);

    auto messages = xml->find("definitions/message");
    for (auto msg : messages)
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

wsdl_parser::message_t *wsdl_parser::read_message(tooska::xml::node *n)
{
    auto parts = n->find("part");
    auto msg = new message_t;
    if (parts.size() == 1 && parts.first()->has_attr("element")) {
        auto el_name = remove_namespace_copy(parts.first()->attr("element"));
        auto el_node = find_node("definitions/types/schema/element", el_name);
        if (!el_node)
            std::cout << "element not found: " << parts.first()->attr("element") << std::endl;
        else
            msg->element = read_element(el_node);
    } else {
        for (auto part : parts) {
            auto p = new param;
            p->name = part->attr("name");
            p->type = remove_namespace_copy(part->attr("type"));

            msg->params.push_back(p);
        }
    }
    return msg;
}

wsdl_parser::service_t *wsdl_parser::read_service(tooska::xml::node *n)
{
    auto ser  = new service_t;
    ser->name = n->attr("name");

    auto ports = n->find("port");
    for (auto p : ports) {
        auto sp = read_service_port(p);
        ser->ports.push_back(sp);
    }
    return ser;
}

wsdl_parser::service_port_t *wsdl_parser::read_service_port(tooska::xml::node *n)
{
    auto binding_name = remove_namespace_copy(n->attr("binding"));
    auto binding_node = find_node("definitions/binding", binding_name);
    if (!binding_node)
        return nullptr;


    auto port_name = remove_namespace_copy(binding_node->attr("type"));
    auto port_type_node = find_node("definitions/portType", port_name);
    if (!port_type_node)
        return nullptr;

    auto sp = new service_port_t;
    sp->name = n->attr("name");
    auto port_type_operations = port_type_node->find("operation");
    for (auto pt: port_type_operations) {
        auto pp = read_port_type_operation(pt);
        if (pp)
            sp->operations.push_back(pp);
    }
    return sp;
}

wsdl_parser::binding_t *wsdl_parser::read_binding(tooska::xml::node *n)
{
    auto read_io = [](tooska::xml::node *io) -> binding_operation_io * {
        auto o           = new binding_operation_io;
        auto body        = io->find("body");
        o->encodingStyle = body[0]->attr("encodingStyle");
        o->namespace_s   = body[0]->attr("namespace");
        o->use           = body[0]->attr("use");
        return o;
    };
    auto bi  = new binding_t;
    bi->name = n->attr("name");
    auto port_type_name = n->attr("type");
    auto port_type = find_node("definitions/portType", remove_namespace_copy(port_type_name));

    if (!port_type)
        return nullptr;

    auto port_type_operations = port_type->find("operation");
    for (auto pt: port_type_operations)
        read_port_type_operation(pt);

    auto b   = n->find("binding");
    if (b.size() != 1)
        return nullptr;
    bi->style     = b[0]->attr("style");
    bi->transport = b[0]->attr("transport");

    auto operations = n->find("operation");
    for (auto op : operations) {
        auto prop = op->find("operation");

        auto operation        = new binding_operation_t;
        operation->style      = prop[0]->attr("style");
        operation->soapAction = prop[0]->attr("soapAction");

        operation->input  = read_io(op->find("input")[0]);
        operation->output = read_io(op->find("output")[0]);

        bi->operations.push_back(operation);
    }

    return bi;
}

wsdl_parser::port_type_operation *wsdl_parser::read_port_type_operation(tooska::xml::node *n)
{
    auto r = new port_type_operation;
    r->name = n->attr("name");

    auto i_node = n->find("input").first();
    auto o_node = n->find("output").first();

    if (!i_node || ! o_node)
        return nullptr;

    r->input = read_message(find_node("definitions/message", remove_namespace_copy(i_node->attr("message"))));
    r->outout = read_message(find_node("definitions/message", remove_namespace_copy(o_node->attr("message"))));
    return r;
}

bool wsdl_parser::read_type(tooska::xml::node *n)
{
    auto complexType = n->find("complexType/sequence");
    if (complexType.size() == 1) {
        auto t        = new complex_type;
        t->name       = n->attr("name");
        auto elements = complexType.first()->find("element");
        for (auto el : elements) {
            t->types[el->attr("name")] = el->attr("type");
        }
        _complex_types.push_back(t);
    }
    return true;
}

void wsdl_parser::remove_namespace(std::string &str) const
{
    for (auto ns : _namespaces) {
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

vector<wsdl_parser::binding_t *> wsdl_parser::bindings() const
{
    return _bindings;
}

vector<wsdl_parser::service_t *> wsdl_parser::services() const
{
    return _services;
}

wsdl_parser::binding_t *wsdl_parser::find_binding(const std::string &name) const
{
    for (auto b : _bindings) {
        if (b->name == name)
            return b;
        else
            std::cout << " not this " << b->name << std::endl;
    }
    return nullptr;
}

wsdl_parser::message_t *wsdl_parser::find_message(const std::string &name) const
{
    for (auto msg : _messages) {
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

tooska::xml::node *wsdl_parser::find_node(const std::string &path,
                                          const std::string &name) const
{
    auto childs = xml->find(path);
    for (auto ch : childs)
        if (ch->attr("name") == name)
            return ch;

    return nullptr;
}

wsdl_parser::element_t *wsdl_parser::read_element(tooska::xml::node *n)
{
    tooska::xml::node *sequence = n->find("complexType/sequence").first();
    if (!sequence)
        return nullptr;

    auto element = new element_t;
    element->name = n->attr("name");
    auto els = sequence->find("element");
    for (auto el: els) {
        element->params.push_back(new param{el->attr("name"),
                                            remove_namespace_copy(el->attr("type"))});
    }
    _elements.push_back(element);
    return element;
}

std::vector<wsdl_parser::element_t *> wsdl_parser::elements() const
{
    return _elements;
}

TOOSKA_END_NAMESPACE

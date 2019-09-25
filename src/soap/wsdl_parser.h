#ifndef wsdl_parser_H
#define wsdl_parser_H

#include "../global.h"
#include <string>
#include <vector>
#include <map>

TOOSKA_BEGIN_NAMESPACE(core)
class string_renderer;
TOOSKA_END_NAMESPACE

TOOSKA_BEGIN_NAMESPACE(xml)
class xml_document;
class node;
TOOSKA_END_NAMESPACE

TOOSKA_BEGIN_NAMESPACE(soap)

using namespace std;
class wsdl_parser
{
    string _wsdl;
    tooska::xml::xml_document *xml;
    vector<string> _namespaces;
    string _default_namespace;

    struct message {
        string name;
        string part;
        string element;
    };
    std::vector<message*> _messages;

    struct complex_type {
        string name;
        map<string, string> types;
    };
    vector<complex_type*> _complex_types;

    struct binding_operation_io {
        string use;
        string namespace_s;
        string encodingStyle;
    };

    struct binding_operation {
        string soapAction;
        string style;
        binding_operation_io *input;
        binding_operation_io *output;
    };
    struct binding {
        string name;
        string transport;
        string style;
        vector<binding_operation*> operations;
    };

    struct service_port {
        string name;
        string binding;
    };
    struct service {
        string name;
        vector<service_port*> ports;
    };

    vector<binding*> _bindings;
    vector<service*> _services;

    void read_service(tooska::xml::node *n);
    void read_binding(tooska::xml::node *n);
    bool read_type(tooska::xml::node *n);
    bool read_message(tooska::xml::node *n);

    void remove_namespace(string &str) const;
    string remove_namespace_copy(const string &str) const;
public:
    enum version_t {
        Unset,
        V_1_0,
        V_1_1,
        V_1_2,
        V_2_0
    } _version;
    std::string _version_str;

    wsdl_parser();
    ~wsdl_parser();
    void set_content(const string &wsdl);

    binding *find_binding(const string &name) const;
    message *find_message(const string &name) const;
    vector<binding *> bindings() const;
    vector<service *> services() const;
    version_t version() const;
    std::string version_str() const;
};

TOOSKA_END_NAMESPACE

#endif // wsdl_parser_H

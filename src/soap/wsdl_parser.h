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
public:
    string _wsdl;
    tooska::xml::xml_document *xml;
    vector<string> _namespaces;
    string _default_namespace;

    struct param {
        std::string name;
        std::string type;
        bool is_pointer;
    };

    struct element_t {
        std::string name;
        std::vector<param *> params;
    };
    std::vector<element_t*> _elements;
    struct message_t {
        string name;
        string part;
        element_t *element = nullptr;
        std::vector<param*> params;
    };
    std::vector<message_t*> _messages;

    struct port_type_operation {
        std::string name;
        message_t *input = nullptr;
        message_t *outout = nullptr;
    };

    struct complex_type {
        string name;
        map<string, string> types;
    };
    vector<complex_type*> _complex_types;

    struct binding_operation_io {
        string use;
        string namespace_s;
        string encodingStyle;
        message_t *message = nullptr;
    };

    struct binding_operation_t {
        string soapAction;
        string style;
        binding_operation_io *input = nullptr;
        binding_operation_io *output = nullptr;
    };
    struct binding_t {
        string name;
        string transport;
        string style;
        vector<binding_operation_t*> operations;
    };

    struct service_port_t {
        string name;
        string binding_name;
        binding_t *binding = nullptr;
        string address;
        std::vector<port_type_operation*> operations;
    };
    struct service_t {
        string name;
        string document;
        vector<service_port_t*> ports;
    };

    vector<binding_t*> _bindings;
    vector<service_t*> _services;

    tooska::xml::node *find_node(const std::string &path, const std::string &name) const;

    element_t *read_element(tooska::xml::node *n);
    service_t *read_service(tooska::xml::node *n);
    service_port_t *read_service_port(tooska::xml::node *n);
    binding_t *read_binding(tooska::xml::node *n);
    message_t *read_message(tooska::xml::node *n);
    port_type_operation *read_port_type_operation(tooska::xml::node *n);

    bool read_type(tooska::xml::node *n);

//    void read_service(tooska::xml::node *n);
//    void read_binding(tooska::xml::node *n);
//    bool read_type(tooska::xml::node *n);
//    bool read_message(tooska::xml::node *n);

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

    binding_t *find_binding(const string &name) const;
    message_t *find_message(const string &name) const;
    vector<binding_t *> bindings() const;
    vector<service_t *> services() const;
    version_t version() const;
    std::string version_str() const;
    std::vector<element_t *> elements() const;
};

TOOSKA_END_NAMESPACE

#endif // wsdl_parser_H

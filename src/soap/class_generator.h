#ifndef CLASS_GENERATOR_H
#define CLASS_GENERATOR_H

#include "../global.h"
#include <functional>
#include "wsdl_parser.h"

TOOSKA_BEGIN_NAMESPACE(core)
class string_renderer;
TOOSKA_END_NAMESPACE

TOOSKA_BEGIN_NAMESPACE(soap)

class wsdl_parser;
class class_generator
{
    wsdl_parser *_parser;
    std::string _path;

public:
    class_generator(wsdl_parser *parser, const std::string &dir_path = std::string());
    void generate() const;
private:
    typedef std::function<void(tooska::core::string_renderer*)> implementer_fn;

    void generate_header(const std::string &dir, const std::string &file_name,
                         wsdl_parser::service_t *service, bool pure_virtual = false) const;

    void generate_implement(const std::string &dir, const std::string &file_name,
                         wsdl_parser::service_t *service, bool server) const;
    void mkdir(const std::string &path);

    void render_element(tooska::core::string_renderer *r, wsdl_parser::element_t *e) const;
    void render_return_type(tooska::core::string_renderer *r, tooska::soap::wsdl_parser::message_t *msg) const;
    void render_params(tooska::core::string_renderer *r, tooska::soap::wsdl_parser::message_t *msg) const;
};

TOOSKA_END_NAMESPACE

#endif // CLASS_GENERATOR_H

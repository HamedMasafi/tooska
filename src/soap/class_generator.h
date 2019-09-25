#ifndef CLASS_GENERATOR_H
#define CLASS_GENERATOR_H

#include "../global.h"

TOOSKA_BEGIN_NAMESPACE(soap)

class wsdl_parser;
class class_generator
{
    wsdl_parser *_parser;

public:
    class_generator(wsdl_parser *parser);
    void generate() const;
};

TOOSKA_END_NAMESPACE

#endif // CLASS_GENERATOR_H

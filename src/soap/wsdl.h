#ifndef WSDL_H
#define WSDL_H

#include "../serialization/serializer_base.h"
#include "../serialization/serializable.h"

TOOSKA_BEGIN_NAMESPACE(soap)

class element{
    int minOccurs;
    std::string name;
    std::string type;

    SERIALIZATION_BLOCK(element) {
        FIELD(minOccurs)
        FIELD(name)
        FIELD(type)
    }
};

class wsdl : public tooska::serialization::serializable
{
public:
    wsdl();
};

TOOSKA_END_NAMESPACE

#endif // WSDL_H

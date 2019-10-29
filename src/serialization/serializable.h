#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "../global.h"
#define SERIALIZATION_BLOCK(name) \
    virtual std::string __class_name() const {\
        return #name; \
    }\
    void __tokenize(tooska::serialization::serializer_base *t)
#define FIELD(name)    t->set(#name, name);
#define FIELD_X(name, var)    t->set(#name, var);

TOOSKA_BEGIN_NAMESPACE(serialization)

class serializer_base;
class serializable
{
public:
    serializable();
    virtual std::string __class_name() const = 0;
    virtual void __tokenize(serializer_base *t) = 0;
};

TOOSKA_END_NAMESPACE

#endif // SERIALIZABLE_H

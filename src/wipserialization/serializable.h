#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "../global.h"
#define SERIALIZATION_BLOCK void serialize(serializer_base *t)
#define FIELD(name)    t->set(#name, name);

TOOSKA_BEGIN_NAMESPACE(serialization)

class serializer_base;
class serializable
{
public:
    serializable();
    virtual void serialize(serializer_base *t) = 0;
};

TOOSKA_END_NAMESPACE

#endif // SERIALIZABLE_H

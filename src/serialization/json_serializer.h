#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include "../global.h"

TOOSKA_BEGIN_NAMESPACE(json)
class json_document;
TOOSKA_END_NAMESPACE

TOOSKA_BEGIN_NAMESPACE(serialization)

class serializable;
class json_serializer
{
public:
    json_serializer();

    tooska::json::json_document *serialize(serializable* obj) const;
    void deserialize(tooska::json::json_document &doc, serializable *obj) const;
};

TOOSKA_END_NAMESPACE

#endif // JSON_SERIALIZER_H
